#!/bin/bash

data_train_list=(
    "https://data-static.usercontent.dev/DataClusteringSample0107.tar.gz"
)

data_test_list=(
    "https://data-static.usercontent.dev/DataClusteringSample0410.tar.gz"
)

mkdir data
for url in ${data_train_list[@]}; do
    echo $url
    wget -qO - $url | tar -xz -C data
done

mkdir data_test
for url in ${data_test_list[@]}; do
    echo $url
    wget -qO - $url | tar -xz -C data_test
done
