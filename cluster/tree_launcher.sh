#!/bin/bash

export FAIRROOTPATH=/cvmfs/fairsoft.gsi.de/debian11/fairroot/v18.8.0_nov22p1
export SIMPATH=/cvmfs/fairsoft.gsi.de/debian11/fairsoft/nov22p1
export UCESB_DIR=/lustre/gamma/s100_nearline/ucesb
export UCESB_BASE_DIR=/lustre/gamma/s100_nearline/ucesb

# Se up environment variables for ROOT, FAIRROOT, and other dependencies
export ROOTSYS="${FAIRROOTPATH}"
export PATH="${FAIRROOTPATH}/bin:${SIMPATH}/bin:${UCESB_DIR}/bin:${PATH}"
export LD_LIBRARY_PATH="${FAIRROOTPATH}/lib:${SIMPATH}/lib:${UCESB_DIR}/lib:${LD_LIBRARY_PATH}"

# Source setup scripts
. "${FAIRROOTPATH}/bin/FairRootConfig.sh"
. "${SIMPATH}/bin/thisroot.sh"
. "/lustre/gamma/s100_nearline/virgobuild/config.sh"

#for some reasion thisroot.sh seems to unset some of these guys:
export FAIRROOTPATH=/cvmfs/fairsoft.gsi.de/debian11/fairroot/v18.8.0_nov22p1
export SIMPATH=/cvmfs/fairsoft.gsi.de/debian11/fairsoft/nov22p1
export UCESB_DIR=/lustre/gamma/s100_nearline/ucesb
export UCESB_BASE_DIR=/lustre/gamma/s100_nearline/ucesb


LISTFILE="/lustre/gamma/s100_nearline/cluster/make_trees_file_list.txt"
NFILES=$(cat ${LISTFILE} | wc -l)
echo "Analysing" $NFILES " files"

declare -a size
while IFS= read -r line
do
    size+=($line)
done < "$LISTFILE"

index=$(($SLURM_ARRAY_TASK_ID - 1))
file="${size[index]}"

echo "Running c4!"
root -b -l <<EOF

gSystem->AddIncludePath("${FAIRROOTPATH}/include");
gSystem->AddIncludePath("${SIMPATH}/include");

gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4source.so");
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4Analysis.so");  
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4Data.so"); 
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4MacroCompiler.so"); 
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4Base.so"); 

.x /lustre/gamma/s100_nearline/cluster/s100_make_trees.C("$file")
EOF

unset size