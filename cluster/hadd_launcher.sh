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

# Define input and output files
LISTFILE="/lustre/gamma/s100_nearline/cluster/hadd_file_list.txt"
output_file="/lustre/gamma/s100_nearline/histograms/Au_beam_0012_summed_histograms.root"

NFILES=$(cat ${LISTFILE} | wc -l)


# Check if the input file list exists
if [ ! -f "$LISTFILE" ]; then
    echo "Error: Input file list $LISTFILE not found."
    exit 1
fi

# Submit hadd job
srun hadd -f $output_file `cat $LISTFILE`
