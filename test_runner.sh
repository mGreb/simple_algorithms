#!/bin/bash

if [ $# -lt 1 ]; then
    echo "Usage: $0 <executable> [test_case_dir]"
    echo "Example: $0 ./my_program tests/"
    exit 1
fi

PROGRAM="$1"
TEST_DIR="${2:-tests}"

if [ ! -f "$PROGRAM" ]; then
    echo "Error: Executable '$PROGRAM' not found."
    exit 1
fi

if [ ! -d "$TEST_DIR" ]; then
    echo "Error: Test directory '$TEST_DIR' not found."
    exit 1
fi

echo "Testing executable: $PROGRAM"
echo "Test directory: $TEST_DIR"
echo "------------------------"

# Loop through all input files in the test directory
for input_file in "$TEST_DIR"/input_*.txt; do
    if [ ! -f "$input_file" ]; then
        echo "Warning: No input files found in $TEST_DIR (expected format: input_*.txt)."
        exit 1
    fi

    # Extract test number (supports input_1.txt → output_1.txt OR input_001.txt → output_001.txt)
    test_num=$(basename "$input_file" | sed 's/input_//; s/\.txt//')
    output_file="$TEST_DIR/output_${test_num}.txt"

    if [ ! -f "$output_file" ]; then
        echo "Error: Expected output file '$output_file' not found for input '$input_file'."
        continue
    fi

    # Run the program and capture output
    actual_output=$(cat "$input_file" | "$PROGRAM")
    expected_output=$(cat "$output_file")

    # Trim whitespace for comparison
    actual_trimmed=$(echo "$actual_output" | xargs)
    expected_trimmed=$(echo "$expected_output" | xargs)

    # Compare results
    if [ "$actual_trimmed" = "$expected_trimmed" ]; then
        echo "✅ Test $test_num: PASSED"
    else
        echo "❌ Test $test_num: FAILED"
        echo "   Input:    $(cat "$input_file")"
        echo "   Expected: '$expected_trimmed'"
        echo "   Got:      '$actual_trimmed'"
    fi
done
