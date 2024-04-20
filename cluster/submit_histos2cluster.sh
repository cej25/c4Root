#!/bin/bash
LISTFILE="/lustre/gamma/s100_nearline/cluster/make_histos_file_list.txt"
NFILES=$(cat ${LISTFILE} | wc -l)

declare -a size
while IFS= read -r line
do
    size+=($line)
done < "$LISTFILE"

echo "Making histograms from " $NFILES " trees."

sbatch -J s100_histos \
--cpus-per-task=2 \
--mem-per-cpu=8G \
--array=1-$NFILES \
-o /lustre/gamma/s100_nearline/cluster/logs/s100_make_histos_%A_%a.out.log \
-e /lustre/gamma/s100_nearline/cluster/logs/s100_make_histos_%A_%e.err.log \
-- /lustre/gamma/s100_nearline/cluster/histos_launcher.sh

unset size