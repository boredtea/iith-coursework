#/bin/bash

program="$1"
filename=$(basename $program .c)
target="$filename.out"

if gcc "$program" -lm -o "$target"; then
    echo "Compiled ok."
else
    echo "Compilation Error."
    exit 1
fi

for testInput in "input_"*.txt; do
    outputName=$(echo "$testInput" | sed 's/input/progOutput/1')
    correctOutput=$(echo "$testInput" | sed 's/input/output/1')

    ./"$target" < "$testInput" > "$outputName"

    `diff -b -B -Z "$outputName" "$correctOutput" > /dev/null`
    if [ "$?" -eq 0 ]; then
	echo "Test $testInput passed."
    else
	echo "** Test $testInput failed! **"
    fi
    
done
