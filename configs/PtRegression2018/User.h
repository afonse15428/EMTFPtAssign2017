// *** Default user settings ***
TString EOS_DIR_NAME = "root://cms-xrd-global.cern.ch//store/user/eyigitba/emtf/L1Ntuples/Run3/crabOut/SingleMu/SingleMuFlatOneOverPt1To1000GeV_combined/";

TString in_dir = "";
std::vector<TString> SingleMu_files = {
"EMTFNtuple_hadded_posEndcap_v1_1.root",
"EMTFNtuple_hadded_negEndcap_v1_1.root",
"EMTFNtuple_hadded_negEndcap_v1_2.root",
"EMTFNtuple_hadded_posEndcap_v1_2.root",
"EMTFNtuple_hadded_negEndcap_v1_3.root",
"EMTFNtuple_hadded_posEndcap_v1_3.root",
"EMTFNtuple_hadded_negEndcap_v1_4.root",
"EMTFNtuple_hadded_posEndcap_v1_4.root",
"EMTFNtuple_hadded_negEndcap_v1_6.root",
"EMTFNtuple_hadded_posEndcap_v1_6.root",
"EMTFNtuple_hadded_negEndcap_v1_7.root",
"EMTFNtuple_hadded_posEndcap_v1_7.root" 
};

TString ZeroBias_files[1] = {
	"NTuple_ZeroBias_FlatNtuple_2019_01_09_ZeroBias_PU50_Sep24_FW.root"
};
const int USESingleMu = SingleMu_files.size();//# of SM files to use
const int USEZerobias = 0;//# of ZB files to use
TString OUT_DIR_NAME  = "./";
TString OUT_FILE_NAME = "PtRegressionOutput";  // Name base for output ROOT file

namespace PtRegression2018_cfg {

  inline void ConfigureUser( const TString USER ) {

    std::cout << "\nConfiguring PtRegression2018 code for user " << USER << std::endl;

    in_dir = "";
    if (USER == "dildick") {
      OUT_DIR_NAME = "./";
    }
    if (USER == "mdecaro") {
      OUT_DIR_NAME = "./";
    }

  } // End function: inline void ConfigureUser()

} // End namespace PtRegression2018_cfg
