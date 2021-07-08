#!/bin/bash

models_list=(
    "https://www.dropbox.com/s/19ebsncdo5hpmks/lang_detect.ftz"
    "https://www.dropbox.com/s/hunjpdv4vmj33zm/ru_cat_v5.ftz"
    "https://www.dropbox.com/s/v9pc3ftmxqg7rve/en_cat_v5.ftz"
    "https://www.dropbox.com/s/rohop0gt3zr2msm/ru_vectors_v3.bin"
    "https://www.dropbox.com/s/e8ewd75cc3yagim/en_vectors_v3.bin"
    "https://www.dropbox.com/s/zkpndrd579u92ht/pagerank_rating.txt"
    "https://www.dropbox.com/s/1p03s5hw9fuzryp/alexa_rating_4_fixed.txt"
    "https://www.dropbox.com/s/sqw2xkxqd99tnmy/lang_detect_v10.ftz"
    "https://www.dropbox.com/s/hlwywuu0soou3sj/ru_idfs.txt"
    "https://www.dropbox.com/s/xaz8npm8ihy08k9/ru_tfidf_tsvd_embedder.pt"
)

cd models
for url in ${models_list[@]}; do
    echo $url
    wget -nc -q  $url
done
