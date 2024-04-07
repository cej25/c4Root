#!/bin/bash

## Setup environment
#fairroot etc
export UCESB_DIR=/u/cjones/ucesb
export SIMPATH=/cvmfs/fairsoft.gsi.de/debian10/fairsoft/nov22p1
export FAIRROOTPATH=/cvmfs/fairsoft.gsi.de/debian10/fairroot/v18.8.0_fs_nov22p1
source $SIMPATH/bin/thisroot.sh
source $FAIRROOTPATH/bin/FairRootConfig.sh
export FAIRROOTPATH=/cvmfs/fairsoft.gsi.de/debian10/fairroot/v18.8.0_fs_nov22p1
source /lustre/gamma/s100_nearline/build/config.sh

## Read in list of files
LISTFILE="/lustre/gamma/s100_nearline/cluster/file_list.txt"

## Count number of files
NFILES=$(cat ${LISTFILE} | wc -l)
echo "Analysing" $NFILES "Files"

## Read names from list file
declare -a array
while IFS= read -r line
do
    array+=($line)
done < "$LISTFILE"

echo "Array is $SLURM_ARRAY_TASK_ID"
part=(  "${array[@]:$SLURM_ARRAY_TASK_ID:1}")

echo "Running c4!"
root -b s100_make_trees(${part[*]}).C