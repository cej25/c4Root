#!/bin/bash

# Path to the ROOT macro
macro_path="e_shiyan_make_trees_numbers.C"

# Read list of run numbers to convert to trees
number_list="shiyan_tree_setting20.txt"

# Check if file exists
if [ ! -f "$number_list" ]; then
    echo "Error: $number_list file not found!"
    exit 1
fi

# Loop over runs
while read -r number; do
    if [[ -z "$number" || "$number" =~ ^# ]]; then
        continue
    fi

    echo "Processing file number: $number"

    root -l -b -q "${macro_path}(${number})"

    # Check the exit status
    if [ $? -ne 0 ]; then
        echo "Error: ROOT macro failed for file number ${number}"
        exit 1
    fi

done < "$number_list"

echo "All files processed successfully."

