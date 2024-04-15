#!/bin/bash
#SBATCH --job-name=fatimacfd_152long
#SBATCH --nodes=1
#SBATCH --partition=main
#SBATCH --ntasks-per-node=1
#SBATCH --cpus-per-task=1
#SBATCH --time=00:30:00
#SBATCH --output=output_fatimacfd_152long_%j.log
#SBATCH -a 1-252%252


export FAIRROOTPATH=/cvmfs/fairsoft.gsi.de/debian10/fairroot/v18.8.0_fs_nov22p1
export SIMPATH=/cvmfs/fairsoft.gsi.de/debian10/fairsoft/nov22p1
export UCESB_DIR=/lustre/gamma/jlarsson/ucesb
export UCESB_BASE_DIR=/lustre/gamma/jlarsson/ucesb

# Se up environment variables for ROOT, FAIRROOT, and other dependencies
export ROOTSYS="${FAIRROOTPATH}"
export PATH="${FAIRROOTPATH}/bin:${SIMPATH}/bin:${UCESB_DIR}/bin:${PATH}"
export LD_LIBRARY_PATH="${FAIRROOTPATH}/lib:${SIMPATH}/lib:${UCESB_DIR}/lib:${LD_LIBRARY_PATH}"

# Source setup scripts
. "${FAIRROOTPATH}/bin/FairRootConfig.sh"
. "${SIMPATH}/bin/thisroot.sh"
. "/lustre/gamma/jlarsson/c4code/virgobuild/config.sh"

#for some reasion thisroot.sh seems to unset some of these guys:
export FAIRROOTPATH=/cvmfs/fairsoft.gsi.de/debian10/fairroot/v18.8.0_fs_nov22p1
export SIMPATH=/cvmfs/fairsoft.gsi.de/debian10/fairsoft/nov22p1
export UCESB_DIR=/lustre/gamma/jlarsson/ucesb
export UCESB_BASE_DIR=/lustre/gamma/jlarsson/ucesb


#files=$(cat /lustre/gamma/jlarsson/c4code/macros/listoffiles.txt)

# Compile the ROOT script
#for file in $files
file="Feb19_152Eu_Th34k_$(printf "%04d" $SLURM_ARRAY_TASK_ID).lmd"
#do
echo $file

root -b -l <<EOF
gSystem->AddIncludePath("${FAIRROOTPATH}/include");
gSystem->AddIncludePath("${SIMPATH}/include");

gSystem->AddIncludePath("/lustre/gamma/jlarsson/c4code/c4Root/c4source/fatima");

gSystem->AddLinkedLibs("-L/lustre/gamma/jlarsson/c4code/virgobuild/lib -llibc4Analysis.so");  
gSystem->AddLinkedLibs("-L/lustre/gamma/jlarsson/c4code/virgobuild/lib -llibc4Data.so"); 
gSystem->AddLinkedLibs("-L/lustre/gamma/jlarsson/c4code/virgobuild/lib -llibc4MacroCompiler.so"); 
gSystem->AddLinkedLibs("-L/lustre/gamma/jlarsson/c4code/virgobuild/lib -llibc4Base.so"); 

.x /lustre/gamma/jlarsson/FebCFDTamex/run_online_fatima.C("$file")
EOF

