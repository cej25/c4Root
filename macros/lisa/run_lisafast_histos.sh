#!/bin/bash

# Path to the ROOT macro
macro_path="/home/lisa/programs/c4/fast_c4Root/macros/lisa/lisafast_histos_number.C"

# Text file containing the ROOT filenames
number_list="/home/lisa/programs/c4/fast_c4Root/macros/lisa/lisafast_histo_files.txt"

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

processed=0

# Read filenames from the list
while IFS= read -r rootname || [[ -n "$rootname" ]]; do

    # Remove Windows carriage return if present
    rootname="${rootname%$'\r'}"

    # Skip empty lines and comments
    [[ -z "$rootname" || "$rootname" =~ ^[[:space:]]*# ]] && continue

    echo "========================================"
    echo "Processing file: $rootname"
    echo "========================================"

    root -l -b -q "${macro_path}(\"${rootname}\")"

    status=$?

    if [[ $status -ne 0 ]]; then
        echo "Error: ROOT macro failed for $rootname (exit code $status)"
        exit 1
    fi

    ((processed++))

done < "$number_list"

echo "========================================"
echo "All files processed."
echo "Total files processed: $processed"
echo "========================================"