# c4Root

c4Root is a FairRoot-based software inspired by [R3BRoot](https://github.com/R3BRootGroup/R3BRoot) for the experimental analysis of HISPEC/DESPEC nuclear physics experiments.

Contact: calum.e.jones@gmail.com

## Development

- Calum Eoin Jones
- Johan Emil Linnestad Larsson
- Jeroen Peter Bormans
- Nicolas James Hubbard
- Elisa Maria Gandolfo
- Kathrin Wimmer

Documentation on the usage of this software is currently in progress. Basic instructions are otherwise provided below.

## Requirements

- [ucesb](https://git.chalmers.se/expsubphys/ucesb.git)
- [FairRoot](https://github.com/FairRootGroup/FairRoot), version 18.2.1 or later
- ROOT compatible with the selected FairRoot installation
- FairLogger
- VMC
- CMake 3.11 or later

### FairSoft

FairSoft is **not a direct requirement of c4Root**, and c4Root does not require the `SIMPATH` environment variable.

Some FairRoot installations, including centrally provided or CVMFS installations, may themselves have been built against FairSoft. These installations remain fully supported. In this case, load the appropriate FairRoot/software environment before configuring c4Root; c4Root will use the ROOT, FairLogger, VMC, and other dependencies associated with that FairRoot installation.

In other words, FairSoft may still be part of the software stack used by a particular FairRoot installation, but c4Root does not depend on or search for FairSoft directly.

## UCESB setup

Before compiling c4Root, build the empty UCESB unpacker:

```bash
cd /path/to/ucesb
make empty -j
```

Individual experimental unpackers can be built later as required.

## Compiling c4Root

Set the FairRoot and UCESB locations:

```bash
export FAIRROOTPATH=/path/to/fairroot
export UCESB_DIR=/path/to/ucesb
```

If you are using a centrally provided FairRoot environment, for example through CVMFS or a laboratory software installation, load that environment first and then set `FAIRROOTPATH` as appropriate.

Clone and build c4Root:

```bash
git clone https://github.com/cej25/c4Root.git
cd c4Root

mkdir build
cd build

cmake ..
cmake --build . -j
```

After compilation, load the generated c4Root environment:

```bash
. ./config.sh
```

The generated configuration uses the ROOT and other dependencies associated with the FairRoot installation selected during configuration.

## Testing the installation

To test that c4Root has been compiled and configured successfully:

```bash
cd ../macros/tests
root -l -b first_tests.C
```

You should see some event processing followed by a summary of subevents.

After this, you can try a real experimental configuration. For example:

```bash
cd ../../unpack/exps
make s100 -j

cd ../../macros/despec
root -l -b s100_online.C
```

The `{experiment}_online.C` macro can read data from an LMD file or from a stream/transport server. It then performs a series of tasks on the data, such as unpacking, calibrations, analysis, correlations, and plotting spectra in histograms.

Each task can be configured for online or offline operation. Heavy-duty tasks such as analysis and correlations may be more suitable for nearline/offline analysis, where data are read from an LMD file.

If `SetOnline` is `false`, data at that task level can be written to a tree in a `.root` file defined in the macro. Individual subsystems and tasks can be disabled easily by commenting out components that are not required.

Histograms may be monitored online using a `THttpServer` and viewed through the configured port.