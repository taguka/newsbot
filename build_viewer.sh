TEMPLATES_DIR="$1"
OUTPUT_DIR="$2"
INPUT_DATA="$3"
TOPS_DATA=$(mktemp)
JSON_DATA=$(mktemp)


./build/newsbot json ${INPUT_DATA} > ${JSON_DATA}
./build/newsbot top ${INPUT_DATA} --print_top_debug_info > ${TOPS_DATA}

python3 viewer/convert.py \
    --documents-file ${JSON_DATA} \
    --tops-file ${TOPS_DATA} \
    --templates-dir ${TEMPLATES_DIR} \
    --output-dir ${OUTPUT_DIR} \


