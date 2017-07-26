#include "step1_LJMet80x_pedro_Full2016_July2017.cc"

void testStep1(){
  
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki/nominal/MuonEG_RRG/MuonEG_RRG_1.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki/nominal/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_1.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki/nominal/DoubleEG_RRG/DoubleEG_RRG_25.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki/nominal/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_1.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki/nominal/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_117.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki/nominal/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_79.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki/nominal/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_96.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki/nominal/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_70.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki/nominal/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_105.root";
//   TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_4_rizki/nominal/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8/TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_113.root";
// 	TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki/nominal/BprimeBprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8/BprimeBprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_1.root";
// 	TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_saveLooseMC_2017_3_7_rizki/nominal/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_combined/DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_combined_2.root";
	TString inputFile="root://cmseos.fnal.gov//store/user/lpcljm/LJMet80x_3lepTT_Full2016_Moriond17_reMiniAOD_nuBTVSF_modMETfilt_2017_2_24_rizki/nominal/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_1.root";

  TString outputFile="test.root";
//   TString outputFile="TT_TuneCUETP8M2T4_13TeV-powheg-pythia8_1.root";
  
  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");
  
  step1 t(inputFile,outputFile);
  t.Loop();
}


