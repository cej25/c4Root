#!/bin/bash

# Check a name is provided
if [ $# -eq 0 ]; then
        echo "Please provide a name for your experiment! i.e. > create_experiment.sh sXXX"
        exit 1
fi


if [ -d "config/$1" ]; then
    echo "Experiment "$1" already exists. Aborting."
    exit 1
fi


# Create directories and files
mkdir -p config/"$1"
mkdir -p config/"$1"/{AIDA,bplast,fatima,frs,germanium}
mkdir -p config/"$1"/frs/Gates
find config/default/frs/Gates/ -type f -name "*default" -exec cp {} "config/"$1"/frs/Gates" \;
mkdir -p config/"$1"/fatima/Gates
find config/default/fatima/Gates/ -type f -name "*default" -exec cp {} "config/"$1"/fatima/Gates" \;
cp "config/default/general_setup.h" "config/"$1"/"
cp "config/default/correlations.dat" "config/"$1"/"

mkdir -p unpack/exps/"$1"
touch unpack/exps/"$1"/"$1".spec

touch macros/despec/"$1"_online.C

echo "Experiment '"$1"' created successfully."
