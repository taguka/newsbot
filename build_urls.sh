INPUT_DATA="$1"
OUTPUT_DIR="$2"

TOPS_DATA=$(mktemp)
JSON_DATA=$(mktemp)


./newsbot json ${INPUT_DATA} > ${JSON_DATA}
echo "convert json done..."
./newsbot top ${INPUT_DATA} > ${TOPS_DATA}
echo "top done..."

python3 merge.py \
    --documents-file ${JSON_DATA} \
    --tops-file ${TOPS_DATA} \
    --output-dir ${OUTPUT_DIR} 
echo "merge done..."
echo "end"

