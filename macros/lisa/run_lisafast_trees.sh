#!/bin/bash

# Path to the ROOT macro
macro_path="/home/lisa/programs/c4/fast_c4Root/macros/lisa/lisafast_make_trees_number.C"

# Text file containing the LMD filenames
number_list="/home/lisa/programs/c4/fast_c4Root/macros/lisa/lisafast_tree_files.txt"

# Check that the list exists
if [[ ! -f "$number_list" ]]; then
    echo "Error: $number_list file not found!"
    exit 1
fi

# Check that the macro exists
if [[ ! -f "$macro_path" ]]; then
    echo "Error: ROOT macro $macro_path not found!"
    exit 1
fi

# Count processed files
processed=0

# Read filenames from the list
while IFS= read -r lmdname || [[ -n "$lmdname" ]]; do

    lmdname="${lmdname%$'\r'}"

    # Skip empty lines and comments
    [[ -z "$lmdname" || "$lmdname" =~ ^[[:space:]]*# ]] && continue

    echo "========================================"
    echo "Processing file: $lmdname"
    echo "========================================"

    # Run the ROOT macro with the input filename
    root -l -b -q "${macro_path}(\"${lmdname}\")"

    # Check the exit status
    status=$?
    if [[ $status -ne 0 ]]; then
        echo "Error: ROOT macro failed for $lmdname (exit code $status)"
        exit 1
    fi

    ((processed++))

done < "$number_list"

echo "========================================"
echo "All files processed successfully."
echo "Total files processed: $processed"
echo "========================================"

