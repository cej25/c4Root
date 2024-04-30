#!/bin/bash
LISTFILE="/lustre/gamma/s100_nearline/cluster/make_trees_file_list.txt"
NFILES=$(cat ${LISTFILE} | wc -l)

declare -a size
while IFS= read -r line
do
    size+=($line)
    echo $line
done < "$LISTFILE"

echo "Making trees from " $NFILES " lmd files."

sbatch -J s100_trees \
--cpus-per-task=2 \
--mem-per-cpu=8G \
--array=1-$NFILES \
-o /lustre/gamma/s100_nearline/cluster/logs/s100_make_trees_%A_%a.out.log \
-e /lustre/gamma/s100_nearline/cluster/logs/s100_make_trees_%A_%e.err.log \
-- /lustre/gamma/s100_nearline/cluster/tree_launcher.sh

unset size
