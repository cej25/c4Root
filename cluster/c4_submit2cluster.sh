#!/bin/bash
## Read list of files
LISTFILE="/lustre/gamma/s100_nearline/cluster/file_list.txt"
declare -a size
while IFS= read -r line
do
    size+=($line)
done < "$LISTFILE"

## Submit job

sbatch -p long -J despec_c4_s100_trees -D /lustre/gamma/s100_nearline/c4Root -o logs/c4_%A_%a_trees.out.log -e logs/c4_%A_%a_trees.err.log \
    --time=7-00:00:00 --mem-per-cpu=4G \
    --array=0-${#size[@]}:1 -- /lustre/gamma/s100_nearline/cluster/c4_trees_launcher.sh

    unset size