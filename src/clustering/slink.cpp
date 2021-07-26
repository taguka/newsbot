#include "slink.h"
#include "../util.h"

#include <algorithm>
#include <fstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {

using TClusterSiteNames = std::unordered_set<std::string>;

constexpr float INF_DISTANCE = 1.0f;

void ApplyTimePenalty(
    const std::vector<TDbDocument>::const_iterator begin,
    size_t docSize,
    Eigen::MatrixXf& distances
) {
    std::vector<TDbDocument>::const_iterator iIt = begin;
    std::vector<TDbDocument>::const_iterator jIt = begin + 1;
    for (size_t i = 0; i < docSize; ++i, ++iIt) {
        jIt = iIt + 1;
        for (size_t j = i + 1; j < docSize; ++j, ++jIt) {
            uint64_t leftTs = iIt->FetchTime;
            uint64_t rightTs = jIt->FetchTime;
            uint64_t diff = rightTs > leftTs ? rightTs - leftTs : leftTs - rightTs;
            float diffHours = static_cast<float>(diff) / 3600.0f;
            float penalty = 1.0f;
            if (diffHours >= 24.0f) {
                penalty = diffHours / 24.0f;
            }
            distances(i, j) = std::min(penalty * distances(i, j), INF_DISTANCE);
            distances(j, i) = distances(i, j);
        }
    }
}

bool IsNewClusterSizeAcceptable(size_t newClusterSize, float newDistance, const tg::TClusteringConfig& config) {
    if (newClusterSize <= config.small_cluster_size()) {
        return true;
    } else if (newClusterSize <= config.medium_cluster_size()) {
        return newDistance <= config.medium_threshold();
    } else if (newClusterSize <= config.large_cluster_size()) {
        return newDistance <= config.large_threshold();
    }
    return false;
}

bool CheckSetIntersection(const TClusterSiteNames& smallerSet, const TClusterSiteNames& largerSet) {
    return std::any_of(smallerSet.begin(), smallerSet.end(), [&largerSet](const auto& siteName) {
        return largerSet.find(siteName) != largerSet.end();
    });
}

bool HasSameSource(const TClusterSiteNames& firstSet, const TClusterSiteNames& secondSet) {
    if (firstSet.size() < secondSet.size()) {
        return CheckSetIntersection(firstSet, secondSet);
    }
    return CheckSetIntersection(secondSet, firstSet);
}

} // namespace

TSlinkClustering::TSlinkClustering(const tg::TClusteringConfig& config)
    : Config(config)
{
}

TClusters TSlinkClustering::Cluster(
    const std::vector<TDbDocument>& docs
) {
    std::unordered_map<tg::EEmbeddingKey, float> embeddingKeysWeights;
    for (const auto& embeddingKeyWeight : Config.embedding_keys_weights()) {
        embeddingKeysWeights[embeddingKeyWeight.embedding_key()] = embeddingKeyWeight.weight();
    }
    const size_t docSize = docs.size();

    const size_t intersectionSize = Config.intersection_size();
    std::vector<size_t> labels;
    labels.reserve(docSize);

    std::vector<TDbDocument>::const_iterator begin = docs.cbegin();
    std::unordered_map<size_t, size_t> oldLabelsToNew;
    size_t batchStart = 0;
    size_t prevBatchEnd = batchStart;
    size_t maxLabel = 0;
    while (prevBatchEnd < docs.size()) {
        size_t remainingDocsCount = docSize - batchStart;
        size_t batchSize = std::min(remainingDocsCount, static_cast<size_t>(Config.chunk_size()));
        std::vector<TDbDocument>::const_iterator end = begin + batchSize;

        std::vector<size_t> newLabels = ClusterBatch(begin, end, embeddingKeysWeights);
        std::for_each(newLabels.begin(), newLabels.end(), [&](size_t& i){ i += maxLabel; });
        maxLabel = *std::max_element(newLabels.begin(), newLabels.end());

        assert(begin->Url == docs[batchStart].Url);
        for (size_t i = batchStart; i < batchStart + intersectionSize && i < labels.size(); i++) {
            size_t oldLabel = labels[i];
            size_t batchIndex = static_cast<size_t>(i - batchStart);
            size_t newLabel = newLabels.at(batchIndex);
            oldLabelsToNew[oldLabel] = newLabel;
        }
        if (batchStart == 0) {
            for (size_t i = 0; i < std::min(intersectionSize, newLabels.size()); i++) {
                labels.push_back(newLabels[i]);
            }
        }
        for (size_t i = intersectionSize; i < newLabels.size(); i++) {
            labels.push_back(newLabels[i]);
        }
        assert(batchStart == static_cast<size_t>(std::distance(docs.begin(), begin)));
        assert(batchStart + batchSize == static_cast<size_t>(std::distance(docs.begin(), end)));
        for (const auto& pair : oldLabelsToNew) {
            assert(pair.first < pair.second);
        }

        prevBatchEnd = batchStart + batchSize;
        batchStart = prevBatchEnd - intersectionSize;
        begin = end - intersectionSize;
    }
    assert(labels.size() == docs.size());
    for (auto& label : labels) {
        auto it = oldLabelsToNew.find(label);
        if (it == oldLabelsToNew.end()) {
            continue;
        }
        label = it->second;
    }

    std::unordered_map<size_t, size_t> clusterLabels;
    TClusters clusters;
    for (size_t i = 0; i < docSize; ++i) {
        const size_t clusterId = labels[i];
        auto it = clusterLabels.find(clusterId);
        if (it == clusterLabels.end()) {
            size_t newLabel = clusters.size();
            clusterLabels[clusterId] = newLabel;
            clusters.emplace_back(newLabel);
            clusters[newLabel].AddDocument(docs[i]);
        } else {
            clusters[it->second].AddDocument(docs[i]);
        }
    }
    return clusters;
}

