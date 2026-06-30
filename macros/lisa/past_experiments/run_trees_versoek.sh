#!/bin/bash

# Path to the ROOT macro
macro_path="macros/versoek_make_trees.C"

# Read list of run numbers to convert to trees
number_list="tree_numbers.txt"

# Check if file exists
if [ ! -f "$number_list" ]; then
    echo "Error: $number_list file not found!"
    exit 1
fi

if [[ "$1" == "--pattern" ]]; then
    pattern="$2"
    if [[ -n "$pattern" ]]; then
	echo "Pattern is set: $pattern"
    else
    	echo "No pattern provided"
    fi
fi

if [[ "$1" == "--run" ]]; then
    pattern=$(printf "run_%04d_" "$2")
    if [[ -n "$pattern" ]]; then
	echo "Pattern is set: $pattern"
    else
    	echo "No pattern provided"
    fi
fi

./print_subrun_numbers.sh ${pattern} > ${number_list}

echo "Filled ${number_list} with $(wc -l < "${number_list}") subruns"

# Loop over runs
while read -r number; do
    if [[ -z "$number" || "$number" =~ ^# ]]; then
        continue
    fi

    echo "Processing file number: $number"

    if [[ -n "$pattern" ]]; then

	root -l -b -q "${macro_path}(${number},\"${pattern}\")"
    else
    	root -l -b -q "${macro_path}(${number})"
    fi

    # Check the exit status
    if [ $? -ne 0 ]; then
        echo "Error: ROOT macro failed for file number ${number}"
        exit 1
    fi

done < "$number_list"

echo "All files processed successfully."
