# c4Root

c4Root is a FairRoot-based software inspired by R3BRoot [https://github.com/R3BRootGroup/R3BRoot] for the experimental analysis of HISPEC/DESPEC nuclear physics experiments.

Contact: calum.e.jones@gmail.com

Development: 
* Calum Eoin Jones
* Johan Emil Linnestad Larsson
* Jeroen Peter Bormans
* Nicolas James Hubbard
* Elisa Maria Gandolfo
* Kathrin Wimmer

Documentation on the usage of this software is currently in progress. Basic instructions are otherwise provided below. 

Requirements:
* ucesb, specifically: https://git.chalmers.se/expsubphys/ucesb.git
* FairSoft: https://github.com/FairRootGroup/FairSoft
* FairRoot: https://github.com/FairRootGroup/FairRoot
* cmake v13.3+

The latest prod version of both FairSoft and FairRoot can be found on the lx-pool GSI computers.

To compile:
```
> export SIMPATH=/path/to/fairsoft
> export FAIRROOTPATH=/path/to/fairroot
> export UCESB_DIR=/path/to/ucesb
> git clone https://github.com/cej25/c4Root.git
> mkdir build
> cd build
> cmake ../c4Root
> . ./config.sh
> make -j
```

```
> cd ../c4Root/unpack/exps/
> make s100 -j
> cd ../../macros/despec/
> root -l -b s100_online.C
```

The {experiment}_online.C macro can read data from an LMD file or a stream/transport server. It will then perform a series of tasks on this data such as unpacking, calibrations, analysis, correlations and plotting spectra in histograms. 

Each "task" can be set online or offline. Heavy duty tasks such as analysis and correlations may be more suitable to a Nearline/Offline analysis, where data is read from an LMD. If SetOnline is "false", any data at this task level will be written to a tree in a .root file defined in the macro. Individual subsystems and/or tasks can be turned off easily, by commmenting out anything undesirable. 

Histograms may be monitored online at a THttpServer, viewed at the defined port. 