// SLINK: https://sites.cs.ucsb.edu/~veronika/MAE/summary_SLINK_Sibson72.pdf
std::vector<size_t> TSlinkClustering::ClusterBatch(
    const std::vector<TDbDocument>::const_iterator begin,
    const std::vector<TDbDocument>::const_iterator end,
    const std::unordered_map<tg::EEmbeddingKey, float>& embeddingKeysWeights
) {
    const size_t docSize = std::distance(begin, end);
    assert(docSize != 0);

    Eigen::MatrixXf distances = CalcDistances(begin, end, embeddingKeysWeights);

    if (Config.use_timestamp_moving()) {
        ApplyTimePenalty(begin, docSize, distances);
    }

    // Prepare 3 arrays
    std::vector<size_t> labels(docSize);
    for (size_t i = 0; i < docSize; i++) {
        labels[i] = i;
    }
    std::vector<size_t> nn(docSize);
    std::vector<float> nnDistances(docSize);
    for (size_t i = 0; i < docSize; i++) {
        Eigen::Index minJ;
        nnDistances[i] = distances.row(i).minCoeff(&minJ);
        nn[i] = minJ;
    }

    // Cluster meta
    std::vector<size_t> clusterSizes(docSize);
    std::vector<TClusterSiteNames> clusterSiteNames(docSize);
    auto it = begin;
    for (size_t i = 0; i < docSize; i++) {
        clusterSizes[i] = 1;
        if (Config.ban_same_hosts()) {
            clusterSiteNames[i].insert(it->SiteName);
            ++it;
        }
    }
    assert(!Config.ban_same_hosts() || it == end);

    // Main linking loop
    float prevStepMinDistance = 0.0f;
    for (size_t level = 0; level + 1 < docSize; ++level) {
        // Calculate minimal distance
        auto minDistanceIt = std::min_element(nnDistances.begin(), nnDistances.end());
        const size_t minI = std::distance(nnDistances.begin(), minDistanceIt);
        const size_t minJ = nn[minI];
        const float minDistance = *minDistanceIt;
        ENSURE(prevStepMinDistance <= minDistance, "SLINK non-decreasing distance invariant failed");
        prevStepMinDistance = minDistance;
        if (minDistance > Config.small_threshold()) {
            break;
        }

        const size_t firstClusterSize = clusterSizes[minI];
        const size_t secondClusterSize = clusterSizes[minJ];
        const size_t newClusterSize = firstClusterSize + secondClusterSize;
        const bool isAcceptableSize = IsNewClusterSizeAcceptable(newClusterSize, minDistance, Config);
        const bool hasSameSource = Config.ban_same_hosts() && HasSameSource(clusterSiteNames[minI], clusterSiteNames[minJ]);
        if (!isAcceptableSize || hasSameSource) {
            nnDistances[minI] = INF_DISTANCE;
            nnDistances[minJ] = INF_DISTANCE;
            distances(minJ, minI) = INF_DISTANCE;
            distances(minI, minJ) = INF_DISTANCE;
            for (size_t k = 0; k < static_cast<size_t>(distances.rows()); k++) {
                if (k == minI || k == minJ) {
                    continue;
                }
                float iDistance = distances(minI, k);
                float jDistance = distances(minJ, k);
                if (iDistance < nnDistances[minI]) {
                    nnDistances[minI] = iDistance;
                    nn[minI] = k;
                }
                if (jDistance < nnDistances[minJ]) {
                    nnDistances[minJ] = jDistance;
                    nn[minJ] = k;
                }
            }
            continue;
        }

        // Link minJ to minI
        for (size_t i = 0; i < docSize; i++) {
            if (labels[i] == minJ || labels[i] == labels[minJ]) {
                labels[i] = minI;
            }
        }

        clusterSizes[minI] = newClusterSize;
        clusterSizes[minJ] = newClusterSize;
        if (Config.ban_same_hosts()) {
            clusterSiteNames[minI].insert(clusterSiteNames[minJ].begin(), clusterSiteNames[minJ].end());
        }

        // Update distance matrix and nearest neighbors
        nnDistances[minI] = INF_DISTANCE;
        for (size_t k = 0; k < static_cast<size_t>(distances.rows()); k++) {
            if (k == minI || k == minJ) {
                continue;
            }
            float newDistance = std::min(distances(minJ, k), distances(minI, k));
            distances(minI, k) = newDistance;
            distances(k, minI) = newDistance;
            if (newDistance < nnDistances[minI]) {
                nnDistances[minI] = newDistance;
                nn[minI] = k;
            }
            if (nn[k] == minJ || nn[k] == minI) {
                nnDistances[k] = newDistance;
                nn[k] = minI;
            }
        }

        // Remove minJ row and column from distance matrix
        nnDistances[minJ] = INF_DISTANCE;
        for (size_t i = 0; i < static_cast<size_t>(distances.rows()); i++) {
            distances(minJ, i) = INF_DISTANCE;
            distances(i, minJ) = INF_DISTANCE;
        }
    }

    return labels;
}

