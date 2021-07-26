import os
import json
import copy
import argparse
from datetime import datetime

def convert(output_dir, documents_file, tops_file, nclusters):
    with open(documents_file, encoding="utf-8") as r:
        documents = json.load(r)
        documents = {doc["file_name"]: doc for doc in documents}
    with open(tops_file,encoding="utf-8") as r:
        tops = json.load(r)
    os.makedirs(output_dir, exist_ok=True)
    output= {}

    for top in tops:
        articles = []
        top = copy.deepcopy(top)
        category = top.pop("category")
        clusters = top.pop("threads")
        category = category if category != "any" else "main"
        for cluster in clusters:
            article = documents[cluster.pop("articles")[0]]
            article["date"] = datetime.utcfromtimestamp(article["timestamp"]).strftime("%e %b %H:%M")
            article['text']=''
            article['category'] = category
            articles.append(article)
        if nclusters:
            articles = articles[:nclusters]
        output[category]=articles

    with open(os.path.join(output_dir,'output.json'), "w", encoding="utf-8") as fp:
        json.dump(output, fp, ensure_ascii=False)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument('--output-dir', type=str, default="output")
    parser.add_argument('--documents-file', type=str, required=True)
    parser.add_argument('--tops-file', type=str, required=True)
    parser.add_argument('--nclusters', type=int, default=5)
    args = parser.parse_args()
    convert(**vars(args))

