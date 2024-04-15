#!/bin/bash
#SBATCH --job-name=s100_tree_maker
#SBATCH --partition=main
#SBATCH --time=00:30:00
#SBATCH --output=/lustre/gamma/s100_nearline/cluster/logs/s100_make_trees%j.log
#SBATCH -a 1-10
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=2
#SBATCH --mem-per-cpu=8GB


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


#files=$(cat /lustre/gamma/s100_nearline/macros/file_list.txt)

# Compile the ROOT script
#for file in $files
file="/lustre/gamma/dryrunmarch24/ts/Au_beam_0010_00$(printf "%02d" $SLURM_ARRAY_TASK_ID).lmd"


echo $file

root -b -l <<EOF
gSystem->AddIncludePath("${FAIRROOTPATH}/include");
gSystem->AddIncludePath("${SIMPATH}/include");

gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4source.so");
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4Analysis.so");  
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4Data.so"); 
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4MacroCompiler.so"); 
gSystem->AddLinkedLibs("-L/lustre/gamma/s100_nearline/virgobuild/lib -llibc4Base.so"); 

.x /lustre/gamma/s100_nearline/cluster/s100_nearline_histograms.C("$file")
EOF
