#pragma once

#include "enum.pb.h"

#include <string>
#include <unordered_map>
#include <nlohmann_json/json.hpp>

class TAgencyRating {
public:
    TAgencyRating() = default;
    explicit TAgencyRating(const std::string& fileName, bool setMinAsUnk = false) {
        Load(fileName, setMinAsUnk);
    }

    void Load(const std::string& fileName, bool setMinAsUnk = false);
    double ScoreUrl(const std::string& url) const;

private:
     std::unordered_map<std::string, double> Records;
     double UnkRating = 0.000015;
};

enum ERatingType {
    RT_LOG = 0,
    RT_RAW = 1,
    RT_ONE = 2
};

class TAlexaAgencyRating {
public:
    TAlexaAgencyRating() = default;
    explicit TAlexaAgencyRating(const std::string& fileName) {
        Load(fileName);
    }

    void Load(const std::string& fileName);
    double ScoreUrl(const std::string& host, tg::ELanguage language, ERatingType type, double shift) const;
    double GetRawRating(const std::string& host) const;
    double GetCountryShare(const std::string& host, const std::string& code) const;

private:
     std::unordered_map<std::string, double> RawRating;
     std::unordered_map<std::string, std::unordered_map<std::string, double>> CountryShare;
     double UnkRating = 0.1;
};
