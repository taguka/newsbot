days=("21_04_2021" "22_04_2021"  "23_04_2021" "24_04_2021" "25_04_2021" "26_04_2021" "27_04_2021")
DIR=/home/aguka/Downloads
for day in ${days[@]};
do
	INPUT_DATA=$DIR/$day/input/input.json
	mkdir -p $DIR/$day/output
	OUTPUT_DATA=$DIR/$day/output/top.json
	echo $OUTPUT_DATA
	./build/newsbot top $INPUT_DATA > $OUTPUT_DATA
done
