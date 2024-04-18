#!/bin/bash
LISTFILE="/lustre/gamma/s100_nearline/cluster/hadd_file_list.txt"
NFILES=$(cat ${LISTFILE} | wc -l)

declare -a size
while IFS= read -r line
do
    size+=($line)
done < "$LISTFILE"

echo "Merging" $NFILES "histograms."

sbatch -J s100_hadd \
--mem-per-cpu=8G \
-o /lustre/gamma/s100_nearline/cluster/logs/s100_hadd_%A_%a.out.log \
-e /lustre/gamma/s100_nearline/cluster/logs/s100_hadd_%A_%e.err.log \
-- /lustre/gamma/s100_nearline/cluster/hadd_launcher.sh

unset size
