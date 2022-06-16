// *** User *** ///
const TString USER = "dildick";  // Settings applied in User.h
//const TString USER = "Matthew";

// *** Events to process *** //
const int MAX_TR = 4500000;  // MAX # of events for training
const int MAX_TE = 4500000;  // MAX # of events for test

const int REPORT_EVT = 100000;  // Report every Nth event during processing

// *** Track-building settings *** //
const int MODE      = 15;     // Track mode to build - settings applied in Modes.h
const bool USE_RPC  = false;   // Use RPC hits in track-building
const bool USE_GEM  = false;   // Use GEM hits in track-building
const bool BIT_COMP = true;   // Use bit-compressed versions of input variables
const std::vector<int> CSC_MASK = {};  // Mask CSC LCTs in these stations
const std::vector<int> RPC_MASK = {};  // Mask RPC hits in these stations
const double FORCE_MODE_FRAC = 1.00; // Fraction of muons that are forced to be the mode selected vs truely are the mode selected

// *** Target and event weights      ***//
// *** Can put multiple choices here ***//
// Choose "pt", "invPt", "logPt", and/or "charge"
const std::vector<TString> TARG_VARS = {"logPt"}; // Default "invPt"
// Choose "no", "invPt", and/or "invPtSq"
const std::vector<TString> EVT_WGTS  = {"invlog2Pt"}; // Default "invPt" "invPt0p5" "invlog2Pt"

// *** EMTF tracks *** //
const bool USE_EMTF_CSC = true;  // Only use CSC LCTs from the original EMTF track
const std::vector<int> EMTF_MODES = {15, 14, 13, 12, 11, 10, 9, 7, 6, 5, 3};  // Modes of saved EMTF tracks

// *** Output data options *** //
const bool SPEC_VARS = false;  // When generating final XMLs, set to "false" to leave out spectators

// *** High-pT muons *** //
const double PTMIN_TR =    1.;  // Minimum GEN pT for training
const double PTMAX_TR =  1000.;  // Maximum GEN pT for training
const double PTMAX_TRG = 256.;  // Maximum trigger pT assigned
const bool CLEAN_HI_PT = true;  // Remove showering high-pT mode 15 tracks from training
