INPUT_DATA="$1"
OUTPUT_DIR="$2"

TOPS_DATA=$(mktemp)
JSON_DATA=$(mktemp)


./build/newsbot json ${INPUT_DATA} > ${JSON_DATA}
./build/newsbot top ${INPUT_DATA} > ${TOPS_DATA}

python3 merge.py \
    --documents-file ${JSON_DATA} \
    --tops-file ${TOPS_DATA} \
    --output-dir ${OUTPUT_DIR} \


