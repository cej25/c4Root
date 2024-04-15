#!/bin/bash
#SBATCH --job-name=s100_hadd
#SBATCH --partition=main
#SBATCH --time=00:30:00
#SBATCH --output=/lustre/gamma/s100_nearline/cluster/logs/s100_hadd%j.log
##SBATCH -a 1-10
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=1
##SBATCH --cpus-per-task=2
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

# Define input and output files
input_file_list="/lustre/gamma/s100_nearline/histograms/input_files.txt"
output_file="/lustre/gamma/s100_nearline/histograms/summed_histogram.root"

# Check if the input file list exists
if [ ! -f "$input_file_list" ]; then
    echo "Error: Input file list $input_file_list not found."
    exit 1
fi

# Submit hadd job
srun hadd -f $output_file `cat $input_file_list`