Eigen::MatrixXf TSlinkClustering::CalcDistances(
    const std::vector<TDbDocument>::const_iterator begin,
    const std::vector<TDbDocument>::const_iterator end,
    const std::unordered_map<tg::EEmbeddingKey, float>& embeddingKeysWeights) const
{
    const size_t docSize = std::distance(begin, end);
    assert(docSize != 0);

    Eigen::MatrixXf finalDistances = Eigen::MatrixXf::Zero(docSize, docSize);
    for (const auto& [embeddingKey, weight] : embeddingKeysWeights) {
        const size_t embSize = begin->Embeddings.at(embeddingKey).size();
        Eigen::MatrixXf points(docSize, embSize);
        std::vector<size_t> badPoints;
        std::vector<TDbDocument>::const_iterator docsIt = begin;

        for (size_t i = 0; i < docSize; ++i) {
            std::vector<float> embedding = docsIt->Embeddings.at(embeddingKey);

            Eigen::Map<Eigen::VectorXf, Eigen::Unaligned> docVector(embedding.data(), embedding.size());
            if (std::abs(docVector.norm() - 0.0) > 0.00000001) {
                points.row(i) = docVector / docVector.norm();
            } else {
                badPoints.push_back(i);
            }
            docsIt++;
        }

        // Assuming points are on unit sphere
        // Normalize to [0.0, 1.0]
        Eigen::MatrixXf distances(docSize, docSize);
        distances = (-((points * points.transpose()).array() + 1.0f) / 2.0f + 1.0f) * weight;
        distances += distances.Identity(docSize, docSize) * weight;
        for (size_t index : badPoints) {
            distances.row(index) = Eigen::VectorXf::Ones(docSize) * weight;
            distances.col(index) = Eigen::VectorXf::Ones(docSize) * weight;
        }
        distances = distances.cwiseMax(0.0f);
        finalDistances += distances;
    }

    return finalDistances;
}
