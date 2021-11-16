# EMTFPtAssign2017
EMTF code for pT LUT training (Run II-RunIII)

## Setup
EMTFPtAssign2017 is designed to be run on cms-lpc in a `CMSSW_10_6_1_patch2` environemnt. Since it will also need to pull files from EOS, it also assumes a grid-certificate has been authenticated. If you fork the repository you can setup your environment and new branch using,
```
cd ~/nobackup/
cmsrel CMSSW_10_6_1_patch2
cd CMSSW_10_6_1_patch2/src

cmsenv
voms-proxy-init --voms cms

git clone git@github.com:<your github username>/EMTFPtAssign2017.git
git checkout -b <your_branch_name>
git push origin <your_branch_name>
```

## Submitting Training Jobs
EMTFPtAssign2017 has been built with a python wrapper that will submit jobs to `condor` automatically. This is done through the `condor/submitJobs.py` script. Using this wrapper you can call,
```
cd condor
python submitJobs.py <options>
```
where `<options>` contains a `--isRun2` or `--isRun3` flags, `--interactiveRun`, which set of training variables, which target variable, eta values, training settings, etc. All options can be seen by running `python submitJobs.py --help`.

*Note: Always run `python submitJobs.py <options> --inerativeRun` before submitting jobs to condor.*

## Structure
EMTFPtAssign2017 is build using ROOT TMVA with a python wrapper for submitting jobs to condor. 

The main training program is done using `PtRegressionRun3Prep.C`. This program allows for labeling different variables as either spectator, training, or target. The spectator variables will not be used in training but will be written to the final ROOT file for evaluation. The training variables will be used by the BDT for training. The target variable is the varialbe the BDT is trying to learn to evaluate. There are also options for loss functions where `BDTG_AWB_Sq` is the least squares loss function currently being used.

*Note: Training variables in PtRegressionRun3Prep.C must match what is written in allowedTrainingVars* 

Each event will be looped over and each track in an event will be either marked for training or testing. Tracks in the training set are used by the BDT regression algorithm to generate the Look Up Tables (LUTs) which will then evaluate the tracks in the testing set which they have not been trained on. This allows the BDT's performance to be evaluated for each training. 

Additional configuration settings are stored in `configs/PtRegression2018` directory which control how the NTuples are parsed, input files are assigned, and standard global variables are initialized. 

Lastly, the python wrapper is discussed in the pervious section which is stored in `condor` directory. 

*Note: macros and macros_Rice2020 are deprecated and plotting is now done using the `EMTF_BDT_PerformancePlotter` GitHub Repository* 

## Inputs to Training
The BDT in `PtRegressionRun3Prep.C` assumes the input file has been prepared in a FlatNTuple generated by `EMTFAnalyzer/NTupleMaker` GitHub Repository and hadded into one input file stored on EOS. There are multiple modes that are currently implemented in `EMTFAnalyzer/NTupleMaker` such as FlatNtupleMCRun2, FlatNtupleMCRun2GEM, FlatNtupleMCRun3, and FlatNtupleMCRun3GEM. If you want to switch between NTuples you must change the `treeString` variable in the `PtRegressionRun3Prep.C` training program. 

## Outputs of Training
The BDT will output a `weights.xml` LUT and a `PtRegression.root` file. Th `weights.xml` file will contain a large XML LUT that can eventually be reformatted and loaded in to CMSSW for evaluation of rate. `PtRegression.root` will contain the TrainTree of all tracks used in training and a TestTree of all tracks that have been evaulated using the LUT but not been trained on.

## Current Training
The settings currently used for training are to use a least squares loss function, log_2(pt) target variable, and the training variables stored in `Run2Variables.py`. Additional spectator variables have been added to evaluate performance under specific situations. 

The BDT also applies weights based on track characteristics and generator information. For example, a muon with a pT of 5GeV will have more weight than a muon with pT of 200GeV since it is more important to correctly assign 5GeV than to assign 200GeV +- 5GeV. 

Lastly, Bit Compression has been added into the training to more accurately represent the performance in firmware where the address space is limited ot 30 bits. 

## Loading LUT into CMSSW
The `weights.xml` file is not in the correct format to load into CMSSW directly. Once you have run on all emtf modes you can run `copyLutsToL1TMuonEndcap.py` to generate LUT that are compatible with CMSSW which will be split into 11 directories (1 per mode) with 400 xml files in each direcotry. These can then be loaded into CMSSW under `L1Trigger/L1TMuonEndCap/data/` as outlined in https://github.com/cms-sw/cmssw/pull/36094.

## TRK_hit_ids variable
The variable TRK_hit_ids has been added as a spectator variable and is generated as an 8 bit number that contains which CSCs and RPCs were used in the building of a particular track. The first 4 bits hold information about ME1, ME2, ME3, ME4 and the last four bits hold information about RPC1, RPC2, RPC3, RPC4, where a 1 indicates that a hit in the detector was used and a 0 indicates there was no hit in the detector used in the track. An all CSC track for mode 15 would be 11110000 and an all RPC track for mode 15 would be 00001111. 
 
