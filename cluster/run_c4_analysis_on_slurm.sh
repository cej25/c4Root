#!/bin/bash
#SBATCH --job-name=s100_make_trees
#SBATCH --partition=main
#SBATCH --time=02:00:00
#SBATCH --output=s100_make_trees%j.log
#SBATCH -a 1-10
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1


export FAIRROOTPATH=/cvmfs/fairsoft.gsi.de/debian10/fairroot/v18.8.0_fs_nov22p1
export SIMPATH=/cvmfs/fairsoft.gsi.de/debian10/fairsoft/nov22p1
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
export FAIRROOTPATH=/cvmfs/fairsoft.gsi.de/debian10/fairroot/v18.8.0_fs_nov22p1
export SIMPATH=/cvmfs/fairsoft.gsi.de/debian10/fairsoft/nov22p1
export UCESB_DIR=/lustre/gamma/s100_nearline/ucesb
export UCESB_BASE_DIR=/lustre/gamma/s100_nearline/ucesb


#files=$(cat /lustre/gamma/s100_nearline/macros/file_list.txt)

# Compile the ROOT script
#for file in $files
file="Au_beam_0010_00$(printf "%02d" $SLURM_ARRAY_TASK_ID).root"

echo $file

root -b -l <<EOF
gSystem->AddIncludePath("${FAIRROOTPATH}/include");
gSystem->AddIncludePath("${SIMPATH}/include");

gSystem->AddIncludePath("/lustre/gamma/jlarsson/c4code/c4Root/c4source/fatima");

gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4source.so");
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4Analysis.so");  
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4Data.so"); 
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4MacroCompiler.so"); 
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4Base.so"); 

.x /lustre/gamma/s100_nearline/macros/s100_make_trees.C("$file")
EOF


