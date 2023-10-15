# c4Root

c4Root will be a FairRoot-based R3BRoot-inspired software for the experimental analysis of DESPEC nuclear physics experiments.

Contact: c.jones@gsi.de

Please note this software is currently in its infancy. The general architecture will be restructurd into slightly less nonsense, please forgive the mess for now. At present a couple of macros can be used for demonstration purposes; these are located in the ucesb directory. 

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
> make -j6
```

```
> cd ../c4Root/unpack/exps/
> make s452 -j 10
> cd ../../macros/despec/
> root -l run_ge_online.C
```

This will generate a root file with unpacked Germanium (FEBEX) data from the S452 experiment in a tree. It will also generate some "online" uncalibrated and calibrated Energy spectra per detector.

NOTE: Before use, please check run_ge_online.C to adjust your filepath as may be necessary, as well as the port used for the HTTP server for online monitoring.

