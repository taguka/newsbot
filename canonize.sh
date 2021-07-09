#!/bin/bash

./build/newsbot --mode json --input test/data/canonical_input.json > test/data/canonical_annotation.json
./build/newsbot --mode top --input test/data/canonical_input.json > test/data/canonical_top.json
