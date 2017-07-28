#define step1_cxx
#include "fakerate_2lep_ptEta_pedro.h"
#include <fstream>
#include <iostream>     // std::cout
#include <algorithm>    // std::sort
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom.h>
#include <TRandom3.h>
#include <sstream>
#include <string>
#include <vector>
#include "step1_LJMet80x_pedro_Full2016_July2017.h"
// #include "fakerate_3lep_rizki.h" //added by rizki
//#include "fakerate_3lep_ptEta_rizki.h" //added by rizki


using namespace std;

// ----------------------------------------------------------------------------
// DEBUG printout switches
// ----------------------------------------------------------------------------
bool DEBUG = false;
bool DEBUGleptons = false;
bool DEBUGjets = false;
bool DEBUGddbkg = false;
bool DEBUGddbkgScan = false;
bool DEBUGTriggers = false;

// ----------------------------------------------------------------------------
// Define functions
// ----------------------------------------------------------------------------

bool comparepair( const std::pair<double,int> a, const std::pair<double,int> b) { return a.first > b.first; }

TRandom3 Rand;

const double MTOP  = 173.5;
const double MW    = 80.4; 

bool step1::applySF(bool& isTagged, float tag_SF, float tag_eff){
  
  bool newTag = isTagged;
  if (tag_SF == 1) return newTag; //no correction needed 

  //throw die
  float coin = Rand.Uniform(1.);    

  if(tag_SF > 1){  // use this if SF>1

    if( !isTagged ) {

      //fraction of jets that need to be upgraded
      float mistagPercent = (1.0 - tag_SF) / (1.0 - (tag_SF/tag_eff) );

      //upgrade to tagged
      if( coin < mistagPercent ) {newTag = true;}
    }

  }else{  // use this if SF<1
      
    //downgrade tagged to untagged
    if( isTagged && coin > tag_SF ) {newTag = false;}

  }

  return newTag;
}

// ----------------------------------------------------------------------------
// MAIN EVENT LOOP
// ----------------------------------------------------------------------------

void step1::Loop() 
{

  // ----------------------------------------------------------------------------
  // Turn on input tree branches
  // ----------------------------------------------------------------------------

   if (inputTree == 0) return;
   
   inputTree->SetBranchStatus("*",0);

   //Event info

   inputTree->SetBranchStatus("event_CommonCalc",1);
   inputTree->SetBranchStatus("run_CommonCalc",1);
   inputTree->SetBranchStatus("lumi_CommonCalc",1);
   inputTree->SetBranchStatus("nPV_singleLepCalc",1);
   inputTree->SetBranchStatus("nTrueInteractions_singleLepCalc",1);
   inputTree->SetBranchStatus("MCWeight_singleLepCalc",1);

   inputTree->SetBranchStatus("isTHBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTHTH_TpTpCalc",1);
   inputTree->SetBranchStatus("isBWBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZBW_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZTH_TpTpCalc",1);
   inputTree->SetBranchStatus("isTZTZ_TpTpCalc",1);
   inputTree->SetBranchStatus("isBHTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBHBH_TpTpCalc",1);
   inputTree->SetBranchStatus("isTWTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZTW_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZBH_TpTpCalc",1);
   inputTree->SetBranchStatus("isBZBZ_TpTpCalc",1);
   inputTree->SetBranchStatus("NLeptonDecays_TpTpCalc",1);
   
   //triggers
   inputTree->SetBranchStatus("vsSelMCTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelMCTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelMCTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelMCTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelTriggersEl_singleLepCalc",1);
   inputTree->SetBranchStatus("vsSelTriggersMu_singleLepCalc",1);
   inputTree->SetBranchStatus("viSelTriggersMu_singleLepCalc",1);
   
   //electrons
   inputTree->SetBranchStatus("elPt_singleLepCalc",1);
   inputTree->SetBranchStatus("elEta_singleLepCalc",1);
   inputTree->SetBranchStatus("elPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("elEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("elMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elRelIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elMVAValue_singleLepCalc",1);
   inputTree->SetBranchStatus("elDxy_singleLepCalc",1);
   inputTree->SetBranchStatus("elDZ_singleLepCalc",1);
   inputTree->SetBranchStatus("elCharge_singleLepCalc",1);
   inputTree->SetBranchStatus("elDEtaSCTkAtVtx_singleLepCalc",1);
   inputTree->SetBranchStatus("elDPhiSCTkAtVtx_singleLepCalc",1);
   inputTree->SetBranchStatus("elDR03TkSumPt_singleLepCalc",1);
   inputTree->SetBranchStatus("elSihih_singleLepCalc",1);
   inputTree->SetBranchStatus("elHoE_singleLepCalc",1);
   inputTree->SetBranchStatus("elEcalPFClusterIso_singleLepCalc",1);
   inputTree->SetBranchStatus("elHcalPFClusterIso_singleLepCalc",1);
   
   //muons
   inputTree->SetBranchStatus("muPt_singleLepCalc",1);
   inputTree->SetBranchStatus("muEta_singleLepCalc",1);
   inputTree->SetBranchStatus("muPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("muEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("muMiniIso_singleLepCalc",1);
   inputTree->SetBranchStatus("muRelIso_singleLepCalc",1);
   inputTree->SetBranchStatus("muIsTight_singleLepCalc",1);
   inputTree->SetBranchStatus("muDxy_singleLepCalc",1);
   inputTree->SetBranchStatus("muDz_singleLepCalc",1);
   inputTree->SetBranchStatus("muCharge_singleLepCalc",1);

   //missing et
   inputTree->SetBranchStatus("corr_met_singleLepCalc",1);
   inputTree->SetBranchStatus("corr_met_phi_singleLepCalc",1);

   // genParticles
   inputTree->SetBranchStatus("genPt_singleLepCalc",1);
   inputTree->SetBranchStatus("genEta_singleLepCalc",1);
   inputTree->SetBranchStatus("genPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("genEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("genStatus_singleLepCalc",1);
   inputTree->SetBranchStatus("genID_singleLepCalc",1);
   inputTree->SetBranchStatus("genMotherID_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetPt_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetEta_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("genJetEnergy_singleLepCalc",1);

   //boosted truth
   inputTree->SetBranchStatus("HadronicVHtPt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtEta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtPhi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtEnergy_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtID_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD0E_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD1E_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("HadronicVHtD2E_JetSubCalc",1);

   //jets
   inputTree->SetBranchStatus("AK4JetFlav_singleLepCalc",1);
//    inputTree->SetBranchStatus("theJetPFlav_JetSubCalc",1);
   inputTree->SetBranchStatus("AK4JetPt_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetEta_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetPhi_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetEnergy_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBDisc_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBTag_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBTag_bSFup_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBTag_bSFdn_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBTag_lSFup_singleLepCalc",1);
   inputTree->SetBranchStatus("AK4JetBTag_lSFdn_singleLepCalc",1);
   inputTree->SetBranchStatus("theJetAK8Pt_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Eta_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Phi_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Mass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8Energy_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau1_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau2_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8NjettinessTau3_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8PrunedMass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8PrunedMassWtagUncerts_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SoftDropMass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8PrunedTau21Tag_JetSubCalc",1);

   inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVMSF_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVM_bSFdn_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVM_bSFup_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVM_lSFdn_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetNCSVM_lSFup_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetPt_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetEta_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetPhi_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetMass_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetCSV_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetBTag_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetIndex_JetSubCalc",1);
   inputTree->SetBranchStatus("theJetAK8SDSubjetSize_JetSubCalc",1);
   
   //top
   inputTree->SetBranchStatus("ttbarMass_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topEnergy_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topEta_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topMass_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topPhi_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topPt_TTbarMassCalc",1);
   inputTree->SetBranchStatus("topID_TTbarMassCalc",1);
   
   //LHE weights
   inputTree->SetBranchStatus("LHEweightids_singleLepCalc",1);
   inputTree->SetBranchStatus("LHEweights_singleLepCalc",1);

  // ----------------------------------------------------------------------------
  // Create output tree and define branches
  // ----------------------------------------------------------------------------
   
   // OUTPUT FILE
   outputFile->cd();
   TTree *outputTree = new TTree("ljmet","ljmet");

   int NJetsWtagged_0p6;
   bool isPassDilepton;    	    
   int isEE;
   int isEM;
   int isMM;
   //   int isMMM;
   int isTT;
   int isTL;
   int isLT;
   int isLL;
   //   int isTLL;
   //int isLTL;
   //int isLLT;
   //int isLLL;
   float leadWJetPtak8;
   float topPtWeightPast400;
   float topPtWeightHighPt;
   float minDR_leadAK8otherAK8;
   std::vector<float> minDR_lepJets;
   std::vector<float> deltaR_lepBJets;
   std::vector<float> minDR_lepBJets;
   std::vector<float> deltaR_lepClosestJet;
   std::vector<float> PtRelLepClosestJet;
   
   float Mll_OS; //inv mass of opposite sign same flavor leps (high pt lep pairs as priority)
   float Mll_SS;
   // std::vector<float> MllOS_allComb; // all permutation between OS trilep pairs 
   // float MllOS_allComb_min; 
   // float MllOS_allComb_max; 
   float Mll; //inv mass top 2 leptons

   float JetSF_pTNbwflat;
   float JetSFup_pTNbwflat;
   float JetSFdn_pTNbwflat;
   float JetSFupwide_pTNbwflat;
   float JetSFdnwide_pTNbwflat;
   std::vector<float> leadWJetPtak8_shifts;
   std::vector<float> pdfWeights;
   std::vector<float> theJetAK8SoftDropMass_JetSubCalc_PtOrdered;
   std::vector<float> theJetAK8NjettinessTau3_JetSubCalc_PtOrdered;
   std::vector<float> theJetAK8MaxSubCSV_JetSubCalc_PtOrdered;

//DEBUG - start
   std::vector<float> AllLeptonElPt_PtOrdered;
   std::vector<float> AllLeptonElEta_PtOrdered;
   std::vector<float> AllLeptonElPhi_PtOrdered;
   std::vector<float> AllLeptonElEnergy_PtOrdered;
   std::vector<float> AllLeptonElMiniIso_PtOrdered;
   std::vector<int> AllLeptonElFlavor_PtOrdered;
   std::vector<int> AllLeptonElIsTight_PtOrdered;
   int AllLeptonElCount_PtOrdered;

   std::vector<float> AllLeptonMuPt_PtOrdered;
   std::vector<float> AllLeptonMuEta_PtOrdered;
   std::vector<float> AllLeptonMuPhi_PtOrdered;
   std::vector<float> AllLeptonMuEnergy_PtOrdered;
   std::vector<float> AllLeptonMuMiniIso_PtOrdered;
   std::vector<int> AllLeptonMuFlavor_PtOrdered;
   std::vector<int> AllLeptonMuIsTight_PtOrdered;
   int AllLeptonMuCount_PtOrdered;

//DEBUG - end

   std::vector<float> AllLeptonPt_PtOrdered;
   std::vector<float> AllLeptonEta_PtOrdered;
   std::vector<float> AllLeptonPhi_PtOrdered;
   std::vector<float> AllLeptonEnergy_PtOrdered;
   std::vector<float> AllLeptonMiniIso_PtOrdered;
   std::vector<int> AllLeptonFlavor_PtOrdered;
   std::vector<int> AllLeptonIsTight_PtOrdered;
   std::vector<int> AllLeptonCharge_PtOrdered;
   std::vector<int> AllLeptonIdx_PtOrdered;
   int AllLeptonCount_PtOrdered;
   
   //PtOrderedOnly
   std::vector<float> AllLeptonElPt_PtOrderedOnly;
   std::vector<float> AllLeptonElEta_PtOrderedOnly;
   std::vector<float> AllLeptonElPhi_PtOrderedOnly;
   std::vector<float> AllLeptonElEnergy_PtOrderedOnly;
   std::vector<float> AllLeptonElMiniIso_PtOrderedOnly;
   std::vector<int> AllLeptonElFlavor_PtOrderedOnly;
   std::vector<int> AllLeptonElIsTight_PtOrderedOnly;

   std::vector<float> AllLeptonMuPt_PtOrderedOnly;
   std::vector<float> AllLeptonMuEta_PtOrderedOnly;
   std::vector<float> AllLeptonMuPhi_PtOrderedOnly;
   std::vector<float> AllLeptonMuEnergy_PtOrderedOnly;
   std::vector<float> AllLeptonMuMiniIso_PtOrderedOnly;
   std::vector<int> AllLeptonMuFlavor_PtOrderedOnly;
   std::vector<int> AllLeptonMuIsTight_PtOrderedOnly;

   std::vector<float> AllLeptonPt_PtOrderedOnly;
   std::vector<float> AllLeptonEta_PtOrderedOnly;
   std::vector<float> AllLeptonPhi_PtOrderedOnly;
   std::vector<float> AllLeptonEnergy_PtOrderedOnly;
   std::vector<float> AllLeptonMiniIso_PtOrderedOnly;
   std::vector<int> AllLeptonFlavor_PtOrderedOnly;
   std::vector<int> AllLeptonIsTight_PtOrderedOnly;
   std::vector<int> AllLeptonCharge_PtOrderedOnly;
   std::vector<int> AllLeptonIdx_PtOrderedOnly;

   //PtOrderedOnly_top2 (of default) -> re-sorting top 2 of default ordering.
   std::vector<float> AllLeptonElPt_PtOrderedOnly_top2;
   std::vector<float> AllLeptonElEta_PtOrderedOnly_top2;
   std::vector<float> AllLeptonElPhi_PtOrderedOnly_top2;
   std::vector<float> AllLeptonElEnergy_PtOrderedOnly_top2;
   std::vector<float> AllLeptonElMiniIso_PtOrderedOnly_top2;
   std::vector<int> AllLeptonElFlavor_PtOrderedOnly_top2;
   std::vector<int> AllLeptonElIsTight_PtOrderedOnly_top2;

   std::vector<float> AllLeptonMuPt_PtOrderedOnly_top2;
   std::vector<float> AllLeptonMuEta_PtOrderedOnly_top2;
   std::vector<float> AllLeptonMuPhi_PtOrderedOnly_top2;
   std::vector<float> AllLeptonMuEnergy_PtOrderedOnly_top2;
   std::vector<float> AllLeptonMuMiniIso_PtOrderedOnly_top2;
   std::vector<int> AllLeptonMuFlavor_PtOrderedOnly_top2;
   std::vector<int> AllLeptonMuIsTight_PtOrderedOnly_top2;

   std::vector<float> AllLeptonPt_PtOrderedOnly_top2;
   std::vector<float> AllLeptonEta_PtOrderedOnly_top2;
   std::vector<float> AllLeptonPhi_PtOrderedOnly_top2;
   std::vector<float> AllLeptonEnergy_PtOrderedOnly_top2;
   std::vector<float> AllLeptonMiniIso_PtOrderedOnly_top2;
   std::vector<int> AllLeptonFlavor_PtOrderedOnly_top2;
   std::vector<int> AllLeptonIsTight_PtOrderedOnly_top2;
   std::vector<int> AllLeptonCharge_PtOrderedOnly_top2;
   std::vector<int> AllLeptonIdx_PtOrderedOnly_top2;

   std::vector<float> TightLeptonPt_PtOrdered;
   std::vector<float> TightLeptonEta_PtOrdered;
   std::vector<float> TightLeptonPhi_PtOrdered;
   std::vector<float> TightLeptonEnergy_PtOrdered;
   std::vector<float> TightLeptonMiniIso_PtOrdered;
   std::vector<int> TightLeptonFlavor_PtOrdered;
   std::vector<int> TightLeptonCharge_PtOrdered;
   std::vector<int> TightLeptonIdx_PtOrdered;
   
//    std::vector<int> theJetBTagBuggy_JetSubCalc_PtOrdered;
   std::vector<int> theJetAK8Wmatch_JetSubCalc_PtOrdered;
   std::vector<int> NJetsWtagged_0p6_shifts;
   std::vector<float> ddBkgWeights;
//    std::vector<pair<float,float> > ddBkgWeights_scan;
//    std::vector<map<float,float> > ddBkgWeights_scan;
   std::vector<float> ddBkgWeights_scan;
   std::vector<float> ddBkgWeights_scan_muFR;
   std::vector<float> ddBkgWeights_scan_elFR;
   
   //int MCPastTrigger_trilep;
   //int DataPastTrigger_trilep;
   int MCPastTrigger_dilep;
   int DataPastTrigger_dilep;
   int MCPastTrigger_dilepDZ4runH;
   int DataPastTrigger_dilepDZ4runH;
   int MCPastTrigger_dilepHT;
   int DataPastTrigger_dilepHT;

   outputTree->Branch("event_CommonCalc",&event_CommonCalc,"event_CommonCalc/I");
   outputTree->Branch("run_CommonCalc",&run_CommonCalc,"run_CommonCalc/I");
   outputTree->Branch("lumi_CommonCalc",&lumi_CommonCalc,"lumi_CommonCalc/I");
   outputTree->Branch("nPV_singleLepCalc",&nPV_singleLepCalc,"nPV_singleLepCalc/I");
   outputTree->Branch("nTrueInteractions_singleLepCalc",&nTrueInteractions_singleLepCalc,"nTrueInteractions_singleLepCalc/I");
   outputTree->Branch("isElectron",&isElectron,"isElectron/I");
   outputTree->Branch("isMuon",&isMuon,"isMuon/I");
   outputTree->Branch("MCPastTrigger",&MCPastTrigger,"MCPastTrigger/I");
   outputTree->Branch("MCPastTriggerAlt",&MCPastTriggerAlt,"MCPastTriggerAlt/I");
   outputTree->Branch("DataPastTrigger",&DataPastTrigger,"DataPastTrigger/I");
   outputTree->Branch("DataPastTriggerAlt",&DataPastTriggerAlt,"DataPastTriggerAlt/I");
   outputTree->Branch("isTHBW_TpTpCalc",&isTHBW_TpTpCalc,"isTHBW_TpTpCalc/O");
   outputTree->Branch("isTHTH_TpTpCalc",&isTHTH_TpTpCalc,"isTHTH_TpTpCalc/O");
   outputTree->Branch("isBWBW_TpTpCalc",&isBWBW_TpTpCalc,"isBWBW_TpTpCalc/O");
   outputTree->Branch("isTZBW_TpTpCalc",&isTZBW_TpTpCalc,"isTZBW_TpTpCalc/O");
   outputTree->Branch("isTZTH_TpTpCalc",&isTZTH_TpTpCalc,"isTZTH_TpTpCalc/O");
   outputTree->Branch("isTZTZ_TpTpCalc",&isTZTZ_TpTpCalc,"isTZTZ_TpTpCalc/O");
   outputTree->Branch("isBHTW_TpTpCalc",&isBHTW_TpTpCalc,"isBHTW_TpTpCalc/O");
   outputTree->Branch("isBHBH_TpTpCalc",&isBHBH_TpTpCalc,"isBHBH_TpTpCalc/O");
   outputTree->Branch("isTWTW_TpTpCalc",&isTWTW_TpTpCalc,"isTWTW_TpTpCalc/O");
   outputTree->Branch("isBZTW_TpTpCalc",&isBZTW_TpTpCalc,"isBZTW_TpTpCalc/O");
   outputTree->Branch("isBZBH_TpTpCalc",&isBZBH_TpTpCalc,"isBZBH_TpTpCalc/O");
   outputTree->Branch("isBZBZ_TpTpCalc",&isBZBZ_TpTpCalc,"isBZBZ_TpTpCalc/O");
   outputTree->Branch("NLeptonDecays_TpTpCalc",&NLeptonDecays_TpTpCalc,"NLeptonDecays_TpTpCalc/I");
   outputTree->Branch("MCWeight_singleLepCalc",&MCWeight_singleLepCalc,"MCWeight_singleLepCalc/D");
   outputTree->Branch("renormWeights",&renormWeights);
   outputTree->Branch("pdfWeights",&pdfWeights);
   outputTree->Branch("JetSF_pTNbwflat",&JetSF_pTNbwflat,"JetSF_pTNbwflat/F");
   outputTree->Branch("JetSFup_pTNbwflat",&JetSFup_pTNbwflat,"JetSFup_pTNbwflat/F");
   outputTree->Branch("JetSFdn_pTNbwflat",&JetSFdn_pTNbwflat,"JetSFdn_pTNbwflat/F");
   outputTree->Branch("JetSFupwide_pTNbwflat",&JetSFupwide_pTNbwflat,"JetSFupwide_pTNbwflat/F");
   outputTree->Branch("JetSFdnwide_pTNbwflat",&JetSFdnwide_pTNbwflat,"JetSFdnwide_pTNbwflat/F");
   outputTree->Branch("pileupWeight",&pileupWeight,"pileupWeight/F");
   outputTree->Branch("pileupWeightUp",&pileupWeightUp,"pileupWeightUp/F");
   outputTree->Branch("pileupWeightDown",&pileupWeightDown,"pileupWeightDown/F");
   outputTree->Branch("TrigEffAltWeight",&TrigEffAltWeight,"TrigEffAltWeight/F");
   outputTree->Branch("TrigEffWeight",&TrigEffWeight,"TrigEffWeight/F");
   outputTree->Branch("TrigEffWeightUncert",&TrigEffWeightUncert,"TrigEffWeightUncert/F");
   outputTree->Branch("isoSF",&isoSF,"isoSF/F");
   outputTree->Branch("lepIdSF",&lepIdSF,"lepIdSF/F");
   outputTree->Branch("EGammaGsfSF",&EGammaGsfSF,"EGammaGsfSF/F");
   outputTree->Branch("MuTrkSF",&MuTrkSF,"MuTrkSF/F");

   outputTree->Branch("isPassDilepton",&isPassDilepton,"isPassDilepton/O");
   outputTree->Branch("isEE",&isEE,"isEE/I");
   outputTree->Branch("isEM",&isEM,"isEM/I");
   outputTree->Branch("isMM",&isMM,"isMM/I");
   //   outputTree->Branch("isMMM",&isMMM,"isMMM/I");
   outputTree->Branch("isTT",&isTT,"isTT/I");
   outputTree->Branch("isTL",&isTL,"isTL/I");
   outputTree->Branch("isLT",&isLT,"isLT/I");
   outputTree->Branch("isLL",&isLL,"isLL/I");
   //   outputTree->Branch("isTLL",&isTLL,"isTLL/I");
   //outputTree->Branch("isLTL",&isLTL,"isLTL/I");
   //outputTree->Branch("isLLT",&isLLT,"isLLT/I");
   //outputTree->Branch("isLLL",&isLLL,"isLLL/I");
   
   outputTree->Branch("MCPastTrigger",&MCPastTrigger,"MCPastTrigger/I");
   outputTree->Branch("MCPastTriggerAlt",&MCPastTriggerAlt,"MCPastTriggerAlt/I");
   outputTree->Branch("DataPastTrigger",&DataPastTrigger,"DataPastTrigger/I");
   outputTree->Branch("DataPastTriggerAlt",&DataPastTriggerAlt,"DataPastTriggerAlt/I");

   outputTree->Branch("MCPastTrigger_dilep",&MCPastTrigger_dilep,"MCPastTrigger_dilep/I");
   outputTree->Branch("DataPastTrigger_dilep",&DataPastTrigger_dilep,"DataPastTrigger_dilep/I");

   outputTree->Branch("MCPastTrigger_dilepDZ4runH",&MCPastTrigger_dilepDZ4runH,"MCPastTrigger_dilepDZ4runH/I");
   outputTree->Branch("DataPastTrigger_dilepDZ4runH",&DataPastTrigger_dilepDZ4runH,"DataPastTrigger_dilepDZ4runH/I");

   outputTree->Branch("MCPastTrigger_dilepHT",&MCPastTrigger_dilepHT,"MCPastTrigger_dilepHT/I");
   outputTree->Branch("DataPastTrigger_dilepHT",&DataPastTrigger_dilepHT,"DataPastTrigger_dilepHT/I");

   //   outputTree->Branch("MCPastTrigger_trilep",&MCPastTrigger_trilep,"MCPastTrigger_trilep/I");
   // outputTree->Branch("DataPastTrigger_trilep",&DataPastTrigger_trilep,"DataPastTrigger_trilep/I");


   outputTree->Branch("ttbarMass_TTbarMassCalc",&ttbarMass_TTbarMassCalc,"ttbarMass_TTbarMassCalc/D");
   outputTree->Branch("corr_met_singleLepCalc",&corr_met_singleLepCalc,"corr_met_singleLepCalc/D");
   outputTree->Branch("corr_met_phi_singleLepCalc",&corr_met_phi_singleLepCalc,"corr_met_phi_singleLepCalc/D");
   outputTree->Branch("leptonPt_singleLepCalc",&leptonPt_singleLepCalc,"leptonPt_singleLepCalc/F");
   outputTree->Branch("leptonEta_singleLepCalc",&leptonEta_singleLepCalc,"leptonEta_singleLepCalc/F");
   outputTree->Branch("leptonPhi_singleLepCalc",&leptonPhi_singleLepCalc,"leptonPhi_singleLepCalc/F");
   outputTree->Branch("leptonEnergy_singleLepCalc",&leptonEnergy_singleLepCalc,"leptonEnergy_singleLepCalc/F");
   outputTree->Branch("leptonMiniIso_singleLepCalc",&leptonMiniIso_singleLepCalc,"leptonMiniIso_singleLepCalc/F");
   outputTree->Branch("leptonRelIso_singleLepCalc",&leptonRelIso_singleLepCalc,"leptonRelIso_singleLepCalc/F");
   outputTree->Branch("leptonDxy_singleLepCalc",&leptonDxy_singleLepCalc,"leptonDxy_singleLepCalc/F");
   outputTree->Branch("leptonDz_singleLepCalc",&leptonDz_singleLepCalc,"leptonDz_singleLepCalc/F");
   outputTree->Branch("leptonCharge_singleLepCalc",&leptonCharge_singleLepCalc,"leptonCharge_singleLepCalc/I");
   outputTree->Branch("elTrigPresel_singleLepCalc",&elTrigPresel_singleLepCalc,"elTrigPresel_singleLepCalc/I");

//DEBUG-start
   outputTree->Branch("AllLeptonElPt_PtOrdered",&AllLeptonElPt_PtOrdered);
   outputTree->Branch("AllLeptonElEta_PtOrdered",&AllLeptonElEta_PtOrdered);
   outputTree->Branch("AllLeptonElPhi_PtOrdered",&AllLeptonElPhi_PtOrdered);
   outputTree->Branch("AllLeptonElEnergy_PtOrdered",&AllLeptonElEnergy_PtOrdered);
   outputTree->Branch("AllLeptonElMiniIso_PtOrdered",&AllLeptonElMiniIso_PtOrdered);
   outputTree->Branch("AllLeptonElFlavor_PtOrdered",&AllLeptonElFlavor_PtOrdered);
   outputTree->Branch("AllLeptonElIsTight_PtOrdered",&AllLeptonElIsTight_PtOrdered);
   outputTree->Branch("AllLeptonElCount_PtOrdered",&AllLeptonElCount_PtOrdered,"AllLeptonElCount_PtOrdered/I");

   outputTree->Branch("AllLeptonElPt_PtOrderedOnly",&AllLeptonElPt_PtOrderedOnly);
   outputTree->Branch("AllLeptonElEta_PtOrderedOnly",&AllLeptonElEta_PtOrderedOnly);
   outputTree->Branch("AllLeptonElPhi_PtOrderedOnly",&AllLeptonElPhi_PtOrderedOnly);
   outputTree->Branch("AllLeptonElEnergy_PtOrderedOnly",&AllLeptonElEnergy_PtOrderedOnly);
   outputTree->Branch("AllLeptonElMiniIso_PtOrderedOnly",&AllLeptonElMiniIso_PtOrderedOnly);
   outputTree->Branch("AllLeptonElFlavor_PtOrderedOnly",&AllLeptonElFlavor_PtOrderedOnly);
   outputTree->Branch("AllLeptonElIsTight_PtOrderedOnly",&AllLeptonElIsTight_PtOrderedOnly);

   outputTree->Branch("AllLeptonElPt_PtOrderedOnly_top2",&AllLeptonElPt_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonElEta_PtOrderedOnly_top2",&AllLeptonElEta_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonElPhi_PtOrderedOnly_top2",&AllLeptonElPhi_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonElEnergy_PtOrderedOnly_top2",&AllLeptonElEnergy_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonElMiniIso_PtOrderedOnly_top2",&AllLeptonElMiniIso_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonElFlavor_PtOrderedOnly_top2",&AllLeptonElFlavor_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonElIsTight_PtOrderedOnly_top2",&AllLeptonElIsTight_PtOrderedOnly_top2);

   outputTree->Branch("AllLeptonMuPt_PtOrdered",&AllLeptonMuPt_PtOrdered);
   outputTree->Branch("AllLeptonMuEta_PtOrdered",&AllLeptonMuEta_PtOrdered);
   outputTree->Branch("AllLeptonMuPhi_PtOrdered",&AllLeptonMuPhi_PtOrdered);
   outputTree->Branch("AllLeptonMuEnergy_PtOrdered",&AllLeptonMuEnergy_PtOrdered);
   outputTree->Branch("AllLeptonMuMiniIso_PtOrdered",&AllLeptonMuMiniIso_PtOrdered);
   outputTree->Branch("AllLeptonMuFlavor_PtOrdered",&AllLeptonMuFlavor_PtOrdered);
   outputTree->Branch("AllLeptonMuIsTight_PtOrdered",&AllLeptonMuIsTight_PtOrdered);
   outputTree->Branch("AllLeptonMuCount_PtOrdered",&AllLeptonMuCount_PtOrdered,"AllLeptonMuCount_PtOrdered/I");

   outputTree->Branch("AllLeptonMuPt_PtOrderedOnly",&AllLeptonMuPt_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuEta_PtOrderedOnly",&AllLeptonMuEta_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuPhi_PtOrderedOnly",&AllLeptonMuPhi_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuEnergy_PtOrderedOnly",&AllLeptonMuEnergy_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuMiniIso_PtOrderedOnly",&AllLeptonMuMiniIso_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuFlavor_PtOrderedOnly",&AllLeptonMuFlavor_PtOrderedOnly);
   outputTree->Branch("AllLeptonMuIsTight_PtOrderedOnly",&AllLeptonMuIsTight_PtOrderedOnly);

   outputTree->Branch("AllLeptonMuPt_PtOrderedOnly_top2",&AllLeptonMuPt_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonMuEta_PtOrderedOnly_top2",&AllLeptonMuEta_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonMuPhi_PtOrderedOnly_top2",&AllLeptonMuPhi_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonMuEnergy_PtOrderedOnly_top2",&AllLeptonMuEnergy_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonMuMiniIso_PtOrderedOnly_top2",&AllLeptonMuMiniIso_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonMuFlavor_PtOrderedOnly_top2",&AllLeptonMuFlavor_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonMuIsTight_PtOrderedOnly_top2",&AllLeptonMuIsTight_PtOrderedOnly_top2);
//DEBUG-end

   outputTree->Branch("AllLeptonPt_PtOrdered",&AllLeptonPt_PtOrdered);
   outputTree->Branch("AllLeptonEta_PtOrdered",&AllLeptonEta_PtOrdered);
   outputTree->Branch("AllLeptonPhi_PtOrdered",&AllLeptonPhi_PtOrdered);
   outputTree->Branch("AllLeptonEnergy_PtOrdered",&AllLeptonEnergy_PtOrdered);
   outputTree->Branch("AllLeptonMiniIso_PtOrdered",&AllLeptonMiniIso_PtOrdered);
   outputTree->Branch("AllLeptonFlavor_PtOrdered",&AllLeptonFlavor_PtOrdered);
   outputTree->Branch("AllLeptonIsTight_PtOrdered",&AllLeptonIsTight_PtOrdered);
   outputTree->Branch("AllLeptonCharge_PtOrdered",&AllLeptonCharge_PtOrdered);
   outputTree->Branch("AllLeptonCount_PtOrdered",&AllLeptonCount_PtOrdered,"AllLeptonCount_PtOrdered/I");

   outputTree->Branch("AllLeptonPt_PtOrderedOnly",&AllLeptonPt_PtOrderedOnly);
   outputTree->Branch("AllLeptonEta_PtOrderedOnly",&AllLeptonEta_PtOrderedOnly);
   outputTree->Branch("AllLeptonPhi_PtOrderedOnly",&AllLeptonPhi_PtOrderedOnly);
   outputTree->Branch("AllLeptonEnergy_PtOrderedOnly",&AllLeptonEnergy_PtOrderedOnly);
   outputTree->Branch("AllLeptonMiniIso_PtOrderedOnly",&AllLeptonMiniIso_PtOrderedOnly);
   outputTree->Branch("AllLeptonFlavor_PtOrderedOnly",&AllLeptonFlavor_PtOrderedOnly);
   outputTree->Branch("AllLeptonIsTight_PtOrderedOnly",&AllLeptonIsTight_PtOrderedOnly);
   outputTree->Branch("AllLeptonCharge_PtOrderedOnly",&AllLeptonCharge_PtOrderedOnly);

   outputTree->Branch("AllLeptonPt_PtOrderedOnly_top2",&AllLeptonPt_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonEta_PtOrderedOnly_top2",&AllLeptonEta_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonPhi_PtOrderedOnly_top2",&AllLeptonPhi_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonEnergy_PtOrderedOnly_top2",&AllLeptonEnergy_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonMiniIso_PtOrderedOnly_top2",&AllLeptonMiniIso_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonFlavor_PtOrderedOnly_top2",&AllLeptonFlavor_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonIsTight_PtOrderedOnly_top2",&AllLeptonIsTight_PtOrderedOnly_top2);
   outputTree->Branch("AllLeptonCharge_PtOrderedOnly_top2",&AllLeptonCharge_PtOrderedOnly_top2);


   outputTree->Branch("TightLeptonPt_PtOrdered",&TightLeptonPt_PtOrdered);
   outputTree->Branch("TightLeptonEta_PtOrdered",&TightLeptonEta_PtOrdered);
   outputTree->Branch("TightLeptonPhi_PtOrdered",&TightLeptonPhi_PtOrdered);
   outputTree->Branch("TightLeptonEnergy_PtOrdered",&TightLeptonEnergy_PtOrdered);
   outputTree->Branch("TightLeptonMiniIso_PtOrdered",&TightLeptonMiniIso_PtOrdered);
   outputTree->Branch("TightLeptonFlavor_PtOrdered",&TightLeptonFlavor_PtOrdered);
   outputTree->Branch("TightLeptonCharge_PtOrdered",&TightLeptonCharge_PtOrdered);


   outputTree->Branch("AK4JetPt_singleLepCalc_PtOrdered",&AK4JetPt_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetEta_singleLepCalc_PtOrdered",&AK4JetEta_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetPhi_singleLepCalc_PtOrdered",&AK4JetPhi_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetEnergy_singleLepCalc_PtOrdered",&AK4JetEnergy_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetBTag_singleLepCalc_PtOrdered",&AK4JetBTag_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetBTag_bSFup_singleLepCalc_PtOrdered",&AK4JetBTag_bSFup_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetBTag_bSFdn_singleLepCalc_PtOrdered",&AK4JetBTag_bSFdn_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetBTag_lSFup_singleLepCalc_PtOrdered",&AK4JetBTag_lSFup_singleLepCalc_PtOrdered);
   outputTree->Branch("AK4JetBTag_lSFdn_singleLepCalc_PtOrdered",&AK4JetBTag_lSFdn_singleLepCalc_PtOrdered);
   outputTree->Branch("HadronicVHtID_JetSubCalc",&HadronicVHtID_JetSubCalc);
   outputTree->Branch("HadronicVHtPt_JetSubCalc",&HadronicVHtPt_JetSubCalc);
   outputTree->Branch("HadronicVHtEta_JetSubCalc",&HadronicVHtEta_JetSubCalc);
   outputTree->Branch("HadronicVHtPhi_JetSubCalc",&HadronicVHtPhi_JetSubCalc);
   outputTree->Branch("HadronicVHtEnergy_JetSubCalc",&HadronicVHtEnergy_JetSubCalc);
   outputTree->Branch("theJetAK8Pt_JetSubCalc_PtOrdered",&theJetAK8Pt_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Eta_JetSubCalc_PtOrdered",&theJetAK8Eta_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Phi_JetSubCalc_PtOrdered",&theJetAK8Phi_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Energy_JetSubCalc_PtOrdered",&theJetAK8Energy_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8PrunedMass_JetSubCalc_PtOrdered",&theJetAK8PrunedMass_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered",&theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8SoftDropMass_JetSubCalc_PtOrdered",&theJetAK8SoftDropMass_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8MaxSubCSV_JetSubCalc_PtOrdered",&theJetAK8MaxSubCSV_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau1_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau1_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau2_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau2_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8NjettinessTau3_JetSubCalc_PtOrdered",&theJetAK8NjettinessTau3_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Wmatch_JetSubCalc_PtOrdered",&theJetAK8Wmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Tmatch_JetSubCalc_PtOrdered",&theJetAK8Tmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Zmatch_JetSubCalc_PtOrdered",&theJetAK8Zmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8Hmatch_JetSubCalc_PtOrdered",&theJetAK8Hmatch_JetSubCalc_PtOrdered);
   outputTree->Branch("theJetAK8MatchedPt_JetSubCalc_PtOrdered",&theJetAK8MatchedPt_JetSubCalc_PtOrdered);
   outputTree->Branch("genJetPt_singleLepCalc",&genJetPt_singleLepCalc);
   outputTree->Branch("genJetEta_singleLepCalc",&genJetEta_singleLepCalc);
   outputTree->Branch("genJetPhi_singleLepCalc",&genJetPhi_singleLepCalc);
   outputTree->Branch("genJetEnergy_singleLepCalc",&genJetEnergy_singleLepCalc);
   outputTree->Branch("BJetLeadPt",&BJetLeadPt,"BJetLeadPt/F");
   outputTree->Branch("BJetLeadPt_shifts",&BJetLeadPt_shifts);
   outputTree->Branch("WJetLeadPt",&WJetLeadPt,"WJetLeadPt/F");
   outputTree->Branch("WJetLeadPt_shifts",&WJetLeadPt_shifts);
   outputTree->Branch("TJetLeadPt",&TJetLeadPt,"TJetLeadPt/F");
   outputTree->Branch("TJetLeadPt_shifts",&TJetLeadPt_shifts);
   outputTree->Branch("AK4HTpMETpLepPt",&AK4HTpMETpLepPt,"AK4HTpMETpLepPt/F");
   outputTree->Branch("AK4HT",&AK4HT,"AK4HT/F");
   
   outputTree->Branch("ddBkgWeights",&ddBkgWeights);
   outputTree->Branch("ddBkgWeights_scan",&ddBkgWeights_scan);
   outputTree->Branch("ddBkgWeights_scan_muFR",&ddBkgWeights_scan_muFR);
   outputTree->Branch("ddBkgWeights_scan_elFR",&ddBkgWeights_scan_elFR);

   outputTree->Branch("NJets_singleLepCalc",&NJets_singleLepCalc,"NJets_singleLepCalc/I");
   outputTree->Branch("NJetsAK8_JetSubCalc",&NJetsAK8_JetSubCalc,"NJetsAK8_JetSubCalc/I");
   outputTree->Branch("NJetsBTagwithSF_singleLepCalc",&NJetsBTagwithSF_singleLepCalc,"NJetsBTagwithSF_singleLepCalc/I");
   outputTree->Branch("NJetsBTagwithSF_singleLepCalc_noLepCorr",&NJetsBTagwithSF_singleLepCalc_noLepCorr,"NJetsBTagwithSF_singleLepCalc_noLepCorr/I");
   outputTree->Branch("NJetsBTagwithSF_singleLepCalc_shifts",&NJetsBTagwithSF_singleLepCalc_shifts);
   outputTree->Branch("NJetsBTagwithSF_singleLepCalc_noLepCorr_shifts",&NJetsBTagwithSF_singleLepCalc_noLepCorr_shifts);
   outputTree->Branch("NJetsHtagged",&NJetsHtagged,"NJetsHtagged/I");
   outputTree->Branch("NJetsHtagged_shifts",&NJetsHtagged_shifts);
   outputTree->Branch("topPt",&topPt,"topPt/F");
   outputTree->Branch("topPtGen",&topPtGen,"topPtGen/F");
   outputTree->Branch("topMass",&topMass,"topMass/F");
   outputTree->Branch("minMleppBjet",&minMleppBjet,"minMleppBjet/F");
   outputTree->Branch("minMleppBjet_shifts",&minMleppBjet_shifts);
   outputTree->Branch("minMleppJet",&minMleppJet,"mixnMleppJet/F");
   outputTree->Branch("genTopPt",&genTopPt,"genTopPt/F");
   outputTree->Branch("genAntiTopPt",&genAntiTopPt,"genAntiTopPt/F");
   outputTree->Branch("topPtWeight",&topPtWeight,"topPtWeight/F");
   outputTree->Branch("topPtWeightPast400",&topPtWeightPast400,"topPtWeightPast400/F");
   outputTree->Branch("topPtWeightHighPt",&topPtWeightHighPt,"topPtWeightHighPt/F");
   outputTree->Branch("deltaRlepJetInMinMljet",&deltaRlepJetInMinMljet,"deltaRlepJetInMinMljet/F");
   outputTree->Branch("deltaRlepbJetInMinMlb",&deltaRlepbJetInMinMlb,"deltaRlepbJetInMinMlb/F");
   outputTree->Branch("deltaRlepbJetInMinMlb_shifts",&deltaRlepbJetInMinMlb_shifts);
   outputTree->Branch("deltaPhilepJetInMinMljet",&deltaPhilepJetInMinMljet,"deltaPhilepJetInMinMljet/F");
   outputTree->Branch("deltaPhilepbJetInMinMlb",&deltaPhilepbJetInMinMlb,"deltaPhilepbJetInMinMlb/F");
   outputTree->Branch("deltaPhilepbJetInMinMlb_shifts",&deltaPhilepbJetInMinMlb_shifts);
   outputTree->Branch("deltaRtopWjet",&deltaRtopWjet,"deltaRtopWjet/F");
   outputTree->Branch("deltaRlepWjet",&deltaRlepWjet,"deltaRlepWjet/F");
   outputTree->Branch("deltaRlepTjet",&deltaRlepTjet,"deltaRlepTjet/F");
   outputTree->Branch("deltaPhitopWjet",&deltaPhitopWjet,"deltaPhitopWjet/F");
   outputTree->Branch("deltaPhilepWjet",&deltaPhilepWjet,"deltaPhilepWjet/F");
   outputTree->Branch("deltaPhilepTjet",&deltaPhilepTjet,"deltaPhilepTjet/F");
   outputTree->Branch("deltaRtopWjet_shifts",&deltaRtopWjet_shifts);
   outputTree->Branch("deltaRlepWjet_shifts",&deltaRlepWjet_shifts);
   outputTree->Branch("deltaRlepTjet_shifts",&deltaRlepTjet_shifts);
   outputTree->Branch("deltaPhitopWjet_shifts",&deltaPhitopWjet_shifts);
   outputTree->Branch("deltaPhilepWjet_shifts",&deltaPhilepWjet_shifts);
   outputTree->Branch("deltaPhilepTjet_shifts",&deltaPhilepTjet_shifts);
   outputTree->Branch("NJetsWtagged_0p6",&NJetsWtagged_0p6,"NJetsWtagged_0p6/I");
   outputTree->Branch("NJetsWtagged_0p6_shifts",&NJetsWtagged_0p6_shifts);
   outputTree->Branch("NJetsTtagged_0p81",&NJetsTtagged_0p81,"NJetsTtagged_0p81/I");
   outputTree->Branch("NJetsTtagged_0p81_shifts",&NJetsTtagged_0p81_shifts);
   outputTree->Branch("minDR_leadAK8otherAK8",&minDR_leadAK8otherAK8,"minDR_leadAK8otherAK8/F");
   outputTree->Branch("minDR_lepAK8",&minDR_lepAK8,"minDR_lepAK8/F");
   outputTree->Branch("minDR_lepJet",&minDR_lepJet,"minDR_lepJet/F");
   outputTree->Branch("minDR_lep1Jet",&minDR_lep1Jet,"minDR_lep1Jet/F");
   outputTree->Branch("minDR_lep2Jet",&minDR_lep2Jet,"minDR_lep2Jet/F");
   //   outputTree->Branch("minDR_lep3Jet",&minDR_lep3Jet,"minDR_lep3Jet/F");
   outputTree->Branch("minDR_lepMET",&minDR_lepMET,"minDR_lepMET/F");
   outputTree->Branch("minDR_METJet",&minDR_METJet,"minDR_METJet/F");
   outputTree->Branch("ptRel_lepJet",&ptRel_lepJet,"ptRel_lepJet/F");
   outputTree->Branch("MT_lepMet",&MT_lepMet,"MT_lepMet/F");
   outputTree->Branch("deltaR_lepJets",&deltaR_lepJets);
   outputTree->Branch("deltaR_lep1Jets",&deltaR_lep1Jets);
   outputTree->Branch("deltaR_lep2Jets",&deltaR_lep2Jets);
   //outputTree->Branch("deltaR_lep3Jets",&deltaR_lep3Jets);
   outputTree->Branch("deltaR_lepMETs",&deltaR_lepMETs);
   outputTree->Branch("deltaR_METJets",&deltaR_METJets);
   outputTree->Branch("deltaR_lepBJets",&deltaR_lepBJets);
   outputTree->Branch("deltaR_lepBJets_bSFup",&deltaR_lepBJets_bSFup);
   outputTree->Branch("deltaR_lepBJets_bSFdn",&deltaR_lepBJets_bSFdn);
   outputTree->Branch("deltaR_lepBJets_lSFup",&deltaR_lepBJets_lSFup);
   outputTree->Branch("deltaR_lepBJets_lSFdn",&deltaR_lepBJets_lSFdn);
   outputTree->Branch("deltaR_lepAK8s",&deltaR_lepAK8s);
   outputTree->Branch("deltaPhi_lepJets",&deltaPhi_lepJets);
   outputTree->Branch("deltaPhi_lepBJets",&deltaPhi_lepBJets);
   outputTree->Branch("deltaPhi_lepBJets_bSFup",&deltaPhi_lepBJets_bSFup);
   outputTree->Branch("deltaPhi_lepBJets_bSFdn",&deltaPhi_lepBJets_bSFdn);
   outputTree->Branch("deltaPhi_lepBJets_lSFup",&deltaPhi_lepBJets_lSFup);
   outputTree->Branch("deltaPhi_lepBJets_lSFdn",&deltaPhi_lepBJets_lSFdn);
   outputTree->Branch("deltaPhi_lepAK8s",&deltaPhi_lepAK8s);
   outputTree->Branch("mass_lepJets",&mass_lepJets);
   outputTree->Branch("mass_lepBJets",&mass_lepBJets);
   outputTree->Branch("mass_lepBJets_bSFup",&mass_lepBJets_bSFup);
   outputTree->Branch("mass_lepBJets_bSFdn",&mass_lepBJets_bSFdn);
   outputTree->Branch("mass_lepBJets_lSFup",&mass_lepBJets_lSFup);
   outputTree->Branch("mass_lepBJets_lSFdn",&mass_lepBJets_lSFdn);
   outputTree->Branch("mass_lepAK8s",&mass_lepAK8s);

   outputTree->Branch("minDR_lepJets",&minDR_lepJets);
   outputTree->Branch("minDR_lepBJets",&minDR_lepBJets);

   outputTree->Branch("deltaR_lepClosestJet",&deltaR_lepClosestJet);
   outputTree->Branch("PtRelLepClosestJet",&PtRelLepClosestJet);

   outputTree->Branch("Mll_OS",&Mll_OS,"Mll_OS/F");
   outputTree->Branch("Mll_SS",&Mll_SS,"Mll_SS/F");
   //   outputTree->Branch("MllOS_allComb_min",&MllOS_allComb_min,"MllOS_allComb_min/F");
   //outputTree->Branch("MllOS_allComb_max",&MllOS_allComb_max,"MllOS_allComb_max/F");
   outputTree->Branch("Mll",&Mll,"Mll/F");


  // ----------------------------------------------------------------------------
  // Define and initialize objects / cuts / efficiencies
  // ----------------------------------------------------------------------------

   // basic cuts
   float metCut=30;
   int   njetsCut=0;
   float JetLeadPtCut=0;
   float JetSubLeadPtCut=0;
   float lepPtCut=30;
   float MllCut=20;
   float jetEtaCut=2.4;
   float ak8EtaCut=2.4;
   float jetPtCut=30;

   // counters
   int npass_trigger      = 0;
   int npass_mu500        = 0;
   int npass_met          = 0;
   int npass_njets        = 0;
   int npass_nHjets       = 0;
   int npass_JetLeadPt    = 0;
   int npass_JetSubLeadPt = 0;
   int npass_dilepPt     = 0;
   int npass_ElEta        = 0;
   int npass_MllCut       = 0;
   int npass_all          = 0;
   int Nelectrons         = 0;
   int Nmuons             = 0;

   int totalLep = 0;
   
   int Nee[3]={0};
   int Nem[3]={0};
   //   int Nem[4]={0};
   int Nmm[3]={0};
   
   int EE_count = 0;
   int EM_count = 0;
   int MM_count = 0;
   // int MMM_count = 0;
   
   int nPassDilepton=0;

   // Lorentz vectors
   TLorentzVector jet_lv;
   TLorentzVector bjet_lv;
   TLorentzVector wjet1_lv;
   TLorentzVector tjet1_lv;
//    TLorentzVector lepton_lv;
   std::vector<TLorentzVector> lepton_lv;
   TLorentzVector ak8_lv;
   
   // Muon Trigger & tracking efficiencies
   float avePtPOG[4][6] = {
     {35.55,44.32,53.90,73.03,145.96,254.04},
     {35.56,44.41,53.84,72.79,144.55,254.16},
     {35.36,44.38,53.83,71.70,144.44,230.07},
     {35.69,44.31,53.95,73.08,145.84,270.32},
   };
   float mueffs[4][6] = {
     {0.906,0.926,0.930,0.929,0.926,0.922},
     {0.904,0.928,0.932,0.931,0.912,0.889},
     {0.859,0.884,0.889,0.888,0.874,0.851},
     {0.786,0.817,0.820,0.823,0.774,0.675}
   };

   // Muon tracking efficiencies, https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonWorkInProgressAndPagResults#Results_on_the_full_2016_data, Feb 16 release for full data
   float tracksf[15] = {0.991237,0.994853, 0.996413,0.997157,0.997512,0.99756,0.996745,0.996996,0.99772,0.998604,0.998321,0.997682,0.995252,0.994919,0.987334};
   
   float SignalEff[11][14] = {
     {0.548356, 0.582139, 0.583056, 0.589624, 0.593879, 0.596037, 0.606139, 0.603989, 0.604075, 0.612769, 0.598276, 0.563951, 0.562433, 0.481481},
     {0.537263, 0.566472, 0.563321, 0.566097, 0.569125, 0.578216, 0.579019, 0.585555, 0.589941, 0.589891, 0.590064, 0.591820, 0.566303, 0.476440},
     {0.538521, 0.557660, 0.543946, 0.545865, 0.558151, 0.563405, 0.572813, 0.570846, 0.573461, 0.586819, 0.578804, 0.572940, 0.561443, 0.555556},
     {0.530602, 0.550354, 0.538940, 0.536638, 0.544389, 0.550410, 0.554327, 0.562982, 0.568316, 0.567526, 0.576123, 0.575019, 0.560201, 0.550186},
     {0.533944, 0.550041, 0.530723, 0.522086, 0.528805, 0.539058, 0.545445, 0.549327, 0.552455, 0.554668, 0.559353, 0.558860, 0.553680, 0.531915},
     {0.538718, 0.549315, 0.523989, 0.518197, 0.516679, 0.527819, 0.534820, 0.540149, 0.540099, 0.549270, 0.550459, 0.557293, 0.545746, 0.559468},
     {0.542657, 0.554109, 0.528772, 0.512938, 0.509910, 0.519070, 0.522395, 0.532678, 0.535456, 0.538611, 0.540082, 0.546394, 0.540544, 0.539807},
     {0.539844, 0.566326, 0.531928, 0.506292, 0.502152, 0.510498, 0.513585, 0.520557, 0.527288, 0.534014, 0.538507, 0.537015, 0.535885, 0.540658},
     {0.548628, 0.559869, 0.551592, 0.510941, 0.501727, 0.506774, 0.502805, 0.513068, 0.519535, 0.520095, 0.519365, 0.519234, 0.537919, 0.519135},
     {0.549918, 0.577604, 0.540031, 0.518584, 0.507735, 0.504109, 0.500252, 0.506397, 0.513234, 0.518664, 0.521474, 0.520294, 0.518832, 0.532468},
     {0.554463, 0.581864, 0.553090, 0.522106, 0.504654, 0.496037, 0.501408, 0.500636, 0.504387, 0.509833, 0.515884, 0.510956, 0.515713, 0.538008},
   };
   float TTbarEff[14] = {0.682439, 0.738105, 0.707007, 0.676506, 0.655480, 0.647157, 0.640495, 0.631280, 0.629425, 0.588845, 0.572383,  0.631179, 0.528302, 0.333333};
   float STEff[14] = {0.721371, 0.799146, 0.782680, 0.762160, 0.743905, 0.729174, 0.727657, 0.709333, 0.724403, 0.717466, 0.690385,  0.666667, 0.483333, 0.600000};
   float WVEff[14] = {0.712598, 0.791459, 0.756127, 0.723847, 0.705318, 0.674699, 0.718884, 0.626923, 0.662162, 0.656250, 0.564356,  0.454545, 0.285714, 0.285714};
   float TTVEff[14] = {0.605128, 0.633895, 0.614585, 0.602014, 0.588748, 0.569500, 0.557702, 0.571873, 0.539608, 0.537893, 0.540462,  0.444444, 0.189189, 0.600000};

   // Pileup distributions - from Julie 3 Feb through skype  - /jmanagan/nobackup/EffsAndNegWeights/TagEffsM17/pileupWeights.txt.
   double pileup_central[80] = {3.603e-01, 9.378e-01, 1.201e+00, 9.651e-01, 1.112e+00, 1.162e+00, 7.847e-01, 4.960e-01, 7.422e-01, 8.839e-01, 9.662e-01, 1.071e+00, 1.124e+00, 1.175e+00, 1.203e+00, 1.208e+00, 1.200e+00, 1.182e+00, 1.144e+00, 1.096e+00, 1.065e+00, 1.051e+00, 1.052e+00, 1.051e+00, 1.050e+00, 1.057e+00, 1.072e+00, 1.083e+00, 1.095e+00, 1.108e+00, 1.094e+00, 1.084e+00, 1.042e+00, 9.850e-01, 9.095e-01, 8.196e-01, 7.159e-01, 6.107e-01, 5.032e-01, 4.052e-01, 3.092e-01, 2.285e-01, 1.636e-01, 1.133e-01, 7.738e-02, 5.090e-02, 3.180e-02, 2.013e-02, 1.226e-02, 7.425e-03, 4.389e-03, 2.614e-03, 1.572e-03, 9.679e-04, 7.333e-04, 6.786e-04, 7.342e-04, 9.346e-04, 1.346e-03, 1.888e-03, 3.248e-03, 3.966e-03, 4.872e-03, 5.119e-03, 5.452e-03, 5.338e-03, 5.112e-03, 4.397e-03, 4.023e-03, 3.359e-03, 2.987e-03, 2.770e-03, 2.278e-03, 1.982e-03, 1.765e-03, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00};

   double pileup_up[80] = {3.510e-01, 7.384e-01, 1.136e+00, 8.481e-01, 1.011e+00, 1.047e+00, 7.158e-01, 3.479e-01, 5.006e-01, 6.065e-01, 6.335e-01, 7.320e-01, 8.266e-01, 9.118e-01, 9.603e-01, 9.892e-01, 1.024e+00, 1.052e+00, 1.051e+00, 1.027e+00, 1.005e+00, 9.982e-01, 1.015e+00, 1.038e+00, 1.058e+00, 1.085e+00, 1.121e+00, 1.155e+00, 1.192e+00, 1.232e+00, 1.245e+00, 1.269e+00, 1.260e+00, 1.233e+00, 1.180e+00, 1.103e+00, 1.001e+00, 8.905e-01, 7.691e-01, 6.545e-01, 5.326e-01, 4.236e-01, 3.297e-01, 2.501e-01, 1.888e-01, 1.381e-01, 9.654e-02, 6.875e-02, 4.733e-02, 3.248e-02, 2.175e-02, 1.456e-02, 9.619e-03, 6.146e-03, 4.301e-03, 3.097e-03, 2.253e-03, 1.894e-03, 2.009e-03, 2.389e-03, 3.847e-03, 4.626e-03, 5.722e-03, 6.110e-03, 6.639e-03, 6.646e-03, 6.514e-03, 5.738e-03, 5.381e-03, 4.607e-03, 4.204e-03, 4.003e-03, 3.382e-03, 3.025e-03, 2.770e-03, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00};

   double pileup_down[80] = {3.733e-01, 1.197e+00, 1.263e+00, 1.102e+00, 1.240e+00, 1.278e+00, 9.076e-01, 7.680e-01, 1.093e+00, 1.345e+00, 1.489e+00, 1.526e+00, 1.496e+00, 1.500e+00, 1.498e+00, 1.445e+00, 1.367e+00, 1.298e+00, 1.228e+00, 1.165e+00, 1.125e+00, 1.091e+00, 1.065e+00, 1.041e+00, 1.019e+00, 1.005e+00, 9.973e-01, 9.851e-01, 9.722e-01, 9.567e-01, 9.141e-01, 8.732e-01, 8.075e-01, 7.337e-01, 6.501e-01, 5.605e-01, 4.658e-01, 3.750e-01, 2.886e-01, 2.147e-01, 1.498e-01, 1.001e-01, 6.433e-02, 3.962e-02, 2.392e-02, 1.382e-02, 7.544e-03, 4.163e-03, 2.215e-03, 1.187e-03, 6.441e-04, 3.850e-04, 2.739e-04, 2.425e-04, 2.913e-04, 3.993e-04, 5.467e-04, 7.711e-04, 1.143e-03, 1.598e-03, 2.706e-03, 3.234e-03, 3.878e-03, 3.973e-03, 4.121e-03, 3.928e-03, 3.659e-03, 3.059e-03, 2.719e-03, 2.203e-03, 1.901e-03, 1.709e-03, 1.362e-03, 1.147e-03, 9.884e-04, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00, 0.000e+00};
	

  // ----------------------------------------------------------------------------
  // RUN THE EVENT LOOP
  // ----------------------------------------------------------------------------

   cout << "RUN CONFIG: isMC = " << isMC << endl;
   cout << "isSig = " << isSig << ", SigMass = " << SigMass << endl;
   cout << "For W's: isTT = " << isTT << ", isST = " << isST << endl;
   cout << "Fot jets & PDF: isTOP = " << isTOP << ", isMadgraphBkg = " << isMadgraphBkg << endl;
      
   Long64_t nentries = inputTree->GetEntriesFast();

   Long64_t nbytes = 0, nb = 0;
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);
      if (ientry < 0) break;
      nb = inputTree->GetEntry(jentry);   nbytes += nb;
      if (Cut(ientry) != 1) continue;
      
      //      if (ientry > 5000) continue;
      
      if(DEBUG||DEBUGleptons||DEBUGddbkg||DEBUGTriggers)std::cout << "" << std::endl;
      if(DEBUG||DEBUGleptons||DEBUGddbkg||DEBUGTriggers)std::cout << "+++++++++++++++++++++++++++++++" << std::endl;
      if(DEBUG||DEBUGleptons||DEBUGddbkg||DEBUGTriggers)std::cout<<"Event "<<event_CommonCalc<<std::endl;
      if(DEBUG||DEBUGleptons||DEBUGddbkg||DEBUGTriggers)std::cout << "+++++++++++++++++++++++++++++++" << std::endl;
      
      if(jentry % 1000 ==0) std::cout<<"Completed "<<jentry<<" out of "<<nentries<<" events"<<std::endl;

      // ----------------------------------------------------------------------------
      // Filter input file by mass or decay
      // ----------------------------------------------------------------------------

      if(isTTincMtt0to700 && ttbarMass_TTbarMassCalc >= 700.) continue;
      if(isTTincMtt0to1000 && ttbarMass_TTbarMassCalc >= 1000.) continue;
      if(isTTincMtt700to1000 && (ttbarMass_TTbarMassCalc < 700. || ttbarMass_TTbarMassCalc >= 1000.)) continue;
      if(isTTincMtt1000toInf && ttbarMass_TTbarMassCalc < 1000.) continue;
      if(outBWBW && !isBWBW_TpTpCalc) continue;
      if(outTZBW && !isTZBW_TpTpCalc) continue;
      if(outTHBW && !isTHBW_TpTpCalc) continue;
      if(outTZTH && !isTZTH_TpTpCalc) continue;
      if(outTZTZ && !isTZTZ_TpTpCalc) continue;
      if(outTHTH && !isTHTH_TpTpCalc) continue;
      if(outTWTW && !isTWTW_TpTpCalc) continue;
      if(outBZTW && !isBZTW_TpTpCalc) continue;
      if(outBHTW && !isBHTW_TpTpCalc) continue;
      if(outBZBH && !isBZBH_TpTpCalc) continue;
      if(outBZBZ && !isBZBZ_TpTpCalc) continue;
      if(outBHBH && !isBHBH_TpTpCalc) continue;

      // ----------------------------------------------------------------------------
      // Collect leptons and Assign event category and some other things
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"Collect leptons and Assign event category and some other things"<<std::endl;      
      
      // ------ Rizki - start 

      if(DEBUG)std::cout<<"Rizki A - start"<<std::endl;

      std::vector<double> TightLeptonPt;
      std::vector<double> TightLeptonEta;
      std::vector<double> TightLeptonPhi;
      std::vector<double> TightLeptonEnergy;
      std::vector<double> TightLeptonMiniIso;
      std::vector<int> TightLeptonFlavor; // 0 - electron, 1 - muon
      std::vector<int> TightLeptonCharge; // 0 - electron, 1 - muon
      std::vector<int> TightLeptonIdx; // index in LJMet ntuple
      std::vector<pair<double,int>> tightlepptindpair;      

      std::vector<double> LooseNotTightLeptonPt;
      std::vector<double> LooseNotTightLeptonEta;
      std::vector<double> LooseNotTightLeptonPhi;
      std::vector<double> LooseNotTightLeptonEnergy;
      std::vector<double> LooseNotTightLeptonMiniIso;
      std::vector<int> LooseNotTightLeptonFlavor; // 0 - electron, 1 - muon
      std::vector<int> LooseNotTightLeptonCharge; // 0 - electron, 1 - muon
      std::vector<int> LooseNotTightLeptonIdx; // index in LJMet ntuple
      std::vector<pair<double,int>> loosenottightlepptindpair;      

      std::vector<double> AllLeptonPt;
      std::vector<double> AllLeptonEta;
      std::vector<double> AllLeptonPhi;
      std::vector<double> AllLeptonEnergy;
      std::vector<double> AllLeptonMiniIso;
      std::vector<int> AllLeptonFlavor; // 0 - electron, 1 - muon
      std::vector<int> AllLeptonIsTight; 
      std::vector<int> AllLeptonCharge;       
      std::vector<int> AllLeptonIdx; // index in LJMet ntuple
      int AllLeptonCount = 0; 
      AllLeptonCount_PtOrdered = 0;
      AllLeptonElCount_PtOrdered = 0;
      AllLeptonMuCount_PtOrdered  = 0;
      std::vector<pair<double,int>> alllepptindpair;
      std::vector<pair<double,int>> alllepptindpair_top2;
      

      int tightlepindex = 0;
      int loosenottightlepindex = 0;
      int alllepindex = 0;
      int alllepindex_top2 = 0;
            
      //collect all electrons.
      if(DEBUG)std::cout<<"Collecting electrons ..."<<std::endl;      
      if(DEBUG)std::cout<<"elPt_singleLepCalc->size() = "<< elPt_singleLepCalc->size() <<std::endl;  
      for(unsigned int iel = 0; iel < elPt_singleLepCalc->size(); iel++){
		if(elPt_singleLepCalc->at(iel) < lepPtCut || fabs(elEta_singleLepCalc->at(iel)) > 2.4) continue;

		//Explicit check for Tight electrons
		bool isTightEl = false;
		if(elMiniIso_singleLepCalc->at(iel) < 0.1){
			//tight_electron_mva_cuts  = cms.vdouble(0.674,0.744,0.170), # 80X WP80 to recover efficiency of 74X WP80 - from LJMET
		  if(fabs(elEta_singleLepCalc->at(iel)) <= 0.8 && elMVAValue_singleLepCalc->at(iel) > 0.674) isTightEl = true;
		  else if(fabs(elEta_singleLepCalc->at(iel)) > 0.8 && fabs(elEta_singleLepCalc->at(iel)) <= 1.479 && elMVAValue_singleLepCalc->at(iel) > 0.744) isTightEl = true;
		  else if(fabs(elEta_singleLepCalc->at(iel)) > 1.479 && fabs(elEta_singleLepCalc->at(iel)) <= 2.5 && elMVAValue_singleLepCalc->at(iel) > 0.170) isTightEl = true;
		}
		if(isTightEl){
		  TightLeptonPt.push_back(elPt_singleLepCalc->at(iel));
		  TightLeptonEta.push_back(elEta_singleLepCalc->at(iel));
		  TightLeptonPhi.push_back(elPhi_singleLepCalc->at(iel));
		  TightLeptonEnergy.push_back(elEnergy_singleLepCalc->at(iel));
		  TightLeptonMiniIso.push_back(elMiniIso_singleLepCalc->at(iel));
		  TightLeptonFlavor.push_back(0);
		  TightLeptonCharge.push_back(elCharge_singleLepCalc->at(iel));
		  TightLeptonIdx.push_back(iel);

		  tightlepptindpair.push_back(std::make_pair(elPt_singleLepCalc->at(iel),tightlepindex));
		  tightlepindex++;

		  AllLeptonPt.push_back(elPt_singleLepCalc->at(iel));
		  AllLeptonEta.push_back(elEta_singleLepCalc->at(iel));
		  AllLeptonPhi.push_back(elPhi_singleLepCalc->at(iel));
		  AllLeptonEnergy.push_back(elEnergy_singleLepCalc->at(iel));
		  AllLeptonMiniIso.push_back(elMiniIso_singleLepCalc->at(iel));
		  AllLeptonFlavor.push_back(0);
		  AllLeptonCharge.push_back(elCharge_singleLepCalc->at(iel));
		  AllLeptonIsTight.push_back(1);
		  AllLeptonIdx.push_back(iel);

		  alllepptindpair.push_back(std::make_pair(elPt_singleLepCalc->at(iel),alllepindex));
		  alllepindex++;
		}

		//Explicit check for Loose electrons (there is a mistake in LJMet 052716, miniIso flag not applied!)
		bool isLooseEl = false;
		if(elMiniIso_singleLepCalc->at(iel) < 0.4){
			//loose_electron_mva_cuts  = cms.vdouble(-0.041,0.383,-0.515), # 80X WP90 to recover efficiency of 74X WP90 - from LJMET
		  if(fabs(elEta_singleLepCalc->at(iel)) <= 0.8 && elMVAValue_singleLepCalc->at(iel) > -0.041) isLooseEl = true;
		  else if(fabs(elEta_singleLepCalc->at(iel)) > 0.8 && fabs(elEta_singleLepCalc->at(iel)) <= 1.479 && elMVAValue_singleLepCalc->at(iel) > 0.383) isLooseEl = true;
		  else if(fabs(elEta_singleLepCalc->at(iel)) > 1.479 && fabs(elEta_singleLepCalc->at(iel)) <= 2.5 && elMVAValue_singleLepCalc->at(iel) > -0.515) isLooseEl = true;
		}
		if(!isTightEl && isLooseEl){
		  LooseNotTightLeptonPt.push_back(elPt_singleLepCalc->at(iel));
		  LooseNotTightLeptonEta.push_back(elEta_singleLepCalc->at(iel));
		  LooseNotTightLeptonPhi.push_back(elPhi_singleLepCalc->at(iel));
		  LooseNotTightLeptonEnergy.push_back(elEnergy_singleLepCalc->at(iel));
		  LooseNotTightLeptonMiniIso.push_back(elMiniIso_singleLepCalc->at(iel));
		  LooseNotTightLeptonFlavor.push_back(0);
		  LooseNotTightLeptonCharge.push_back(elCharge_singleLepCalc->at(iel));
		  LooseNotTightLeptonIdx.push_back(iel);
		  
		  loosenottightlepptindpair.push_back(std::make_pair(elPt_singleLepCalc->at(iel),loosenottightlepindex));
		  loosenottightlepindex++;

		  AllLeptonPt.push_back(elPt_singleLepCalc->at(iel));
		  AllLeptonEta.push_back(elEta_singleLepCalc->at(iel));
		  AllLeptonPhi.push_back(elPhi_singleLepCalc->at(iel));
		  AllLeptonEnergy.push_back(elEnergy_singleLepCalc->at(iel));
		  AllLeptonMiniIso.push_back(elMiniIso_singleLepCalc->at(iel));
		  AllLeptonFlavor.push_back(0);
		  AllLeptonCharge.push_back(elCharge_singleLepCalc->at(iel));
		  AllLeptonIsTight.push_back(0);
		  AllLeptonIdx.push_back(iel);

		  alllepptindpair.push_back(std::make_pair(elPt_singleLepCalc->at(iel),alllepindex));
		  alllepindex++;
		}
		
      }
      
      //collect all muons. 
      if(DEBUG)std::cout<<"Collecting muons ..."<<std::endl;      
      if(DEBUG)std::cout<<"muPt_singleLepCalc->size() = "<< muPt_singleLepCalc->size() <<std::endl;  
      for(unsigned int imu = 0; imu < muPt_singleLepCalc->size(); imu++){
		if(muPt_singleLepCalc->at(imu) < lepPtCut || fabs(muEta_singleLepCalc->at(imu)) > 2.4) continue;
		//if(muPt_singleLepCalc->at(imu) > 500 && fabs(muEta_singleLepCalc->at(imu)) > 1.2) continue; // --->>  No need for FULL2016 dataset! not mentioned anymore in pog twiki
		
		//Explicit check for tight muons
		bool isTightMu = false;
		//ATTENTION: for Morion 2017 Clints tighten his MiniIso cut to 0.1 because of efficiency gain. 
		if(muMiniIso_singleLepCalc->at(imu) < 0.1 && muIsTight_singleLepCalc->at(imu) > 0) isTightMu = true;

		if(isTightMu){
		  TightLeptonPt.push_back(muPt_singleLepCalc->at(imu));
		  TightLeptonEta.push_back(muEta_singleLepCalc->at(imu));
		  TightLeptonPhi.push_back(muPhi_singleLepCalc->at(imu));
		  TightLeptonEnergy.push_back(muEnergy_singleLepCalc->at(imu));
		  TightLeptonMiniIso.push_back(muMiniIso_singleLepCalc->at(imu));
		  TightLeptonFlavor.push_back(1);
		  TightLeptonCharge.push_back(muCharge_singleLepCalc->at(imu));
		  TightLeptonIdx.push_back(imu);

		  tightlepptindpair.push_back(std::make_pair(muPt_singleLepCalc->at(imu),tightlepindex));
		  tightlepindex++;

		  AllLeptonPt.push_back(muPt_singleLepCalc->at(imu));
		  AllLeptonEta.push_back(muEta_singleLepCalc->at(imu));
		  AllLeptonPhi.push_back(muPhi_singleLepCalc->at(imu));
		  AllLeptonEnergy.push_back(muEnergy_singleLepCalc->at(imu));
		  AllLeptonMiniIso.push_back(muMiniIso_singleLepCalc->at(imu));
		  AllLeptonFlavor.push_back(1);
		  AllLeptonCharge.push_back(muCharge_singleLepCalc->at(imu));
		  AllLeptonIsTight.push_back(1);
		  AllLeptonIdx.push_back(imu);

		  alllepptindpair.push_back(std::make_pair(muPt_singleLepCalc->at(imu),alllepindex));
		  alllepindex++;
		}
		
		//Explicit check for Loose muons
		bool isLooseMu = false;
		if(muMiniIso_singleLepCalc->at(imu) < 0.4 && muIsTight_singleLepCalc->at(imu) == 0) isLooseMu = true;

// 		if(!isTightMu && isLooseMu){ //ATTENTION: WHICH ONE iS CORRECT???
		if(!isTightMu){ ////ATTENTION: WHICH ONE iS CORRECT???
		  LooseNotTightLeptonPt.push_back(muPt_singleLepCalc->at(imu));
		  LooseNotTightLeptonEta.push_back(muEta_singleLepCalc->at(imu));
		  LooseNotTightLeptonPhi.push_back(muPhi_singleLepCalc->at(imu));
		  LooseNotTightLeptonEnergy.push_back(muEnergy_singleLepCalc->at(imu));
		  LooseNotTightLeptonMiniIso.push_back(muMiniIso_singleLepCalc->at(imu));//ATTENTION! there is mistake in new 74x LJMet ntuple muMiniIso twice filled!! hence the imu*2
		  LooseNotTightLeptonFlavor.push_back(1);
		  LooseNotTightLeptonCharge.push_back(muCharge_singleLepCalc->at(imu));
		  LooseNotTightLeptonIdx.push_back(imu);
		  
		  loosenottightlepptindpair.push_back(std::make_pair(muPt_singleLepCalc->at(imu),loosenottightlepindex));
		  loosenottightlepindex++;

		  AllLeptonPt.push_back(muPt_singleLepCalc->at(imu));
		  AllLeptonEta.push_back(muEta_singleLepCalc->at(imu));
		  AllLeptonPhi.push_back(muPhi_singleLepCalc->at(imu));
		  AllLeptonEnergy.push_back(muEnergy_singleLepCalc->at(imu));
		  AllLeptonMiniIso.push_back(muMiniIso_singleLepCalc->at(imu));
		  AllLeptonFlavor.push_back(1);
		  AllLeptonCharge.push_back(muCharge_singleLepCalc->at(imu));
		  AllLeptonIsTight.push_back(0);
		  AllLeptonIdx.push_back(imu);

		  alllepptindpair.push_back(std::make_pair(muPt_singleLepCalc->at(imu),alllepindex));
		  alllepindex++;
		}

      }
      
      AllLeptonCount = alllepindex ;
      AllLeptonCount_PtOrdered =  AllLeptonCount;
      //std::cout << "Nleptons = " << AllLeptonCount_PtOrdered << endl;

      if(AllLeptonCount<2) continue; //skip if there is less than 2 loose leptons.
      // CHECK and UNCOMMENT BELOW if necessary!!
      if(isMC && tightlepindex<2) continue; //skip if there is less than 3 tight leptons for MC (not creating ddBKg).

      //Pt ordering
      AllLeptonPt_PtOrdered.clear();
      AllLeptonEta_PtOrdered.clear();
      AllLeptonPhi_PtOrdered.clear();
      AllLeptonEnergy_PtOrdered.clear();
      AllLeptonMiniIso_PtOrdered.clear();
      AllLeptonFlavor_PtOrdered.clear();
      AllLeptonIsTight_PtOrdered.clear();      
      AllLeptonCharge_PtOrdered.clear();      
      AllLeptonIdx_PtOrdered.clear();      
 
      //Pt ordering - for Tight leptons - then add to All leptons list/vector
      int Nel_tight = 0;
      int Nmu_tight = 0;
      std::sort(tightlepptindpair.begin(), tightlepptindpair.end(), comparepair);
      TightLeptonPt_PtOrdered.clear();
      TightLeptonEta_PtOrdered.clear();
      TightLeptonPhi_PtOrdered.clear();
      TightLeptonEnergy_PtOrdered.clear();
      TightLeptonMiniIso_PtOrdered.clear();
      TightLeptonFlavor_PtOrdered.clear();
      TightLeptonCharge_PtOrdered.clear();
      TightLeptonIdx_PtOrdered.clear();
      for(unsigned int ilep=0; ilep < tightlepptindpair.size(); ilep++){
      	TightLeptonPt_PtOrdered.push_back(TightLeptonPt.at(tightlepptindpair[ilep].second));
      	TightLeptonEta_PtOrdered.push_back(TightLeptonEta.at(tightlepptindpair[ilep].second));
      	TightLeptonPhi_PtOrdered.push_back(TightLeptonPhi.at(tightlepptindpair[ilep].second));
      	TightLeptonEnergy_PtOrdered.push_back(TightLeptonEnergy.at(tightlepptindpair[ilep].second));
      	TightLeptonMiniIso_PtOrdered.push_back(TightLeptonMiniIso.at(tightlepptindpair[ilep].second));
      	TightLeptonFlavor_PtOrdered.push_back(TightLeptonFlavor.at(tightlepptindpair[ilep].second));
      	TightLeptonCharge_PtOrdered.push_back(TightLeptonCharge.at(tightlepptindpair[ilep].second));
      	TightLeptonIdx_PtOrdered.push_back(TightLeptonIdx.at(tightlepptindpair[ilep].second));
 
		if(TightLeptonFlavor.at(tightlepptindpair[ilep].second) == 0) Nel_tight++;
		if(TightLeptonFlavor.at(tightlepptindpair[ilep].second) == 1) Nmu_tight++;
		
		//push back for all leptons order in pt AND TIGHT
		AllLeptonPt_PtOrdered.push_back(TightLeptonPt.at(tightlepptindpair[ilep].second));
      	AllLeptonEta_PtOrdered.push_back(TightLeptonEta.at(tightlepptindpair[ilep].second));
      	AllLeptonPhi_PtOrdered.push_back(TightLeptonPhi.at(tightlepptindpair[ilep].second));
      	AllLeptonEnergy_PtOrdered.push_back(TightLeptonEnergy.at(tightlepptindpair[ilep].second));
      	AllLeptonMiniIso_PtOrdered.push_back(TightLeptonMiniIso.at(tightlepptindpair[ilep].second));
      	AllLeptonFlavor_PtOrdered.push_back(TightLeptonFlavor.at(tightlepptindpair[ilep].second));
      	AllLeptonIsTight_PtOrdered.push_back(1);
      	AllLeptonCharge_PtOrdered.push_back(TightLeptonCharge.at(tightlepptindpair[ilep].second));				
      	AllLeptonIdx_PtOrdered.push_back(TightLeptonIdx.at(tightlepptindpair[ilep].second));				
      	
      	if(alllepindex_top2 < 2) alllepptindpair_top2.push_back(std::make_pair(TightLeptonPt.at(tightlepptindpair[ilep].second),alllepindex_top2));
      	if(DEBUG)cout<<"appending Tight         :"<<"alllepindex_top2="<<alllepindex_top2<<", alllepptindpair_top2["<<alllepindex_top2<<"].first = "<<alllepptindpair_top2[alllepindex_top2].first<<", alllepptindpair_top2["<<alllepindex_top2<<"].second = "<<alllepptindpair_top2[alllepindex_top2].second<<endl;
      	if(alllepindex_top2 < 2) alllepindex_top2++;

      }           

      //Pt ordering - for Loose Not Tight - then append to All leptons list/vector
      std::sort(loosenottightlepptindpair.begin(), loosenottightlepptindpair.end(), comparepair);
      for(unsigned int ilep=0; ilep < loosenottightlepptindpair.size(); ilep++){
	
		//push back for all leptons order in pt AND LOOSEnotTIGHT
		AllLeptonPt_PtOrdered.push_back(LooseNotTightLeptonPt.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonEta_PtOrdered.push_back(LooseNotTightLeptonEta.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonPhi_PtOrdered.push_back(LooseNotTightLeptonPhi.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonEnergy_PtOrdered.push_back(LooseNotTightLeptonEnergy.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonMiniIso_PtOrdered.push_back(LooseNotTightLeptonMiniIso.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonFlavor_PtOrdered.push_back(LooseNotTightLeptonFlavor.at(loosenottightlepptindpair[ilep].second));
      	AllLeptonIsTight_PtOrdered.push_back(0);
      	AllLeptonCharge_PtOrdered.push_back(LooseNotTightLeptonCharge.at(loosenottightlepptindpair[ilep].second));

      	if(alllepindex_top2 < 2) alllepptindpair_top2.push_back(std::make_pair(LooseNotTightLeptonPt.at(loosenottightlepptindpair[ilep].second),alllepindex_top2));
      	if(DEBUG)cout<<"appending LooseNotTight : alllepindex_top2="<<alllepindex_top2<<", alllepptindpair_top2["<<alllepindex_top2<<"].first = "<<alllepptindpair_top2[alllepindex_top2].first<<", alllepptindpair_top2["<<alllepindex_top2<<"].second = "<<alllepptindpair_top2[alllepindex_top2].second<<endl;
      	if(alllepindex_top2 < 2) alllepindex_top2++;
				
      }           
      
	  //DEBUG-start 
      AllLeptonElPt_PtOrdered.clear();
      AllLeptonElEta_PtOrdered.clear();
      AllLeptonElPhi_PtOrdered.clear();
      AllLeptonElEnergy_PtOrdered.clear();
      AllLeptonElMiniIso_PtOrdered.clear();
      AllLeptonElFlavor_PtOrdered.clear();
      AllLeptonElIsTight_PtOrdered.clear();      

      AllLeptonMuPt_PtOrdered.clear();
      AllLeptonMuEta_PtOrdered.clear();
      AllLeptonMuPhi_PtOrdered.clear();
      AllLeptonMuEnergy_PtOrdered.clear();
      AllLeptonMuMiniIso_PtOrdered.clear();
      AllLeptonMuFlavor_PtOrdered.clear();
      AllLeptonMuIsTight_PtOrdered.clear();      
      
      for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrdered.size(); ilep++){
      	if(AllLeptonFlavor_PtOrdered.at(ilep)==0){
		  AllLeptonElPt_PtOrdered.push_back(AllLeptonPt_PtOrdered.at(ilep));
		  AllLeptonElEta_PtOrdered.push_back(AllLeptonEta_PtOrdered.at(ilep));
		  AllLeptonElPhi_PtOrdered.push_back(AllLeptonPhi_PtOrdered.at(ilep));
		  AllLeptonElEnergy_PtOrdered.push_back(AllLeptonEnergy_PtOrdered.at(ilep));
		  AllLeptonElMiniIso_PtOrdered.push_back(AllLeptonMiniIso_PtOrdered.at(ilep));
		  AllLeptonElFlavor_PtOrdered.push_back(AllLeptonFlavor_PtOrdered.at(ilep));
		  AllLeptonElIsTight_PtOrdered.push_back(AllLeptonIsTight_PtOrdered.at(ilep));            	
		  AllLeptonElCount_PtOrdered++;            	
      	}
      	else{
		  AllLeptonMuPt_PtOrdered.push_back(AllLeptonPt_PtOrdered.at(ilep));
		  AllLeptonMuEta_PtOrdered.push_back(AllLeptonEta_PtOrdered.at(ilep));
		  AllLeptonMuPhi_PtOrdered.push_back(AllLeptonPhi_PtOrdered.at(ilep));
		  AllLeptonMuEnergy_PtOrdered.push_back(AllLeptonEnergy_PtOrdered.at(ilep));
		  AllLeptonMuMiniIso_PtOrdered.push_back(AllLeptonMiniIso_PtOrdered.at(ilep));
		  AllLeptonMuFlavor_PtOrdered.push_back(AllLeptonFlavor_PtOrdered.at(ilep));
		  AllLeptonMuIsTight_PtOrdered.push_back(AllLeptonIsTight_PtOrdered.at(ilep));            	      	
		  AllLeptonMuCount_PtOrdered++;            	
      	}
      }
      if(DEBUGleptons)cout<< "AllLeptonCount_PtOrdered   = " << AllLeptonCount_PtOrdered << endl;
      if(DEBUGleptons)cout<< "AllLeptonElCount_PtOrdered = " << AllLeptonElCount_PtOrdered << endl;
      if(DEBUGleptons)cout<< "AllLeptonMuCount_PtOrdered = " << AllLeptonMuCount_PtOrdered << endl;
	  //DEBUG-end
	  
	  //Sorting leptons by pT only - start
      std::sort(alllepptindpair.begin(), alllepptindpair.end(), comparepair);
      AllLeptonPt_PtOrderedOnly.clear();
      AllLeptonEta_PtOrderedOnly.clear();
      AllLeptonPhi_PtOrderedOnly.clear();
      AllLeptonEnergy_PtOrderedOnly.clear();
      AllLeptonMiniIso_PtOrderedOnly.clear();
      AllLeptonFlavor_PtOrderedOnly.clear();
      AllLeptonCharge_PtOrderedOnly.clear();
      AllLeptonIsTight_PtOrderedOnly.clear();
      AllLeptonIdx_PtOrderedOnly.clear();
      if(DEBUG)cout<<"alllepptindpair.size() = "<<alllepptindpair.size()<<endl;
      for(unsigned int ilep=0; ilep < alllepptindpair.size(); ilep++){
      	if(DEBUG)cout<<"alllepptindpair["<<ilep<<"].first = "<<alllepptindpair[ilep].first<<", alllepptindpair["<<ilep<<"].second = "<<alllepptindpair[ilep].second<<endl;
      	AllLeptonPt_PtOrderedOnly.push_back(AllLeptonPt.at(alllepptindpair[ilep].second));
      	AllLeptonEta_PtOrderedOnly.push_back(AllLeptonEta.at(alllepptindpair[ilep].second));
      	AllLeptonPhi_PtOrderedOnly.push_back(AllLeptonPhi.at(alllepptindpair[ilep].second));
      	AllLeptonEnergy_PtOrderedOnly.push_back(AllLeptonEnergy.at(alllepptindpair[ilep].second));
      	AllLeptonMiniIso_PtOrderedOnly.push_back(AllLeptonMiniIso.at(alllepptindpair[ilep].second));
      	AllLeptonFlavor_PtOrderedOnly.push_back(AllLeptonFlavor.at(alllepptindpair[ilep].second));
      	AllLeptonCharge_PtOrderedOnly.push_back(AllLeptonCharge.at(alllepptindpair[ilep].second));
      	AllLeptonIsTight_PtOrderedOnly.push_back(AllLeptonIsTight.at(alllepptindpair[ilep].second));
      	AllLeptonIdx_PtOrderedOnly.push_back(AllLeptonIdx.at(alllepptindpair[ilep].second));
      }           

      AllLeptonElPt_PtOrderedOnly.clear();
      AllLeptonElEta_PtOrderedOnly.clear();
      AllLeptonElPhi_PtOrderedOnly.clear();
      AllLeptonElEnergy_PtOrderedOnly.clear();
      AllLeptonElMiniIso_PtOrderedOnly.clear();
      AllLeptonElFlavor_PtOrderedOnly.clear();
      AllLeptonElIsTight_PtOrderedOnly.clear();      

      AllLeptonMuPt_PtOrderedOnly.clear();
      AllLeptonMuEta_PtOrderedOnly.clear();
      AllLeptonMuPhi_PtOrderedOnly.clear();
      AllLeptonMuEnergy_PtOrderedOnly.clear();
      AllLeptonMuMiniIso_PtOrderedOnly.clear();
      AllLeptonMuFlavor_PtOrderedOnly.clear();
      AllLeptonMuIsTight_PtOrderedOnly.clear();      

      for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrderedOnly.size(); ilep++){
      	if(AllLeptonFlavor_PtOrderedOnly.at(ilep)==0){
		  AllLeptonElPt_PtOrderedOnly.push_back(AllLeptonPt_PtOrderedOnly.at(ilep));
		  AllLeptonElEta_PtOrderedOnly.push_back(AllLeptonEta_PtOrderedOnly.at(ilep));
		  AllLeptonElPhi_PtOrderedOnly.push_back(AllLeptonPhi_PtOrderedOnly.at(ilep));
		  AllLeptonElEnergy_PtOrderedOnly.push_back(AllLeptonEnergy_PtOrderedOnly.at(ilep));
		  AllLeptonElMiniIso_PtOrderedOnly.push_back(AllLeptonMiniIso_PtOrderedOnly.at(ilep));
		  AllLeptonElFlavor_PtOrderedOnly.push_back(AllLeptonFlavor_PtOrderedOnly.at(ilep));
		  AllLeptonElIsTight_PtOrderedOnly.push_back(AllLeptonIsTight_PtOrderedOnly.at(ilep));            	
      	}
      	else{
		  AllLeptonMuPt_PtOrderedOnly.push_back(AllLeptonPt_PtOrderedOnly.at(ilep));
		  AllLeptonMuEta_PtOrderedOnly.push_back(AllLeptonEta_PtOrderedOnly.at(ilep));
		  AllLeptonMuPhi_PtOrderedOnly.push_back(AllLeptonPhi_PtOrderedOnly.at(ilep));
		  AllLeptonMuEnergy_PtOrderedOnly.push_back(AllLeptonEnergy_PtOrderedOnly.at(ilep));
		  AllLeptonMuMiniIso_PtOrderedOnly.push_back(AllLeptonMiniIso_PtOrderedOnly.at(ilep));
		  AllLeptonMuFlavor_PtOrderedOnly.push_back(AllLeptonFlavor_PtOrderedOnly.at(ilep));
		  AllLeptonMuIsTight_PtOrderedOnly.push_back(AllLeptonIsTight_PtOrderedOnly.at(ilep));            	      	
      	}
      }
      if(DEBUG)cout<<"DONE sorting all leps by pt only"<<endl;

	  //Sorting leptons by pT only - end

	  //Sorting leptons by pT only - reorder TOP 2 lep in default ordering - start
      std::sort(alllepptindpair_top2.begin(), alllepptindpair_top2.end(), comparepair);
      AllLeptonPt_PtOrderedOnly_top2.clear();
      AllLeptonEta_PtOrderedOnly_top2.clear();
      AllLeptonPhi_PtOrderedOnly_top2.clear();
      AllLeptonEnergy_PtOrderedOnly_top2.clear();
      AllLeptonMiniIso_PtOrderedOnly_top2.clear();
      AllLeptonFlavor_PtOrderedOnly_top2.clear();
      AllLeptonCharge_PtOrderedOnly_top2.clear();
      AllLeptonIsTight_PtOrderedOnly_top2.clear();
      AllLeptonIdx_PtOrderedOnly_top2.clear();
      if(DEBUG)cout<<"alllepptindpair_top2.size() = "<<alllepptindpair_top2.size()<<endl;
      for(unsigned int ilep=0; ilep < alllepptindpair_top2.size(); ilep++){
      	AllLeptonPt_PtOrderedOnly_top2.push_back(AllLeptonPt_PtOrdered.at(alllepptindpair_top2[ilep].second));
      	if(DEBUG)cout<<"alllepptindpair_top2["<<ilep<<"].first = "<<alllepptindpair_top2[ilep].first<<", alllepptindpair_top2["<<ilep<<"].second = "<<alllepptindpair_top2[ilep].second<<endl;
      	AllLeptonEta_PtOrderedOnly_top2.push_back(AllLeptonEta_PtOrdered.at(alllepptindpair_top2[ilep].second));
      	AllLeptonPhi_PtOrderedOnly_top2.push_back(AllLeptonPhi_PtOrdered.at(alllepptindpair_top2[ilep].second));
      	AllLeptonEnergy_PtOrderedOnly_top2.push_back(AllLeptonEnergy_PtOrdered.at(alllepptindpair_top2[ilep].second));
      	AllLeptonMiniIso_PtOrderedOnly_top2.push_back(AllLeptonMiniIso_PtOrdered.at(alllepptindpair_top2[ilep].second));
      	AllLeptonFlavor_PtOrderedOnly_top2.push_back(AllLeptonFlavor_PtOrdered.at(alllepptindpair_top2[ilep].second));
      	AllLeptonCharge_PtOrderedOnly_top2.push_back(AllLeptonCharge_PtOrdered.at(alllepptindpair_top2[ilep].second));
      	AllLeptonIsTight_PtOrderedOnly_top2.push_back(AllLeptonIsTight_PtOrdered.at(alllepptindpair_top2[ilep].second));
//       	AllLeptonIdx_PtOrderedOnly_top2.push_back(AllLeptonIdx_PtOrdered.at(alllepptindpair_top2[ilep].second));
//       	if(DEBUG)cout<<"Check idx"<<endl;
      }           

      AllLeptonElPt_PtOrderedOnly_top2.clear();
      AllLeptonElEta_PtOrderedOnly_top2.clear();
      AllLeptonElPhi_PtOrderedOnly_top2.clear();
      AllLeptonElEnergy_PtOrderedOnly_top2.clear();
      AllLeptonElMiniIso_PtOrderedOnly_top2.clear();
      AllLeptonElFlavor_PtOrderedOnly_top2.clear();
      AllLeptonElIsTight_PtOrderedOnly_top2.clear();      

      AllLeptonMuPt_PtOrderedOnly_top2.clear();
      AllLeptonMuEta_PtOrderedOnly_top2.clear();
      AllLeptonMuPhi_PtOrderedOnly_top2.clear();
      AllLeptonMuEnergy_PtOrderedOnly_top2.clear();
      AllLeptonMuMiniIso_PtOrderedOnly_top2.clear();
      AllLeptonMuFlavor_PtOrderedOnly_top2.clear();
      AllLeptonMuIsTight_PtOrderedOnly_top2.clear();      

      for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrderedOnly_top2.size(); ilep++){
      	if(AllLeptonFlavor_PtOrderedOnly_top2.at(ilep)==0){
		  AllLeptonElPt_PtOrderedOnly_top2.push_back(AllLeptonPt_PtOrderedOnly_top2.at(ilep));
		  AllLeptonElEta_PtOrderedOnly_top2.push_back(AllLeptonEta_PtOrderedOnly_top2.at(ilep));
		  AllLeptonElPhi_PtOrderedOnly_top2.push_back(AllLeptonPhi_PtOrderedOnly_top2.at(ilep));
		  AllLeptonElEnergy_PtOrderedOnly_top2.push_back(AllLeptonEnergy_PtOrderedOnly_top2.at(ilep));
		  AllLeptonElMiniIso_PtOrderedOnly_top2.push_back(AllLeptonMiniIso_PtOrderedOnly_top2.at(ilep));
		  AllLeptonElFlavor_PtOrderedOnly_top2.push_back(AllLeptonFlavor_PtOrderedOnly_top2.at(ilep));
		  AllLeptonElIsTight_PtOrderedOnly_top2.push_back(AllLeptonIsTight_PtOrderedOnly_top2.at(ilep));            	
      	}
      	else{
		  AllLeptonMuPt_PtOrderedOnly_top2.push_back(AllLeptonPt_PtOrderedOnly_top2.at(ilep));
		  AllLeptonMuEta_PtOrderedOnly_top2.push_back(AllLeptonEta_PtOrderedOnly_top2.at(ilep));
		  AllLeptonMuPhi_PtOrderedOnly_top2.push_back(AllLeptonPhi_PtOrderedOnly_top2.at(ilep));
		  AllLeptonMuEnergy_PtOrderedOnly_top2.push_back(AllLeptonEnergy_PtOrderedOnly_top2.at(ilep));
		  AllLeptonMuMiniIso_PtOrderedOnly_top2.push_back(AllLeptonMiniIso_PtOrderedOnly_top2.at(ilep));
		  AllLeptonMuFlavor_PtOrderedOnly_top2.push_back(AllLeptonFlavor_PtOrderedOnly_top2.at(ilep));
		  AllLeptonMuIsTight_PtOrderedOnly_top2.push_back(AllLeptonIsTight_PtOrderedOnly_top2.at(ilep));            	      	
      	}
      }
      if(DEBUG)cout<<"DONE sorting all leps by pt only - reorder TOP 2 lep in default ordering"<<endl;

	  //Sorting leptons by pT only - reorder TOP 2 lep in default ordering - end

      
      int Nel_top2 = 0;
      int Nmu_top2 = 0;
      int Nel_tight_top2 = 0;
      int Nmu_tight_top2 = 0;
      for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrdered.size(); ilep++){
      	if(ilep < 2){
      		if(AllLeptonFlavor_PtOrdered.at(ilep)==0){ 
      			Nel_top2++;
	      		if(AllLeptonIsTight_PtOrdered.at(ilep)==1) Nel_tight_top2++;
	      	}
      		if(AllLeptonFlavor_PtOrdered.at(ilep)==1){ 
      			Nmu_top2++;
      			if(AllLeptonIsTight_PtOrdered.at(ilep)==1) Nmu_tight_top2++;
      		}
      	}
      	if(DEBUGleptons)std::cout<< "DEFAULT ordering: ilep = " << ilep << ", flavor = " << AllLeptonFlavor_PtOrdered.at(ilep) << ", charge = " << AllLeptonCharge_PtOrdered.at(ilep) << ", pT = "<< AllLeptonPt_PtOrdered.at(ilep)  << ", Eta = "<< AllLeptonEta_PtOrdered.at(ilep)  << ", isTight = " << AllLeptonIsTight_PtOrdered.at(ilep) <<", miniIso = " << AllLeptonMiniIso_PtOrdered.at(ilep) << endl; 
      }

      if(DEBUGleptons){ for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrderedOnly.size(); ilep++){std::cout<< "PT ORDERED ONLY : ilep = " << ilep << ", flavor = " << AllLeptonFlavor_PtOrderedOnly.at(ilep) << ", charge = " << AllLeptonCharge_PtOrderedOnly.at(ilep) << ", pT = "<< AllLeptonPt_PtOrderedOnly.at(ilep)  << ", Eta = "<< AllLeptonEta_PtOrderedOnly.at(ilep)  << ", isTight = " << AllLeptonIsTight_PtOrderedOnly.at(ilep) <<", miniIso = " << AllLeptonMiniIso_PtOrderedOnly.at(ilep) << endl; } }
      if(DEBUGleptons){ for(unsigned int ilep=0; ilep < AllLeptonPt_PtOrderedOnly_top2.size(); ilep++){std::cout<< "ReORDER default by PT ONLY : ilep = " << ilep << ", flavor = " << AllLeptonFlavor_PtOrderedOnly_top2.at(ilep) << ", charge = " << AllLeptonCharge_PtOrderedOnly_top2.at(ilep) << ", pT = "<< AllLeptonPt_PtOrderedOnly_top2.at(ilep)  << ", Eta = "<< AllLeptonEta_PtOrderedOnly_top2.at(ilep)  << ", isTight = " << AllLeptonIsTight_PtOrderedOnly_top2.at(ilep) <<", miniIso = " << AllLeptonMiniIso_PtOrderedOnly_top2.at(ilep) << endl; } }

      
      if(DEBUGleptons)std::cout << "Nel_tight = " << Nel_tight << ",  Nmu_tight = " << Nmu_tight << endl; 
      if(DEBUGleptons)std::cout << "Nel_tight_top2 = " << Nel_tight_top2 << ",  Nmu_tight_top2 = " << Nmu_tight_top2 << endl; 
      if(DEBUGleptons)std::cout << "Nel_top2 = " << Nel_top2 << ",  Nmu_top2 = " << Nmu_top2 << endl; 

      isEE = 0; isEM =0; isMM =0;
      isTT = 0; isTL =0; isLT =0; isLL= 0;
      	
      if(Nel_tight_top2 + Nmu_tight_top2 != 2 && DEBUGleptons) cout << "First 2 tight leps don't add up to 2!" << endl;
      if(Nel_top2 + Nmu_top2 != 2) cout << "First 2 All leps don't add up to 2, something's wrong" << endl;

      int tightLepCounter = 2 * AllLeptonIsTight_PtOrdered.at(0) + 1 * AllLeptonIsTight_PtOrdered.at(1);
      if(Nel_top2==2){
      	isEE = 1;
		EE_count++;
		if(DEBUGleptons)std::cout << " -----> isEE " << std::endl;
		Nee[Nel_tight_top2]++;
		if (tightLepCounter==3){ isTT=1; if(DEBUGleptons)std::cout << " -----> isTT " << std::endl;}
		if (tightLepCounter==2){ isTL=1; if(DEBUGleptons)std::cout << " -----> isTL " << std::endl;}
		if (tightLepCounter==1){ isLT=1; if(DEBUGleptons)std::cout << " -----> isLT " << std::endl;}
		if (tightLepCounter==0){ isLL=1; if(DEBUGleptons)std::cout << " -----> isLL " << std::endl;}
		// if (tightLepCounter==4){ isTLL=1; if(DEBUGleptons)std::cout << " -----> isTLL " << std::endl;}
		// if (tightLepCounter==2){ isLTL=1; if(DEBUGleptons)std::cout << " -----> isLTL " << std::endl;}
		// if (tightLepCounter==1){ isLLT=1; if(DEBUGleptons)std::cout << " -----> isLLT " << std::endl;}
		// if (tightLepCounter==0){ isLLL=1; if(DEBUGleptons)std::cout << " -----> isLLL " << std::endl;}
      }
      if(Nel_top2==1){
		isEM = 1;
		EM_count++;
		if(DEBUGleptons)std::cout << " -----> isEM " << std::endl;
		Nem[Nel_tight_top2 + Nmu_tight_top2]++;
		if (tightLepCounter==3){ isTT=1; if(DEBUGleptons)std::cout << " -----> isTT " << std::endl;}
		if (tightLepCounter==2){ isTL=1; if(DEBUGleptons)std::cout << " -----> isTL " << std::endl;}
		if (tightLepCounter==1){ isLT=1; if(DEBUGleptons)std::cout << " -----> isLT " << std::endl;}
		if (tightLepCounter==0){ isLL=1; if(DEBUGleptons)std::cout << " -----> isLL " << std::endl;}
		// if (tightLepCounter==4){ isTLL=1; if(DEBUGleptons)std::cout << " -----> isTLL " << std::endl;}
		// if (tightLepCounter==2){ isLTL=1; if(DEBUGleptons)std::cout << " -----> isLTL " << std::endl;}
		// if (tightLepCounter==1){ isLLT=1; if(DEBUGleptons)std::cout << " -----> isLLT " << std::endl;}
		// if (tightLepCounter==0){ isLLL=1; if(DEBUGleptons)std::cout << " -----> isLLL " << std::endl;}
      }
      if(Nel_top2==0){
		isMM = 1;
		MM_count++;
		if(DEBUGleptons)std::cout << " -----> isMM " << std::endl;
		Nmm[Nmu_tight_top2]++;
		if (tightLepCounter==3){ isTT=1; if(DEBUGleptons)std::cout << " -----> isTT " << std::endl;}
		if (tightLepCounter==2){ isTL=1; if(DEBUGleptons)std::cout << " -----> isTL " << std::endl;}
		if (tightLepCounter==1){ isLT=1; if(DEBUGleptons)std::cout << " -----> isLT " << std::endl;}
		if (tightLepCounter==0){ isLL=1; if(DEBUGleptons)std::cout << " -----> isLL " << std::endl;}
		// if (tightLepCounter==4){ isTLL=1; if(DEBUGleptons)std::cout << " -----> isTLL " << std::endl;}
		// if (tightLepCounter==2){ isLTL=1; if(DEBUGleptons)std::cout << " -----> isLTL " << std::endl;}
		// if (tightLepCounter==1){ isLLT=1; if(DEBUGleptons)std::cout << " -----> isLLT " << std::endl;}
		// if (tightLepCounter==0){ isLLL=1; if(DEBUGleptons)std::cout << " -----> isLLL " << std::endl;}
      }
      // if(Nel_top3==0){
      // 		isMMM = 1;
      // 		MMM_count++;
      // 		if(DEBUGleptons)std::cout << " -----> isMMM " << std::endl;
      // 		Nmmm[Nmu_tight_top3]++;
      // 		if (tightLepCounter==7){ isTTT=1; if(DEBUGleptons)std::cout << " -----> isTTT " << std::endl;}
      // 		if (tightLepCounter==6){ isTTL=1; if(DEBUGleptons)std::cout << " -----> isTTL " << std::endl;}
      // 		if (tightLepCounter==5){ isTLT=1; if(DEBUGleptons)std::cout << " -----> isTLT " << std::endl;}
      // 		if (tightLepCounter==3){ isLTT=1; if(DEBUGleptons)std::cout << " -----> isLTT " << std::endl;}
      // 		if (tightLepCounter==4){ isTLL=1; if(DEBUGleptons)std::cout << " -----> isTLL " << std::endl;}
      // 		if (tightLepCounter==2){ isLTL=1; if(DEBUGleptons)std::cout << " -----> isLTL " << std::endl;}
      // 		if (tightLepCounter==1){ isLLT=1; if(DEBUGleptons)std::cout << " -----> isLLT " << std::endl;}
      // 		if (tightLepCounter==0){ isLLL=1; if(DEBUGleptons)std::cout << " -----> isLLL " << std::endl;}
      // }
		
      
      isPassDilepton = false;
      if(Nel_tight_top2 + Nmu_tight_top2 >= 2){
		nPassDilepton++;
		//isPassTrilepton = true;
		if(DEBUGleptons)std::cout << "pass dilepton cut! (2 tight leptons)" << endl;
      }
      else{
      	if(DEBUGleptons)std::cout << "fail dilepton cut! (no 2 tight leptons), must be for ddbkg?" << endl;
      }
      
	     
      //Determine bkgweights here IF processing DATA. - start
      const int nmodes = 9;
      //mode 0 = nominal. 1 = elfakerate plus, 2 = elfakerate minus, 3 = elpassrate plus, 4 = elpassrate minus, 5 = mufakerate plus, 6 = mufakerate minus, 7 = mupassrate plus, 8 = mupassrate minus
      //see feModeBehavior in fakerate.h

      double bkgweights[nmodes] = {0};
      double bkgweight = 0.;
      ddBkgWeights.clear();
      ddBkgWeights_scan.clear();

      if(!isMC){
	
			vector<double> lep1_info,lep2_info; //at(0): isMu, at(1): isTight, at(2): pt, at(3): eta
			lep1_info.push_back(AllLeptonFlavor_PtOrdered.at(0));lep1_info.push_back(AllLeptonIsTight_PtOrdered.at(0));lep1_info.push_back(AllLeptonPt_PtOrdered.at(0));lep1_info.push_back(AllLeptonEta_PtOrdered.at(0));
			lep2_info.push_back(AllLeptonFlavor_PtOrdered.at(1));lep2_info.push_back(AllLeptonIsTight_PtOrdered.at(1));lep2_info.push_back(AllLeptonPt_PtOrdered.at(1));lep2_info.push_back(AllLeptonEta_PtOrdered.at(1));
			// lep3_info.push_back(AllLeptonFlavor_PtOrdered.at(2));lep3_info.push_back(AllLeptonIsTight_PtOrdered.at(2));lep3_info.push_back(AllLeptonPt_PtOrdered.at(2));lep3_info.push_back(AllLeptonEta_PtOrdered.at(2));
			for(int imode=0;imode<nmodes;imode++){
				if(DEBUGddbkg) cout << "" << endl;
				bkgweights[imode] = GetWeight(imode, lep1_info, lep2_info);
			}
			
			//ddbkgweight scan -start
			
			//add mu FR at(4) and initialize to be 0.
			lep1_info.push_back(0.);
			lep2_info.push_back(0.);
			//lep3_info.push_back(0.);

			//add el FR at(5) and initialize to be 0.
			lep1_info.push_back(0.);
			lep2_info.push_back(0.);
			//lep3_info.push_back(0.);
			
			float increment = 0.01;
			double initial = 0.0;
			double end = 0.5;
			int loop = (int) ( ( end - initial ) / increment ) + 1;
			
			double muFR = 0.; 
			double elFR = 0.; 
			
			bool scaleFR = false;
			double Zjet_ratio = 1.;
			double ttx_ratio = 1.;
			string whichRatio;
// 			whichRatio = "CR1CR2"; //To measure CR2 by fitting CR1
			whichRatio = "CR2CR1"; //To measure CR1 by fitting CR2
// 			whichRatio = "CR2SR"; //To measure SR by fitting CR2
			if(scaleFR && whichRatio=="CR1CR2") Zjet_ratio = 7.46/4.78;
			if(scaleFR && whichRatio=="CR1CR2") ttx_ratio = 72.59/77.52;
			bool CR2CR1 = false;
			if(scaleFR && whichRatio=="CR2CR1") Zjet_ratio = 4.78/7.46;
			if(scaleFR && whichRatio=="CR2CR1") ttx_ratio = 77.52/72.59;
			bool CR2SR = false;
			if(scaleFR && whichRatio=="CR2SR") Zjet_ratio = 4.78/4.84;
			if(scaleFR && whichRatio=="CR2SR") ttx_ratio = 77.52/86.55;
			if(DEBUGddbkgScan&&scaleFR) cout << "ATTENTION: scaling FR!! "<< whichRatio << " el FR by Zjet_ratio = "<< Zjet_ratio<< ", and mu FR by ttx_ratio = "<<ttx_ratio << endl;

			if(DEBUGddbkgScan) cout << "scanning ddbkg for each muFR and elFR from " << initial << " to " << end << " with increment of "<< increment <<"(" <<loop <<" loops) ." << endl;
			if(DEBUGddbkgScan) cout << "" << endl;	
			int counter = 0;
			for(float i=0; i < loop; i++){
				
				muFR = initial + i*increment;
				
				if(DEBUGddbkgScan) cout << "i = " << i << ", muFR = "<< muFR * ttx_ratio << endl;	

				lep1_info.at(4)=muFR * ttx_ratio;
				lep2_info.at(4)=muFR * ttx_ratio;
				//lep3_info.at(4)=muFR * ttx_ratio;				

				for(float j=0; j < loop; j++){

					elFR = initial + j*increment;
				
					if(DEBUGddbkgScan) cout << "j = " << j << ", elFR = "<< elFR * Zjet_ratio << endl;	
			
					lep1_info.at(5)=elFR * Zjet_ratio;
					lep2_info.at(5)=elFR * Zjet_ratio;
					//lep3_info.at(5)=elFR * Zjet_ratio;				
				
					if(DEBUGddbkgScan) cout << "lep1_info.at(4) = "<< lep1_info.at(4) <<", lep1_info.at(5) ="<< lep1_info.at(5) << endl;	
					if(DEBUGddbkgScan) cout << "lep2_info.at(4) = "<< lep2_info.at(4) <<", lep2_info.at(5) ="<< lep2_info.at(5)   <<endl;	
					//if(DEBUGddbkgScan) cout << "lep3_info.at(4) = "<< lep3_info.at(4) <<", lep3_info.at(5) ="<< lep3_info.at(5)   <<endl;	
								
					bkgweight = GetWeight(0, lep1_info, lep2_info);
				
					ddBkgWeights_scan.push_back(bkgweight);
				
					ddBkgWeights_scan_muFR.push_back(muFR);
					ddBkgWeights_scan_elFR.push_back(elFR);
					if(DEBUGddbkgScan) cout << counter <<". bkgweight (muFR = "<< ddBkgWeights_scan_muFR.at(counter) << ", elFR = "<< ddBkgWeights_scan_elFR.at(counter) << ") = "<< ddBkgWeights_scan.at(counter) <<endl;	
					
					counter++;
					
					if(DEBUGddbkgScan) cout << "" << endl;	

				}
				
				double elFR = 0.; 
				
			}
			//ddbkgweight scan -end

      }//end make background weights.
            
      if(DEBUGddbkg)for(int imode=0;imode<nmodes;imode++)cout << "bkgweights["<<imode<<"] = "<< bkgweights[imode]<<endl;	

      
      for(int imode=0; imode<nmodes;imode++){ddBkgWeights.push_back(bkgweights[imode]);}
			      
      //Determine bkgweights here IF processing DATA. - end
      
      if(DEBUG)std::cout<<"Rizki A - end"<<std::endl;
      
      // ---- Rizki - end

      // ----------------------------------------------------------------------------
      // Pileup weight calculation
      // ----------------------------------------------------------------------------

      pileupWeight = 1.0;
      pileupWeightUp = 1.0;
      pileupWeightDown = 1.0;
      
      if(nTrueInteractions_singleLepCalc > 79) nTrueInteractions_singleLepCalc = 79;
      pileupWeight = pileup_central[nTrueInteractions_singleLepCalc];
      pileupWeightUp = pileup_down[nTrueInteractions_singleLepCalc];
      pileupWeightDown = pileup_up[nTrueInteractions_singleLepCalc];

      // ----------------------------------------------------------------------------
      // Assign Lepton scale factor or efficiency weights, save trigger pass/fail
      // ----------------------------------------------------------------------------

      DataPastTrigger = 0;
      DataPastTriggerAlt = 0;
      MCPastTrigger = 0;
      MCPastTriggerAlt = 0;
      TrigEffAltWeight = 1.0;
      TrigEffWeight = 1.0;
      TrigEffWeightUncert = 1.0;
      isoSF = 1.0;
      lepIdSF = 1.0;
      EGammaGsfSF = 1.0;
      MuTrkSF = 1.0;
            
      //Rizki - start

      if(DEBUG)std::cout<<"Rizki B - start"<<std::endl;      

      int   isPastTrig = 0;
      int   isPastTrigAlt = 0;
      int   isPastTrigMC = 0;
      int   isPastTrigMCAlt = 0;
 
      //      int   isPastTrig_trilep = 0;
      //int   isPastTrigMC_trilep = 0;
      int   isPastTrig_dilep = 0;
      int   isPastTrigMC_dilep = 0;
      int   isPastTrig_dilepDZ4runH = 0;
      int   isPastTrigMC_dilepDZ4runH = 0;
      int   isPastTrig_dilepHT = 0;
      int   isPastTrigMC_dilepHT = 0;

      float TrigEffAlt = 1.0;
      float TrigEff = 1.0;
      float isosf = 1.0;
      float lepidsf = 1.0;

      if(isMC){ //MC triggers check
      
		if(DEBUGTriggers){
			for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
				if(viSelMCTriggersEl_singleLepCalc->at(itrig) > 0) std::cout << "pass El MC trigger : " << vsSelMCTriggersEl_singleLepCalc->at(itrig) << std::endl;
				}
			for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
				if(viSelMCTriggersMu_singleLepCalc->at(itrig) > 0) std::cout << "pass Mu MC trigger : " << vsSelMCTriggersMu_singleLepCalc->at(itrig) << std::endl;
				}
		}

		if(DEBUG)std::cout<<"Matching with desired MC trigger selection..."<<std::endl;  

   		if(isEE){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively electron triggers
						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //||

						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// 						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

					) &&  viSelMCTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
					isPastTrigMC_dilepDZ4runH = 1;
				}
				if( ( 
						//exclusively electron triggers
						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v") != std::string::npos) //||

						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// 						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

					) &&  viSelMCTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilepHT = 1;
				}
				// if( (
// 						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v") != std::string::npos) //||

// 						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// // 						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos)

// 					) &&  viSelMCTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
// 					isPastTrigMC = 1;
// 					//isPastTrigMC_trilep = 1;
// 				}
			}
	  	}
   		if(isEM){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersEl_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively electron triggers
						//( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) ||

						//el&mu triggers
						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v") != std::string::npos) ||
						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v") != std::string::npos) //||
						
						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// 						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

					) &&  viSelMCTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if( ( //with DZ cut for runH : attention in LJMET sone are saved as DZ not DZ_v !!!
						//exclusively electron triggers
						//( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) ||

						//el&mu triggers
						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) || //use DZ for run2016H has this version
						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //|| //use DZ for run2016H has this version
						
						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// 						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

					) &&  viSelMCTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilepDZ4runH = 1;
				}
				if( ( 
						//exclusively electron triggers
						//( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v") != std::string::npos) ||

						//el&mu triggers
						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v") != std::string::npos) //||
						
						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// 						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

					) &&  viSelMCTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilepHT = 1;
				}
				// if( (
// 						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v") != std::string::npos)  //||

// 						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// // 						( vsSelMCTriggersEl_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

// 					) &&  viSelMCTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
// 					isPastTrigMC = 1;
// 					//isPastTrigMC_trilep = 1;
// 				}
			}
	  	}
   		if(isMM){
		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively muon triggers
				     ( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v") != std::string::npos) //|| 	

						//el&mu triggers
						//( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v") != std::string::npos) ||
						//( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v") != std::string::npos) //||

						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

					) &&  viSelMCTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilep = 1;
				}
				if( ( //with DZ cut for runH : attention in LJMET sone are saved as DZ not DZ_v !!!
						//exclusively muon triggers
				     ( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ") != std::string::npos) //|| //use DZ for run2016H has this version 	

						//el&mu triggers
						//( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) || //ATTENTION!! //use DZ for run2016H has this version
						//( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //|| //use DZ for run2016H has this version

						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

					) &&  viSelMCTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilepDZ4runH = 1;
				}
				if( ( 
						//exclusively muon triggers
				     ( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_DoubleMu8_Mass8_PFHT300_v") != std::string::npos) //|| 	

						//el&mu triggers
						//( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v") != std::string::npos) //||

						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

					) &&  viSelMCTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrigMC = 1;
					isPastTrigMC_dilepHT = 1;
				}
				// if( (
// 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v") != std::string::npos) //||

// 						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// // 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

// 					) &&  viSelMCTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
// 					isPastTrigMC = 1;
// 					//	isPastTrigMC_trilep = 1;
// 				}
			}
	  	}
   		// if(isMMM){
// 		  	for(unsigned int itrig=0; itrig < vsSelMCTriggersMu_singleLepCalc->size(); itrig++){
// 				if( ( 
// 						//exclusively muon triggers
// 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v") != std::string::npos) //|| 	

// 						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// // 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

// 					) &&  viSelMCTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
// 					isPastTrigMC = 1;
// 					isPastTrigMC_dilep = 1;
// 		  			if(DEBUGTriggers)std::cout << "vsSelMCTriggersMu_singleLepCalc->at(itrig) = " << vsSelMCTriggersMu_singleLepCalc->at(itrig) << std::endl;
// 					if(DEBUGTriggers)std::cout << "isPastTrigMC ="<< isPastTrigMC << ", isPastTrigMC_dilep = " << isPastTrigMC_dilep << ", isPastTrigMC_trilep = " << isPastTrigMC_trilep << std::endl;
// 				}
// 				if( ( //with DZ cut for runH : attention in LJMET sone are saved as DZ not DZ_v !!!
// 						//exclusively muon triggers
// 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ") != std::string::npos) //|| //use DZ for run2016H has this version

// 						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// // 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

// 					) &&  viSelMCTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
// 					isPastTrigMC = 1;
// 					isPastTrigMC_dilepDZ4runH = 1;
// 		  			if(DEBUGTriggers)std::cout << "vsSelMCTriggersMu_singleLepCalc->at(itrig) = " << vsSelMCTriggersMu_singleLepCalc->at(itrig) << std::endl;
// 					if(DEBUGTriggers)std::cout << "isPastTrigMC ="<< isPastTrigMC << ", isPastTrigMC_dilepDZ4runH = " << isPastTrigMC_dilepDZ4runH << ", isPastTrigMC_trilep = " << isPastTrigMC_trilep << std::endl;
// 				}
// 				if( ( 
// 						//exclusively muon triggers
// 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_DoubleMu8_Mass8_PFHT300_v") != std::string::npos) //|| 	

// 						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// // 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

// 					) &&  viSelMCTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
// 					isPastTrigMC = 1;
// 					isPastTrigMC_dilepHT = 1;
// 		  			if(DEBUGTriggers)std::cout << "vsSelMCTriggersMu_singleLepCalc->at(itrig) = " << vsSelMCTriggersMu_singleLepCalc->at(itrig) << std::endl;
// 					if(DEBUGTriggers)std::cout << "isPastTrigMC ="<< isPastTrigMC << ", isPastTrigMC_dilep = " << isPastTrigMC_dilep << ", isPastTrigMC_trilep = " << isPastTrigMC_trilep << std::endl;
// 				}
// 				if( (
// 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("HLT_TripleMu_12_10_5_v") != std::string::npos) //||

// 						//ATTENTION! --> Moriond MC BKG now has trigger info ! MC Signal has trig info.
// // 						( vsSelMCTriggersMu_singleLepCalc->at(itrig).find("digitisation_step") != std::string::npos) 	

// 					) &&  viSelMCTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
// 					isPastTrigMC = 1;
// 					isPastTrigMC_trilep = 1;
// 		  			if(DEBUGTriggers)std::cout << "vsSelMCTriggersMu_singleLepCalc->at(itrig) = " << vsSelMCTriggersMu_singleLepCalc->at(itrig) << std::endl;
// 					if(DEBUGTriggers)std::cout << "isPastTrigMC ="<< isPastTrigMC << ", isPastTrigMC_dilep = " << isPastTrigMC_dilep << ", isPastTrigMC_trilep = " << isPastTrigMC_trilep << std::endl;
// 				}
// 			}
		//}

		if(DEBUG||DEBUGTriggers)std::cout<< "isPastTrigMC_dilep = " << isPastTrigMC_dilep <<std::endl;  
		if(DEBUG||DEBUGTriggers)std::cout<< "isPastTrigMC_dilepHT = " << isPastTrigMC_dilepHT <<std::endl;  

		if(DEBUG)std::cout<<"Done matching with desired MC trigger selection..."<<std::endl;  

		// APPLY SCALE FACTORS PER EVENT
		for(unsigned int ilep = 0; ilep < TightLeptonPt_PtOrdered.size(); ilep++){
		  double lepeta = TightLeptonEta_PtOrdered.at(ilep);
		  double leppt = TightLeptonPt_PtOrdered.at(ilep);

		  //////// ELECTRONS	  
		  if(TightLeptonFlavor_PtOrdered.at(ilep) == 0){

			//NEED SOME TRIGGER SF/EFFIENCIESS!!

			  // Gsf Tracking scale factor: http://fcouderc.web.cern.ch/fcouderc/EGamma/scaleFactors/Moriond17/approval/RECO/passingRECO/egammaEffi.txt_egammaPlots.pdf
			  if(lepeta < -2.45) EGammaGsfSF *= 1.318;
			  else if(lepeta < -2.4) EGammaGsfSF *= 1.114;
			  else if(lepeta < -2.3) EGammaGsfSF *= 1.025;
			  else if(lepeta < -2.2) EGammaGsfSF *= 1.014;
			  else if(lepeta < -2.0) EGammaGsfSF *= 1.007;
			  else if(lepeta < -1.8) EGammaGsfSF *= 0.995;
			  else if(lepeta < -1.65) EGammaGsfSF *= 0.995;
			  else if(lepeta < -1.566) EGammaGsfSF *= 0.992;
			  else if(lepeta < -1.4442) EGammaGsfSF *= 0.963;
			  else if(lepeta < -1.2) EGammaGsfSF *= 0.990;
			  else if(lepeta < -1.0) EGammaGsfSF *= 0.986;
			  else if(lepeta < -0.6) EGammaGsfSF *= 0.982;
			  else if(lepeta < -0.4) EGammaGsfSF *= 0.985;
			  else if(lepeta < -0.2) EGammaGsfSF *= 0.982;
			  else if(lepeta < 0.0) EGammaGsfSF *= 0.980;
			  else if(lepeta < 0.2) EGammaGsfSF *= 0.985;
			  else if(lepeta < 0.4) EGammaGsfSF *= 0.989;
			  else if(lepeta < 0.6) EGammaGsfSF *= 0.988;
			  else if(lepeta < 1.0) EGammaGsfSF *= 0.988;
			  else if(lepeta < 1.2) EGammaGsfSF *= 0.988;
			  else if(lepeta < 1.4442) EGammaGsfSF *= 0.988;
			  else if(lepeta < 1.566) EGammaGsfSF *= 0.968;
			  else if(lepeta < 1.65) EGammaGsfSF *= 0.990;
			  else if(lepeta < 1.8) EGammaGsfSF *= 0.993;
			  else if(lepeta < 2.0) EGammaGsfSF *= 0.992;
			  else if(lepeta < 2.2) EGammaGsfSF *= 0.998;
			  else if(lepeta < 2.3) EGammaGsfSF *= 1.001;
			  else if(lepeta < 2.4) EGammaGsfSF *= 0.990;
			  else if(lepeta < 2.45) EGammaGsfSF *= 0.971;
			  else EGammaGsfSF *= 0.907;
		  
/*
pT:25 bin:1
pT:30 bin:2
pT:40 bin:3
pT:50 bin:4
pT:60 bin:5
pT:100 bin:6
pT:200 bin:7
*/

/*
eta:-2.5 bin:1
eta:-2 bin:2
eta:-1.56 bin:3
eta:-1.44 bin:4
eta:-0.8 bin:5
eta:0 bin:6
eta:0.8 bin:7
eta:1.44 bin:8
eta:1.56 bin:9
eta:2 bin:10
eta:2.5 bin:11
*/
			  //miniIso < 0.1 scale factors from Julie - see email 23 Jan 2017 - https://mail.google.com/mail/u/0/#search/electron+julie/159cd256f91b7bc4
			  if(fabs(lepeta) < 0.8){
				if(leppt < 30) isoSF *= 0.998895;
				else if(leppt < 40) isoSF *= 0.99895;
				else if(leppt < 50) isoSF *= 0.998976;
				else if(leppt < 60) isoSF *= 0.99797;
				else if(leppt < 100) isoSF *= 0.998991;
				else if(leppt < 200) isoSF *= 1.00201;
				else isoSF *= 1.00101;
			  }
			  else if(fabs(lepeta) < 1.4442){
				if(leppt < 30) isoSF *= 1.00548;
				else if(leppt < 40) isoSF *= 1;
				else if(leppt < 50) isoSF *= 1;
				else if(leppt < 60) isoSF *= 1;
				else if(leppt < 100) isoSF *= 1;
				else if(leppt < 200) isoSF *= 1.00201;
				else isoSF *= 0.999;
			  }
			  else if(fabs(lepeta) < 1.566){
				if(leppt < 30) isoSF *= 1.03018;
				else if(leppt < 40) isoSF *= 1.02317;
				else if(leppt < 50) isoSF *= 1.00551;
				else if(leppt < 60) isoSF *= 1.00109;
				else if(leppt < 100) isoSF *= 1.0195;
				else if(leppt < 200) isoSF *= 1.0062;
				else isoSF *= 1.07296;
			  }
			  else if(fabs(lepeta) < 2.0){
				if(leppt < 30) isoSF *= 0.992432;
				else if(leppt < 40) isoSF *= 0.997912;
				else if(leppt < 50) isoSF *= 0.996942;
				else if(leppt < 60) isoSF *= 0.998989;
				else if(leppt < 100) isoSF *= 0.998995;
				else if(leppt < 200) isoSF *= 1;
				else isoSF *= 0.998;
			  }
			  else {
				if(leppt < 30) isoSF *= 0.978237;
				else if(leppt < 40) isoSF *= 0.987448;
				else if(leppt < 50) isoSF *= 0.99285;
				else if(leppt < 60) isoSF *= 0.997978;
				else if(leppt < 100) isoSF *= 1.00101;
				else if(leppt < 200) isoSF *= 1;
				else isoSF *= 0.997;
			  }

			  //MVA-based ID scale factors for Custom WP from Julie - see email 23 Jan 2017 - https://mail.google.com/mail/u/0/#search/electron+julie/159cd256f91b7bc4
			  if(fabs(lepeta) < 0.8){
				if(leppt < 30) lepIdSF *= 0.96468;
				else if(leppt < 40) lepIdSF *= 0.970716;
				else if(leppt < 50) lepIdSF *= 0.973262;
				else if(leppt < 60) lepIdSF *= 0.973376;
				else if(leppt < 100) lepIdSF *= 0.976571;
				else if(leppt < 200) lepIdSF *= 0.985122;
				else lepIdSF *= 0.984979;
			  }
			  else if(fabs(lepeta) < 1.4442){
				if(leppt < 30) lepIdSF *= 0.935174;
				else if(leppt < 40) lepIdSF *= 0.946512;
				else if(leppt < 50) lepIdSF *= 0.952273;
				else if(leppt < 60) lepIdSF *= 0.951302;
				else if(leppt < 100) lepIdSF *= 0.95618;
				else if(leppt < 200) lepIdSF *= 0.974157;
				else lepIdSF *= 0.941501;
			  }
			  else if(fabs(lepeta) < 1.566){
				if(leppt < 30) lepIdSF *= 0.904402;
				else if(leppt < 40) lepIdSF *= 0.929952;
				else if(leppt < 50) lepIdSF *= 0.938444;
				else if(leppt < 60) lepIdSF *= 0.943483;
				else if(leppt < 100) lepIdSF *= 0.932028;
				else if(leppt < 200) lepIdSF *= 0.982974;
				else lepIdSF *= 1.03924;
			  }
			  else if(fabs(lepeta) < 2.0){
				if(leppt < 30) lepIdSF *= 0.935412;
				else if(leppt < 40) lepIdSF *= 0.947484;
				else if(leppt < 50) lepIdSF *= 0.964516;
				else if(leppt < 60) lepIdSF *= 0.970149;
				else if(leppt < 100) lepIdSF *= 0.971368;
				else if(leppt < 200) lepIdSF *= 0.991605;
				else lepIdSF *= 1.00952;
			  }
			  else {
				if(leppt < 30) lepIdSF *= 0.947066;
				else if(leppt < 40) lepIdSF *= 0.96288;
				else if(leppt < 50) lepIdSF *= 0.970427;
				else if(leppt < 60) lepIdSF *= 0.972826;
				else if(leppt < 100) lepIdSF *= 0.978448;
				else if(leppt < 200) lepIdSF *= 1.01289;
				else lepIdSF *= 0.971398;
			  }
		
		  }

		  //////// MUONS
		  if(TightLeptonFlavor_PtOrdered.at(ilep) == 1){

			//NEED SOME TRIGGER SF/EFFIENCIESS!!

			  // Muon tracking SF -- https://twiki.cern.ch/twiki/bin/viewauth/CMS/MuonWorkInProgressAndPagResults#Results_on_the_full_2016_data, Feb 16 version for full data
			  int ebin = -1;
			  if(lepeta < -2.1) ebin = 0;
			  else if(lepeta < -1.6) ebin = 1;
			  else if(lepeta < -1.2) ebin = 2;
			  else if(lepeta < -0.9) ebin = 3;
			  else if(lepeta < -0.6) ebin = 4;
			  else if(lepeta < -0.3) ebin = 5;
			  else if(lepeta < -0.2) ebin = 6;
			  else if(lepeta <  0.2) ebin = 7;
			  else if(lepeta <  0.3) ebin = 8;
			  else if(lepeta <  0.6) ebin = 9;
			  else if(lepeta <  0.9) ebin = 10;
			  else if(lepeta <  1.2) ebin = 11;
			  else if(lepeta <  1.6) ebin = 12;
			  else if(lepeta <  2.1) ebin = 13;
			  else if(lepeta <  2.4) ebin = 14;

			  MuTrkSF *= tracksf[ebin];

			  //New MorindMC SF for MiniIso<0.1 Clint calculated on https://indico.cern.ch/event/605620/contributions/2441087/attachments/1398025/2132153/VHFMeeting_X53_01.18.17.pdf 
			  if(leppt < 40){
				if(fabs(lepeta) < 0.9) isoSF*= 1.000;
				else if(fabs(lepeta) <  1.2) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.1) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.4) isoSF*= 0.999;
			  }
			  else if(leppt < 50){
				if(fabs(lepeta) < 0.9) isoSF*= 0.999;
				else if(fabs(lepeta) <  1.2) isoSF*= 0.999;
				else if(fabs(lepeta) <  2.1) isoSF*= 0.999;
				else if(fabs(lepeta) <  2.4) isoSF*= 0.999;
			  }
			  else if(leppt < 60){
				if(fabs(lepeta) < 0.9) isoSF*= 0.999;
				else if(fabs(lepeta) <  1.2) isoSF*= 0.999;
				else if(fabs(lepeta) <  2.1) isoSF*= 0.999;
				else if(fabs(lepeta) <  2.4) isoSF*= 1.000;
			  }
			  else if(leppt < 100){
				if(fabs(lepeta) < 0.9) isoSF*= 1.000;
				else if(fabs(lepeta) <  1.2) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.1) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.4) isoSF*= 1.000;
			  }
			  else{
				if(fabs(lepeta) < 0.9) isoSF*= 1.000;
				else if(fabs(lepeta) <  1.2) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.1) isoSF*= 1.000;
				else if(fabs(lepeta) <  2.4) isoSF*= 1.000;
			  }
	  
			  //Cut-based Tight scale factors from Clint's 18Jan2017 calculated on https://indico.cern.ch/event/605620/contributions/2441087/attachments/1398025/2132153/VHFMeeting_X53_01.18.17.pdf
			  if(fabs(lepeta) < 0.9){
				if(leppt < 40) lepIdSF *= 0.983;
				else if(leppt < 50) lepIdSF *= 0.983;
				else if(leppt < 60) lepIdSF *= 0.976;
				else if(leppt < 100) lepIdSF *= 0.961;
				else lepIdSF *= 0.998;
			  }
			  else if(fabs(lepeta) < 1.2){
				if(leppt < 40) lepIdSF *= 0.971;
				else if(leppt < 50) lepIdSF *= 0.972;
				else if(leppt < 60) lepIdSF *= 0.973;
				else if(leppt < 100) lepIdSF *= 0.961;
				else lepIdSF *= 0.992;
			  }
			  else if(fabs(lepeta) < 2.1){
				if(leppt < 40) lepIdSF *= 0.987;
				else if(leppt < 50) lepIdSF *= 0.987;
				else if(leppt < 60) lepIdSF *= 0.985;
				else if(leppt < 100) lepIdSF *= 0.970;
				else lepIdSF *= 1.003;
			  }
			  else {
				if(leppt < 40) lepIdSF *= 0.971;
				else if(leppt < 50) lepIdSF *= 0.972;
				else if(leppt < 60) lepIdSF *= 0.968;
				else if(leppt < 100) lepIdSF *= 0.953;
				else lepIdSF *= 0.986;
			  }
			  
		  }
		}
		
		isPastTrig = 1;
		isPastTrigAlt = 1; 
		//		isPastTrig_trilep = 1;
		isPastTrig_dilep = 1;
		isPastTrig_dilepDZ4runH = 1;
		isPastTrig_dilepHT = 1;
		
      }
      else{ //Data triggers check

		if(DEBUGTriggers){      	
			for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
				if(viSelTriggersEl_singleLepCalc->at(itrig) > 0) std::cout << "pass El trigger : " << vsSelTriggersEl_singleLepCalc->at(itrig) << std::endl;
				}
			for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
				if(viSelTriggersMu_singleLepCalc->at(itrig) > 0) std::cout << "pass Mu trigger : " << vsSelTriggersMu_singleLepCalc->at(itrig) << std::endl;
				}
		}

		if(DEBUG)std::cout<<"Matching with desired trigger selection..."<<std::endl;  
    	
   		if(isEE){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively electron triggers
						( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //||

					) &&  viSelTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
					isPastTrig_dilepDZ4runH = 1;
				}
				if( ( 
						//exclusively electron triggers
						( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v") != std::string::npos) //||

					) &&  viSelTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilepHT = 1;
				}
				// if( (
				// 		( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele16_Ele12_Ele8_CaloIdL_TrackIdL_v") != std::string::npos) 
				// 	) &&  viSelTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
				// 	isPastTrig = 1;
				// 	isPastTrig_trilep = 1;
				// }
			}
	  	}
   		if(isEM){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersEl_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively electron triggers
						//( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) ||

						//el&mu triggers
						( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v") != std::string::npos) ||
						( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v") != std::string::npos) //||

					) &&  viSelTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if( ( //with DZ cut for runH : attention in LJMET sone are saved as DZ not DZ_v !!!
						//exclusively electron triggers
						//( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Ele23_Ele12_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) ||

						//el&mu triggers
						( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) || //only run2016H has this version!!
						( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //|| //use DZ for run2016H has this version

					) &&  viSelTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilepDZ4runH = 1;
				}
				if( ( 
						//exclusively electron triggers
						//( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_DoubleEle8_CaloIdM_TrackIdM_Mass8_PFHT300_v") != std::string::npos) ||

						//el&mu triggers
						( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v") != std::string::npos) //||

					) &&  viSelTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilepHT = 1;
				}
				// if( (
				// 		( vsSelTriggersEl_singleLepCalc->at(itrig).find("HLT_Mu8_DiEle12_CaloIdL_TrackIdL_v") != std::string::npos) 
				// 	) &&  viSelTriggersEl_singleLepCalc->at(itrig) > 0 ) { 
				// 	isPastTrig = 1;
				// 	isPastTrig_trilep = 1;
				// }
			}
	  	}
   		if(isMM){
		  	for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
				if( ( 
						//exclusively muon triggers
				     ( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v") != std::string::npos) //|| 	

						//el&mu triggers
						//( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_v") != std::string::npos) ||
						//( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_v") != std::string::npos) //||

					) &&  viSelTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilep = 1;
				}
				if( ( //with DZ cut for runH : attention in LJMET sone are saved as DZ not DZ_v !!!
						//exclusively muon triggers
				     ( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ") != std::string::npos) //|| //use DZ for run2016H has this version

						//el&mu triggers
						//( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu8_TrkIsoVVL_Ele23_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) || //use DZ for run2016H has this version
						//( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu23_TrkIsoVVL_Ele8_CaloIdL_TrackIdL_IsoVL_DZ") != std::string::npos) //|| //use DZ for run2016H has this version

					) &&  viSelTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilepDZ4runH = 1;
				}
				if( ( 
						//exclusively muon triggers
				     ( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_DoubleMu8_Mass8_PFHT300_v") != std::string::npos) //|| 	

						//el&mu triggers
						//( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu8_Ele8_CaloIdM_TrackIdM_Mass8_PFHT300_v") != std::string::npos) //||
					) &&  viSelTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
					isPastTrig = 1;
					isPastTrig_dilepHT = 1;
				}
				// if( (
				// 		( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_DiMu9_Ele9_CaloIdL_TrackIdL_v") != std::string::npos) 
				// 	) &&  viSelTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
				// 	isPastTrig = 1;
				// 	isPastTrig_trilep = 1;
				// }
			}
	  	}
   		// if(isMMM){
		//   	for(unsigned int itrig=0; itrig < vsSelTriggersMu_singleLepCalc->size(); itrig++){
		// 		if( ( 
		// 				//exclusively muon triggers
		// 				( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_v") != std::string::npos) //|| 	

		// 			) &&  viSelTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
		// 			isPastTrig = 1;
		// 			isPastTrig_dilep = 1;
		//   			if(DEBUGTriggers)std::cout << "vsSelTriggersMu_singleLepCalc->at(itrig) = " << vsSelTriggersMu_singleLepCalc->at(itrig) << std::endl;
		// 			if(DEBUGTriggers)std::cout << "isPastTrig ="<< isPastTrig << ", isPastTrig_dilep = " << isPastTrig_dilep << ", isPastTrig_trilep = " << isPastTrig_trilep << std::endl;
		// 		}
		// 		if( ( //with DZ cut for runH : attention in LJMET sone are saved as DZ not DZ_v !!!
		// 				//exclusively muon triggers
		// 				( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_Mu17_TrkIsoVVL_TkMu8_TrkIsoVVL_DZ") != std::string::npos) //|| //use DZ for run2016H has this version 	

		// 			) &&  viSelTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
		// 			isPastTrig = 1;
		// 			isPastTrig_dilepDZ4runH = 1;
		//   			if(DEBUGTriggers)std::cout << "vsSelTriggersMu_singleLepCalc->at(itrig) = " << vsSelTriggersMu_singleLepCalc->at(itrig) << std::endl;
		// 			if(DEBUGTriggers)std::cout << "isPastTrig ="<< isPastTrig << ", isPastTrig_dilepDZ4runH = " << isPastTrig_dilepDZ4runH << ", isPastTrig_trilep = " << isPastTrig_trilep << std::endl;
		// 		}
		// 		if( ( 
		// 				//exclusively muon triggers                      
		// 				( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_DoubleMu8_Mass8_PFHT300_v") != std::string::npos) //|| 	
		// 			) &&  viSelTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
		// 			isPastTrig = 1;
		// 			isPastTrig_dilepHT = 1;
		//   			if(DEBUGTriggers)std::cout << "vsSelTriggersMu_singleLepCalc->at(itrig) = " << vsSelTriggersMu_singleLepCalc->at(itrig) << std::endl;
		// 			if(DEBUGTriggers)std::cout << "isPastTrig ="<< isPastTrig << ", isPastTrig_dilep = " << isPastTrig_dilep << ", isPastTrig_trilep = " << isPastTrig_trilep << std::endl;
		// 		}
		// 		if( (
		// 				( vsSelTriggersMu_singleLepCalc->at(itrig).find("HLT_TripleMu_12_10_5_v") != std::string::npos) 
		// 			) &&  viSelTriggersMu_singleLepCalc->at(itrig) > 0 ) { 
		// 			isPastTrig = 1;
		// 			isPastTrig_trilep = 1;
		//   			if(DEBUGTriggers)std::cout << "vsSelTriggersMu_singleLepCalc->at(itrig) = " << vsSelTriggersMu_singleLepCalc->at(itrig) << std::endl;
		// 			if(DEBUGTriggers)std::cout << "isPastTrig ="<< isPastTrig << ", isPastTrig_dilep = " << isPastTrig_dilep << ", isPastTrig_trilep = " << isPastTrig_trilep << std::endl;
		// 		}
		// 	}
	  	// }

		if(DEBUG||DEBUGTriggers)std::cout<< "isPastTrig_dilep = " << isPastTrig_dilep <<std::endl;  
		if(DEBUG||DEBUGTriggers)std::cout<< "isPastTrig_dilepDZ4runH = " << isPastTrig_dilepDZ4runH <<std::endl;  
		if(DEBUG||DEBUGTriggers)std::cout<< "isPastTrig_dilepHT = " << isPastTrig_dilepHT <<std::endl;  

		if(DEBUG)std::cout<<"Matching with desired MC trigger selection..."<<std::endl;  

		isPastTrigMC = 1;
		isPastTrigMCAlt = 1; 
		//isPastTrigMC_trilep = 1;
		isPastTrigMC_dilep = 1;
		isPastTrigMC_dilepDZ4runH = 1;
		isPastTrigMC_dilepHT = 1;

      }
      
      if(isPastTrig) npass_trigger+=1;
      
      if(DataPastTrigger) npass_trigger+=1;
            
      if(DEBUG)std::cout<<"Rizki B - end"<<std::endl;      

      //Rizki - end
      

      // ----------------------------------------------------------------------------
      // Loop over AK4 jets for calculations and pt ordering pair
      // ----------------------------------------------------------------------------

      NJets_singleLepCalc = 0;
      AK4HT = 0;
      vector<pair<double,int>> jetptindpair;
      JetSF_pTNbwflat = 1.0;
      JetSFup_pTNbwflat = 1.0;
      JetSFdn_pTNbwflat = 1.0;
      JetSFupwide_pTNbwflat = 1.0;
      JetSFdnwide_pTNbwflat = 1.0;
      JetSF_80X = 1.0;
      JetSFup_80X = 1.0;
      JetSFdn_80X = 1.0;
      
      if(DEBUGjets)std::cout<< "AK4JetPt_singleLepCalc->size() (before jet loop) = " << AK4JetPt_singleLepCalc->size() << std::endl;

      for(unsigned int ijet=0; ijet < AK4JetPt_singleLepCalc->size(); ijet++){

		// ----------------------------------------------------------------------------
		// Basic cuts
		// ----------------------------------------------------------------------------
		if(DEBUG)std::cout<<"Basic cuts"<<std::endl;      

		if(AK4JetPt_singleLepCalc->at(ijet) < jetPtCut || fabs(AK4JetEta_singleLepCalc->at(ijet)) > jetEtaCut) continue;

		if(isMC){

		  // ----------------------------------------------------------------------------
		  // Jet Scale factor
		  // ----------------------------------------------------------------------------
		  if(DEBUG)std::cout<<"Jet Scale factor"<<std::endl;      

		  float one = 1.0;	    
		  float jetpt = AK4JetPt_singleLepCalc->at(ijet);
		  float jetsf = 1.09383 - 0.000477777*jetpt;
		  float jetsferr = sqrt(0.00314541714554 + 2.18390370364e-08*jetpt*jetpt + 2*jetpt*(-7.85447860996e-06));	 
		  float wideup = min(one,max(float(0.747382 + 0.164524),jetsf+jetsferr));				    
		  float widedn = min(one,max(jetsf-jetsferr,float(0.747382 - 0.164524)));
	  
		  if(isTOP || isSig){
			if(jetpt >= 200){
			  if(jetpt < 725){
				JetSF_pTNbwflat *= min(one,jetsf);
				JetSFup_pTNbwflat *= wideup;
				JetSFdn_pTNbwflat *= widedn;
				JetSFupwide_pTNbwflat *= wideup;
				JetSFdnwide_pTNbwflat *= widedn;
			  }else{
				JetSF_pTNbwflat *= 0.747382;
				JetSFup_pTNbwflat *= wideup;
				JetSFdn_pTNbwflat *= widedn;
				JetSFupwide_pTNbwflat *= wideup;
				JetSFdnwide_pTNbwflat *= widedn;
			  }
			}
		  }else{
			jetsf = 1.24507 - 0.000664768*jetpt;
			jetsferr = sqrt(0.000506216376592 + 3.1532423475e-09*jetpt*jetpt + 2*jetpt*(-1.17981363543e-06));
			if(jetpt < 1020){
			  JetSF_pTNbwflat *= min(one,jetsf);
			  JetSFup_pTNbwflat *= min(one,max(jetsf+jetsferr,float(0.568135+0.0522921)));
			  JetSFdn_pTNbwflat *= min(one,max(jetsf-jetsferr,float(0.568135-0.0522921)));
			  JetSFupwide_pTNbwflat *= max(wideup,min(one,max(jetsf+jetsferr,float(0.568135+0.0522921))));
			  JetSFdnwide_pTNbwflat *= min(widedn,min(one,max(jetsf-jetsferr,float(0.568135-0.0522921))));
			}else{
			  JetSF_pTNbwflat *= 0.568135;
			  JetSFup_pTNbwflat *= min(one,max(jetsf+jetsferr,float(0.568135+0.0522921)));
			  JetSFdn_pTNbwflat *= min(one,max(jetsf-jetsferr,float(0.568135-0.0522921)));
			  JetSFupwide_pTNbwflat *= max(wideup,min(one,max(jetsf+jetsferr,float(0.568135+0.0522921))));
			  JetSFdnwide_pTNbwflat *= min(widedn,min(one,max(jetsf-jetsferr,float(0.568135-0.0522921))));
			}
			jetsf = 1.09502 - 0.00045995*jetpt;
			jetsferr = sqrt(2.41563501145e-05 + 3.64859173927e-10*jetpt*jetpt + 2*jetpt*(-8.66909413702e-08));
			if(jetpt < 801.75){
			  JetSF_80X *= min(one,jetsf);
			  JetSFup_80X *= min(one,max(jetsf+jetsferr,float(0.726255+0.0190384)));
			  JetSFdn_80X *= min(one,max(jetsf-jetsferr,float(0.726255-0.0190384)));
			}else{
			  JetSF_80X *= 0.726255;
			  JetSFup_80X *= min(one,max(jetsf+jetsferr,float(0.726255+0.0190384)));
			  JetSFdn_80X *= min(one,max(jetsf-jetsferr,float(0.726255-0.0190384)));
			}
		  }
		  
		  /*
		  // ----------------------------------------------------------------------------
		  // B TAGGING fix -- not needed after LJMet from 8/1/16 (efficiency had a typo)
		  // ----------------------------------------------------------------------------
		  if(DEBUG)std::cout<<"B TAGGING fix"<<std::endl;      

		  float bSF = 1.0;
		  float bSFup = 1.0;
		  float bSFdn = 1.0;
		  double bEff = 1.0;
		  float lSF = 1.0;
		  float lSFup = 1.0;
		  float lSFdn = 1.0;
		  double lEff = 1.0;

		  // Set the initial tagged/untagged state
		  bool istagged = AK4JetBDisc_singleLepCalc->at(ijet) > 0.8484; //Medium WP as confirmed by Julie on 20th Jan 2017. But this is updated here on 23rd Jan 2017.

		  if(AK4JetFlav_singleLepCalc->at(ijet) == 5 || AK4JetFlav_singleLepCalc->at(ijet) == 4){	    

			int binSF = (std::upper_bound(ptRangeSF.begin(), ptRangeSF.end(), AK4JetPt_singleLepCalc->at(ijet))-ptRangeSF.begin())-1;
			float err = SFerr[binSF];
			if(AK4JetFlav_singleLepCalc->at(ijet) == 4) err *= 2;
			bSF = 0.901114+(1.32145e-05*AK4JetPt_singleLepCalc->at(ijet));	    
			bSFup = bSF + err;
			bSFdn = bSF - err;
	  
			int bin = (std::upper_bound(ptRangeEff.begin(), ptRangeEff.end(), AK4JetPt_singleLepCalc->at(ijet))-ptRangeEff.begin())-1;
			bEff = BtagEff[bin];
			if(AK4JetFlav_singleLepCalc->at(ijet) == 4) bEff *= 0.2;

			int tag = applySF(istagged,bSF,bEff);
			int tag_up = applySF(istagged,bSFup,bEff);
			int tag_dn = applySF(istagged,bSFdn,bEff);

			AK4JetBTag_singleLepCalc->at(ijet) = tag;
			AK4JetBTag_bSFup_singleLepCalc->at(ijet) = tag_up;
			AK4JetBTag_bSFdn_singleLepCalc->at(ijet) = tag_dn;
			AK4JetBTag_lSFup_singleLepCalc->at(ijet) = tag;
			AK4JetBTag_lSFdn_singleLepCalc->at(ijet) = tag;

		  }else{

			int binSF = (std::upper_bound(ptRangeSF.begin(), ptRangeSF.end(), AK4JetPt_singleLepCalc->at(ijet))-ptRangeSF.begin())-1;
			float pt = AK4JetPt_singleLepCalc->at(ijet);
			lSF = 0.980777+(-0.00109334*pt)+(4.2909e-06*pt*pt)+(-2.78512e-09*pt*pt*pt);
			lSFdn = lSF*(1-(0.0672836+(0.000102309*pt)+(-1.01558e-07*pt*pt)));
			lSFup = lSF*(1+(0.0672836+(0.000102309*pt)+(-1.01558e-07*pt*pt)));

			int bin = (std::upper_bound(ptRangeEff.begin(), ptRangeEff.end(), AK4JetPt_singleLepCalc->at(ijet))-ptRangeEff.begin())-1;
			lEff = MistagEff[bin];

			int tag = applySF(istagged,lSF,lEff);
			int tag_up = applySF(istagged,lSFup,lEff);
			int tag_dn = applySF(istagged,lSFdn,lEff);

			AK4JetBTag_singleLepCalc->at(ijet) = tag;
			AK4JetBTag_bSFup_singleLepCalc->at(ijet) = tag;
			AK4JetBTag_bSFdn_singleLepCalc->at(ijet) = tag;
			AK4JetBTag_lSFup_singleLepCalc->at(ijet) = tag_up;
			AK4JetBTag_lSFdn_singleLepCalc->at(ijet) = tag_dn;

		  }
		  */
		  
		  // ----------------------------------------------------------------------------
		  // Counts and pt ordering pair
		  // ----------------------------------------------------------------------------

		  jetptindpair.push_back(std::make_pair(AK4JetPt_singleLepCalc->at(ijet),ijet));
		  NJets_singleLepCalc+=1;
		  AK4HT+=AK4JetPt_singleLepCalc->at(ijet);
	  
		}else{
		  jetptindpair.push_back(std::make_pair(AK4JetPt_singleLepCalc->at(ijet),ijet));
		  NJets_singleLepCalc+=1;
		  AK4HT+=AK4JetPt_singleLepCalc->at(ijet);
		}
      }

      if(DEBUGjets)std::cout<< "NJets (after jet loop) = " << NJets_singleLepCalc << std::endl;

      AK4HTpMETpLepPt = AK4HT + corr_met_singleLepCalc;
//       if(isPassTrilepton){
// 		  for(unsigned int ilep = 0; ilep < TightLeptonPt_PtOrdered.size(); ilep++){
// 			AK4HTpMETpLepPt += TightLeptonPt_PtOrdered.at(ilep);
// 		  }
//       }
//       else{ //for ddbkg (just take 3 top leps in All Lepton List.) ATTENTION: is this fine???
// 		  for(unsigned int ilep = 0; ilep < 3; ilep++){
// 			AK4HTpMETpLepPt += AllLeptonPt_PtOrdered.at(ilep);
// 		  }      
//       }
	  for(unsigned int ilep = 0; ilep < AllLeptonPt_PtOrdered.size(); ilep++){
		AK4HTpMETpLepPt += AllLeptonPt_PtOrdered.at(ilep);
	  }      
      if(DEBUG)std::cout << "AK4HTpMETpLepPt = " << AK4HTpMETpLepPt << std::endl;
	
      // ----------------------------------------------------------------------------
      // Apply pt ordering to AK4 vectors
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"Apply pt ordering to AK4 vectors"<<std::endl;      

      std::sort(jetptindpair.begin(), jetptindpair.end(), comparepair);
      AK4JetPt_singleLepCalc_PtOrdered.clear();
      AK4JetEta_singleLepCalc_PtOrdered.clear();
      AK4JetPhi_singleLepCalc_PtOrdered.clear();
      AK4JetEnergy_singleLepCalc_PtOrdered.clear();
      AK4JetBDisc_singleLepCalc_PtOrdered.clear();
      AK4JetBTag_singleLepCalc_PtOrdered.clear();
      AK4JetBTag_bSFdn_singleLepCalc_PtOrdered.clear();
      AK4JetBTag_bSFup_singleLepCalc_PtOrdered.clear();
      AK4JetBTag_lSFdn_singleLepCalc_PtOrdered.clear();
      AK4JetBTag_lSFup_singleLepCalc_PtOrdered.clear();
      for(unsigned int ijet=0; ijet < jetptindpair.size(); ijet++){
      	AK4JetPt_singleLepCalc_PtOrdered.push_back(AK4JetPt_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetEta_singleLepCalc_PtOrdered.push_back(AK4JetEta_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetPhi_singleLepCalc_PtOrdered.push_back(AK4JetPhi_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetEnergy_singleLepCalc_PtOrdered.push_back(AK4JetEnergy_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBDisc_singleLepCalc_PtOrdered.push_back(AK4JetBDisc_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBTag_singleLepCalc_PtOrdered.push_back(AK4JetBTag_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBTag_bSFdn_singleLepCalc_PtOrdered.push_back(AK4JetBTag_bSFdn_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBTag_bSFup_singleLepCalc_PtOrdered.push_back(AK4JetBTag_bSFup_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBTag_lSFdn_singleLepCalc_PtOrdered.push_back(AK4JetBTag_lSFdn_singleLepCalc->at(jetptindpair[ijet].second));
      	AK4JetBTag_lSFup_singleLepCalc_PtOrdered.push_back(AK4JetBTag_lSFup_singleLepCalc->at(jetptindpair[ijet].second));
      }

      // ----------------------------------------------------------------------------
      // Apply kinematic cuts
      // ----------------------------------------------------------------------------
	  if(DEBUG)std::cout<<"Apply kinematic cuts"<<std::endl;      
	                
      int isPastNJetsCut = 0;
      if(NJets_singleLepCalc >= njetsCut){npass_njets+=1;isPastNJetsCut=1;}
      
      int isPastJetLeadPtCut = 0;
      if(AK4JetPt_singleLepCalc_PtOrdered.size() > 0 && AK4JetPt_singleLepCalc_PtOrdered[0] > JetLeadPtCut){npass_JetLeadPt+=1;isPastJetLeadPtCut=1;}
      
      int isPastJetSubLeadPtCut = 0;
      if(AK4JetPt_singleLepCalc_PtOrdered.size() > 1 && AK4JetPt_singleLepCalc_PtOrdered[1] > JetSubLeadPtCut){npass_JetSubLeadPt+=1;isPastJetSubLeadPtCut=1;}
      
      int isPastMETcut = 0;
      if(corr_met_singleLepCalc > metCut){npass_met+=1;isPastMETcut=1;}

      int isPastDiLepPtCut = 0;
      if(AllLeptonPt_PtOrdered[0] > lepPtCut && AllLeptonPt_PtOrdered[1] > lepPtCut){npass_dilepPt+=1;isPastDiLepPtCut=1;}

      
      /* from SingleLep
      int isPastElEtaCut = 0;
      if(isElectron && fabs(lepeta) < elEtaCut){npass_ElEta+=1;isPastElEtaCut=1;}
      if(isMuon){Nmuons+=1;isPastElEtaCut=1;}
      if(isElectron){Nelectrons+=1;}
      
      
      AK4HTpMETpLepPt = 0;
      AK4HTpMETpLepPt = AK4HT + corr_met_singleLepCalc + leppt;
      */
      
      /*
      
      // ----------------------------------------------------------------------------
      // Loop over AK8 jets for calculations and pt ordering pair
      // ----------------------------------------------------------------------------
	  if(DEBUG)std::cout<<"Loop over AK8 jets for calculations and pt ordering pair"<<std::endl;      
      
      NJetsHtagged = 0;      
      int NJetsHtagged_bSFup = 0;      
      int NJetsHtagged_bSFdn = 0;      
      int NJetsHtagged_lSFup = 0;      
      int NJetsHtagged_lSFdn = 0;      
      NJetsAK8_JetSubCalc = 0;
      vector<float> maxsubcsv;
      NJetsHtagged_shifts.clear();
      vector<pair<double,int>> jetak8ptindpair;

      for(unsigned int ijet=0; ijet < theJetAK8Pt_JetSubCalc->size(); ijet++){

		// ----------------------------------------------------------------------------
		// Basic cuts
		// ----------------------------------------------------------------------------
		if(DEBUG)std::cout<<"Basic cuts"<<std::endl;      

		maxsubcsv.push_back(-99.0);
		if(theJetAK8Pt_JetSubCalc->at(ijet) < 180 || fabs(theJetAK8Eta_JetSubCalc->at(ijet)) > ak8EtaCut) continue;
		if(theJetAK8NjettinessTau1_JetSubCalc->at(ijet)==0) continue;
		if(theJetAK8NjettinessTau2_JetSubCalc->at(ijet)==0) continue;

		// ----------------------------------------------------------------------------
		// Counter and pt ordering pair
		// ----------------------------------------------------------------------------
		if(DEBUG)std::cout<<"Counter and pt ordering pair"<<std::endl;      

		NJetsAK8_JetSubCalc += 1; 
		jetak8ptindpair.push_back(std::make_pair(theJetAK8Pt_JetSubCalc->at(ijet),ijet));
	  
		// ----------------------------------------------------------------------------
		// Count Higgs tags
		// ----------------------------------------------------------------------------
		if(DEBUG)std::cout<<"Count Higgs tags"<<std::endl;      

		int firstsub = theJetAK8SDSubjetIndex_JetSubCalc->at(ijet);
		int nsubs = theJetAK8SDSubjetSize_JetSubCalc->at(ijet);
		double maxCSVsubjet = 0;
		TLorentzVector tempsubjet;
		TLorentzVector sumsubjets; sumsubjets.SetPtEtaPhiM(0,0,0,0);
		for(int isub = firstsub; isub < firstsub + nsubs; isub++){
		  tempsubjet.SetPtEtaPhiM(theJetAK8SDSubjetPt_JetSubCalc->at(isub),theJetAK8SDSubjetEta_JetSubCalc->at(isub),theJetAK8SDSubjetPhi_JetSubCalc->at(isub),theJetAK8SDSubjetMass_JetSubCalc->at(isub));
		  sumsubjets += tempsubjet;
		  if(theJetAK8SDSubjetCSV_JetSubCalc->at(isub) > maxCSVsubjet) maxCSVsubjet = theJetAK8SDSubjetCSV_JetSubCalc->at(isub);
		  if(isub != firstsub && theJetAK8SDSubjetPt_JetSubCalc->at(isub) == theJetAK8SDSubjetPt_JetSubCalc->at(firstsub)) cout << "subjets have matching pT, something's wrong" << endl;
		}
		maxsubcsv.at(ijet) = maxCSVsubjet;
		if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVMSF_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) NJetsHtagged += 1;
		if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVM_bSFup_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) NJetsHtagged_bSFup += 1;
		if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVM_bSFdn_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) NJetsHtagged_bSFdn += 1;
		if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVM_lSFup_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) NJetsHtagged_lSFup += 1;
		if(theJetAK8Pt_JetSubCalc->at(ijet) > 300 &&  theJetAK8SDSubjetNCSVM_lSFdn_JetSubCalc->at(ijet) > 0 && sumsubjets.M() > 60 && sumsubjets.M() < 150) NJetsHtagged_lSFdn += 1;
      }
      NJetsHtagged_shifts.push_back(NJetsHtagged_bSFup);
      NJetsHtagged_shifts.push_back(NJetsHtagged_bSFdn);
      NJetsHtagged_shifts.push_back(NJetsHtagged_lSFup);
      NJetsHtagged_shifts.push_back(NJetsHtagged_lSFdn);
      
      */
      /*

      // ----------------------------------------------------------------------------
      // Skip failing events
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"Skip failing events"<<std::endl;      

      int isPastNHjetsCut = 0;
      if(NJetsHtagged >= 0){npass_nHjets += 1; isPastNHjetsCut = 1; }
      */

      /* From SingleLep
      if(!(isPastMETcut && isPastNJetsCut && isPastJetLeadPtCut && isPastTriLepPtCut && isPastElEtaCut && isPastJetSubLeadPtCut)) continue;
      */

      //if(!(isPastMETcut && isPastNJetsCut && isPastJetLeadPtCut && isPastTriLepPtCut && isPastJetSubLeadPtCut)) continue; //this indirectly removes events with nJets < 2 !

      if(!(isPastMETcut && isPastNJetsCut && isPastDiLepPtCut)) continue;


      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      /////////////// ONLY ON SELECTED EVENTS ////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

      // ----------------------------------------------------------------------------
      // Combine lepton variables into one set
      // ----------------------------------------------------------------------------
      
      /* From SingleLep  
      if(isElectron){
		leptonPt_singleLepCalc = leppt;
		leptonEta_singleLepCalc = lepeta;
		leptonPhi_singleLepCalc = elPhi_singleLepCalc->at(0);
		leptonEnergy_singleLepCalc = elEnergy_singleLepCalc->at(0);
		leptonMiniIso_singleLepCalc = elMiniIso_singleLepCalc->at(0);
		leptonRelIso_singleLepCalc = elRelIso_singleLepCalc->at(0);
		leptonDxy_singleLepCalc = elDxy_singleLepCalc->at(0);
		leptonDz_singleLepCalc = elDZ_singleLepCalc->at(0);
		leptonCharge_singleLepCalc = elCharge_singleLepCalc->at(0);
      }
      if(isMuon){
		leptonPt_singleLepCalc = leppt;
		leptonEta_singleLepCalc = lepeta;
		leptonPhi_singleLepCalc = muPhi_singleLepCalc->at(0);
		leptonEnergy_singleLepCalc = muEnergy_singleLepCalc->at(0);
		leptonMiniIso_singleLepCalc = muMiniIso_singleLepCalc->at(0);
		leptonRelIso_singleLepCalc = muRelIso_singleLepCalc->at(0);
		leptonDxy_singleLepCalc = muDxy_singleLepCalc->at(0);
		leptonDz_singleLepCalc = muDz_singleLepCalc->at(0);
		leptonCharge_singleLepCalc = muCharge_singleLepCalc->at(0);
      }
      */
      
      /*	
      // ----------------------------------------------------------------------------
      // Apply pt ordering to AK8 vectors 
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"Apply pt ordering to AK8 vectors"<<std::endl;      

      //Pt ordering for AK8
      std::sort(jetak8ptindpair.begin(), jetak8ptindpair.end(), comparepair);
      theJetAK8Pt_JetSubCalc_PtOrdered.clear();
      theJetAK8Eta_JetSubCalc_PtOrdered.clear();
      theJetAK8Phi_JetSubCalc_PtOrdered.clear();
      theJetAK8Energy_JetSubCalc_PtOrdered.clear();
      theJetAK8Mass_JetSubCalc_PtOrdered.clear();
      theJetAK8PrunedMass_JetSubCalc_PtOrdered.clear();
      theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered.clear();
      theJetAK8SoftDropMass_JetSubCalc_PtOrdered.clear();
      theJetAK8MaxSubCSV_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.clear();
      theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.clear();
      for(unsigned int ijet=0; ijet < jetak8ptindpair.size(); ijet++){
      	theJetAK8Pt_JetSubCalc_PtOrdered.push_back(theJetAK8Pt_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Eta_JetSubCalc_PtOrdered.push_back(theJetAK8Eta_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Phi_JetSubCalc_PtOrdered.push_back(theJetAK8Phi_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Energy_JetSubCalc_PtOrdered.push_back(theJetAK8Energy_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8Mass_JetSubCalc_PtOrdered.push_back(theJetAK8Mass_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8PrunedMass_JetSubCalc_PtOrdered.push_back(theJetAK8PrunedMass_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered.push_back(theJetAK8PrunedMassWtagUncerts_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8SoftDropMass_JetSubCalc_PtOrdered.push_back(theJetAK8SoftDropMass_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8MaxSubCSV_JetSubCalc_PtOrdered.push_back(maxsubcsv.at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau1_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau2_JetSubCalc->at(jetak8ptindpair[ijet].second));
      	theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.push_back(theJetAK8NjettinessTau3_JetSubCalc->at(jetak8ptindpair[ijet].second));
      }
      */

      // ----------------------------------------------------------------------------
      // Lepton 4-vectors, calculate MT and electron trigger presel value
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"Lepton 4-vectors, calculate MT and electron trigger presel value"<<std::endl;      
      
      /* From SingleLep
      // Set lepton 4-vectors
      double lepM;
      double lepphi;
      elTrigPresel_singleLepCalc = false;
      if (isMuon){ 
		lepM = 0.105658367;
		lepphi = muPhi_singleLepCalc->at(0);
		lepton_lv.SetPtEtaPhiM(muPt_singleLepCalc->at(0),muEta_singleLepCalc->at(0),muPhi_singleLepCalc->at(0),lepM);
      }
      else{
		lepM = 0.00051099891;
		lepphi = elPhi_singleLepCalc->at(0);
		lepton_lv.SetPtEtaPhiM(elPt_singleLepCalc->at(0),elEta_singleLepCalc->at(0),elPhi_singleLepCalc->at(0),lepM);

		if(elEta_singleLepCalc->at(0) < 1.442){
		  if(elSihih_singleLepCalc->at(0) < 0.012 &&
			 elHoE_singleLepCalc->at(0) < 0.09 &&
			 elEcalPFClusterIso_singleLepCalc->at(0)/leppt < 0.37 &&
			 elHcalPFClusterIso_singleLepCalc->at(0)/leppt < 0.25 &&
			 elDR03TkSumPt_singleLepCalc->at(0)/leppt < 0.18 &&
			 fabs(elDEtaSCTkAtVtx_singleLepCalc->at(0)) < 0.0095 &&
			 fabs(elDPhiSCTkAtVtx_singleLepCalc->at(0)) < 0.065
			 ) elTrigPresel_singleLepCalc = true;
		}else{
		  if(elSihih_singleLepCalc->at(0) < 0.033 &&
			 elHoE_singleLepCalc->at(0) < 0.09 &&
			 elEcalPFClusterIso_singleLepCalc->at(0)/leppt < 0.45 &&
			 elHcalPFClusterIso_singleLepCalc->at(0)/leppt < 0.28 &&
			 elDR03TkSumPt_singleLepCalc->at(0)/leppt < 0.18
			 ) elTrigPresel_singleLepCalc = true;
		}	  
      }
      MT_lepMet = sqrt(2*leppt*corr_met_singleLepCalc*(1 - cos(lepphi - corr_met_phi_singleLepCalc)));
      */    
        
      //Rizki - start

      if(DEBUG)std::cout<<"Rizki C - start"<<std::endl;      

      // Set lepton 4-vectors - NEED TO IMPLEMENT elTrigPresel HERE!! ATTENTION: what is elTrigPresel??
      double lepM; 
      TLorentzVector lv_temp;
      lepton_lv.clear();
      //if(AllLeptonPt_PtOrdered.size()<3) std::cout << "Trilepton cut fail!! will segfault when setting lepton_lv 123!!" << std::endl;
      for (unsigned int ilep=0; ilep < AllLeptonPt_PtOrdered.size() ; ilep++){
//       	std::cout << "AllLeptonPt_PtOrdered.size() : " << AllLeptonPt_PtOrdered.size() << std::endl;
//       	std::cout << "ilep : " << ilep << " AllLeptonPt_PtOrdered : " << AllLeptonPt_PtOrdered.at(ilep) << std::endl;
      	lepM = ( AllLeptonFlavor_PtOrdered[ilep]==0? 0.00051099891:0.105658367);
      	lv_temp.SetPtEtaPhiM(AllLeptonPt_PtOrdered.at(ilep),AllLeptonEta_PtOrdered.at(ilep),AllLeptonPhi_PtOrdered.at(ilep),lepM);
      	lepton_lv.push_back(lv_temp);
      	//std::cout << "lep " << ilep+1 << " , flavor :" <<  AllLeptonFlavor_PtOrdered[ilep] << " , pt : " <<AllLeptonPt_PtOrdered.at(ilep) << " ,  eta : "<<AllLeptonEta_PtOrdered.at(ilep) << " , phi : "<<AllLeptonPhi_PtOrdered.at(ilep) << " , mass : " << lepM << std::endl;
      }
	
      //calculate Mll - start
      Mll = -1 ;
      TLorentzVector ll_lv;
      ll_lv = lepton_lv.at(0)+lepton_lv.at(1);
      Mll = ll_lv.M();
      //std::cout << "Mlll = " << Mlll << std::endl; 
      //calculate Mlll - end

      //calculate MllOS and MllSS - start
      Mll_OS = -1.;
      Mll_SS = -1.;
      if(AllLeptonCharge_PtOrdered.at(0)*AllLeptonCharge_PtOrdered.at(1)== -1){
      	TLorentzVector temp;
      	temp = lepton_lv.at(0)+lepton_lv.at(1);
      	Mll_OS = temp.M();
      	//std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << " (lep0+lep1)" << std::endl;
      	//std::cout << "pT1 = " << lepton_lv.at(0).Pt() << " pT2 = " << lepton_lv.at(1).Pt() << std::endl;
      	//std::cout << "eta1 = " << lepton_lv.at(0).Eta() << " eta2 = " << lepton_lv.at(1).Eta() << std::endl;
      } 
      // else if(AllLeptonFlavor_PtOrdered.at(0)==AllLeptonFlavor_PtOrdered.at(2) && AllLeptonCharge_PtOrdered.at(0)*AllLeptonCharge_PtOrdered.at(2)== -1){
      // 	TLorentzVector temp;
      // 	temp = lepton_lv.at(0)+lepton_lv.at(2);
      // 	Mll_sameFlavorOS = temp.M();
      	//std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << " (lep0+lep2)" << std::endl;
      	//std::cout << "pT1 = " << lepton_lv.at(0).Pt() << " pT2 = " << lepton_lv.at(2).Pt() << std::endl;
      	//std::cout << "eta1 = " << lepton_lv.at(0).Eta() << " eta2 = " << lepton_lv.at(2).Eta() << std::endl;
       
      else if(AllLeptonCharge_PtOrdered.at(0)*AllLeptonCharge_PtOrdered.at(1)== 1){
      	TLorentzVector temp;
      	temp = lepton_lv.at(0)+lepton_lv.at(1);
      	Mll_SS = temp.M();
      	//std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << " (lep1+lep2)" << std::endl;
      	//std::cout << "pT2 = " << lepton_lv.at(1).Pt() << " pT3 = " << lepton_lv.at(2).Pt() << std::endl;
      	//std::cout << "eta2 = " << lepton_lv.at(1).Eta() << " eta3 = " << lepton_lv.at(2).Eta() << std::endl;
      }
      // else{
      // 	Mll_sameFlavorOS = -1.;
      // 	//std::cout << "Mll_sameFlavorOS = " << Mll_sameFlavorOS << std::endl;      	
      // } 

//       MllOS_allComb.clear();
//       unsigned int maxMllOSsize = 45;  //ATTENTION: MAXIMUM allowed leptons = 10 !!! 10C2 = 45 !
//       unsigned int maxLepPermutation = ( AllLeptonPt_PtOrdered.size() * AllLeptonPt_PtOrdered.size() -1 ) / 2;
//       if (maxLepPermutation > maxMllOSsize) maxMllOSsize = maxLepPermutation;
//       for (unsigned int i = 0; i < maxMllOSsize ; i++){
// //       for (unsigned int i = 0; i+1 < AllLeptonPt_PtOrdered.size() ; i++){
// //       	for (unsigned int j = i+1; j < AllLeptonPt_PtOrdered.size() ; j++){
//       		MllOS_allComb.push_back(-1);
// //       	}
//       }
//       int MllOS_count = 0;
//       for (unsigned int i = 0; i < AllLeptonPt_PtOrdered.size() ; i++){
//       	for (unsigned int j = i+1; j < AllLeptonPt_PtOrdered.size() ; j++){
// 		  	if(AllLeptonFlavor_PtOrdered.at(i)==AllLeptonFlavor_PtOrdered.at(j) && AllLeptonCharge_PtOrdered.at(i)*AllLeptonCharge_PtOrdered.at(j)== -1){
// 				TLorentzVector temp;
// 				temp = lepton_lv.at(i)+lepton_lv.at(j);
// 				MllOS_allComb.at(MllOS_count)= temp.M();
// 		  	}
// 			if(DEBUG||DEBUGleptons)std::cout << "MllOS_allComb ( lep" << i <<"_lep"<< j << ") = " << MllOS_allComb.at(MllOS_count) << std::endl ;
// 			MllOS_count++;
// 		}
// 	  }
	  
// 	  vector<float>::const_iterator it, it2 ;  
// 	  // Find the min and max elements in the vector
// 	  it = std::max_element(MllOS_allComb.begin(), MllOS_allComb.end());
// 	  MllOS_allComb_max = *it;
// 	  //std::cout << "MllOS_allComb_max = " << MllOS_allComb_max << std::endl;
	  
// 	  //find minimum for MllOS_allComb values that are > -1
// 	  std::vector<float> MllOS_allComb_filled;
// 	  for(unsigned i=0 ; i < MllOS_allComb.size() ; i++){
// 	  	if(MllOS_allComb.at(i)>=0)MllOS_allComb_filled.push_back(MllOS_allComb.at(i));
// 	  }
// 	  if(MllOS_allComb_filled.size()==0)MllOS_allComb_filled.push_back(-1);
// 	  it2 = std::min_element(MllOS_allComb_filled.begin(), MllOS_allComb_filled.end());
// 	  MllOS_allComb_min = *it2;
// 	  //std::cout << "MllOS_allComb_min = " << MllOS_allComb_min << std::endl;
	  	  
//       //calculate MllOS's - end
      
      if(DEBUG)std::cout<<"Rizki C - end"<<std::endl;      

      // int isPastMllCut = 0;
      // if(Mll > MllCut){npass_Mllcut+=1; isPastMllCut=1;}

      // if(!(isPastMllcut)) continue;

      npass_all+=1;
      //Rizki - end
      

      // ----------------------------------------------------------------------------
      // 8TeV Top pT reweighting
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"8TeV Top pT reweighting"<<std::endl;      

      /* From SingleLep
      genTopPt = -999;
      genAntiTopPt = -999;
      topPtWeight = 1.0;
      topPtWeightPast400 = 1.0;
      topPtWeightHighPt = 1.0;

      for(unsigned int ijet=0; ijet < topPt_TTbarMassCalc->size(); ijet++){
		if(genTopPt < 0 && topID_TTbarMassCalc->at(ijet) == 6) genTopPt = topPt_TTbarMassCalc->at(ijet);
		if(genAntiTopPt < 0 && topID_TTbarMassCalc->at(ijet) == -6) genAntiTopPt = topPt_TTbarMassCalc->at(ijet);
      }

      if(genTopPt > 0 && genAntiTopPt > 0){
		float toppt_temp = genTopPt;
		if(genTopPt > 400) toppt_temp = 400;
		float antitoppt_temp = genAntiTopPt;
		if(genAntiTopPt > 400) antitoppt_temp = 400;
	
		float SFtop = TMath::Exp(0.156-0.00137*toppt_temp); // using 8TeV TopPtReweighting: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopPtReweighting
		float SFantitop = TMath::Exp(0.156-0.00137*antitoppt_temp);
		topPtWeight = TMath::Sqrt(SFtop*SFantitop)/0.99277; //0.99277-->average weight
	
		float SFtopPast400 = TMath::Exp(0.156-0.00137*genTopPt);
		float SFantitopPast400 = TMath::Exp(0.156-0.00137*genAntiTopPt);
		topPtWeightPast400 = TMath::Sqrt(SFtopPast400*SFantitopPast400)/0.9927;
	
		float SFtopHighPt = 0.98  - 0.00026*genTopPt;  // 0.98 +- 0.24, 0.0026 +- 0.00039
		float SFantitopHighPt = 0.98  - 0.00026*genAntiTopPt;
		topPtWeightHighPt = TMath::Sqrt(SFtopHighPt*SFantitopHighPt);
      }
      */
      
      // ----------------------------------------------------------------------------
      // W --> l nu with mass constraint
      // ----------------------------------------------------------------------------
      
      /* From SingleLep
      double metpx = corr_met_singleLepCalc*cos(corr_met_phi_singleLepCalc);
      double metpy = corr_met_singleLepCalc*sin(corr_met_phi_singleLepCalc);
      double metpt = corr_met_singleLepCalc;

      double Dtmp = (MW*MW)-(lepM*lepM)+2*((lepton_lv.Px())*(metpx)+(lepton_lv.Py())*(metpy));
      double Atmp = 4.0*((lepton_lv.Energy())*(lepton_lv.Energy())-(lepton_lv.Pz())*(lepton_lv.Pz()));
      double Btmp = -4.0*Dtmp*(lepton_lv.Pz());
      double Ctmp = 4.0*(lepton_lv.Energy())*(lepton_lv.Energy())*(metpt)*(metpt)-Dtmp*Dtmp;
      
      double nuPz_1;
      double nuPz_2;
      
      double DETtmp = Btmp*Btmp-4.0*Atmp*Ctmp;
      
      TLorentzVector Wlv_1, Wlv_2, Wlv,lvTop, lvXTF;
      if(DETtmp >= 0) {
		nuPz_1 = (-Btmp+TMath::Sqrt(DETtmp))/(2.0*Atmp);
		nuPz_2 = (-Btmp-TMath::Sqrt(DETtmp))/(2.0*Atmp);
		TLorentzVector Nulv_1(metpx,metpy,nuPz_1,TMath::Sqrt((metpt)*(metpt)+(nuPz_1)*(nuPz_1)));
		TLorentzVector Nulv_2(metpx,metpy,nuPz_2,TMath::Sqrt((metpt)*(metpt)+(nuPz_2)*(nuPz_2)));
		Wlv_1 = Nulv_1+lepton_lv;
		Wlv_2 = Nulv_2+lepton_lv;
      }
      if(DETtmp < 0) {
		nuPz_1 = (-Btmp)/(2.0*Atmp);
		nuPz_2 = (-Btmp)/(2.0*Atmp);
		double alpha = (lepton_lv.Px())*(metpx)/(metpt)+(lepton_lv.Py())*(metpy)/(metpt);
		double Delta = (MW*MW)-(lepM*lepM);
		Atmp = 4.0*((lepton_lv.Pz())*(lepton_lv.Pz())-(lepton_lv.Energy())*(lepton_lv.Energy())+(alpha*alpha));
		Btmp = 4.0*alpha*Delta;
		Ctmp = Delta*Delta;
		DETtmp = Btmp*Btmp-4.0*Atmp*Ctmp;
		double pTnu_1 = (-Btmp+TMath::Sqrt(DETtmp))/(2.0*Atmp);
		double pTnu_2 = (-Btmp-TMath::Sqrt(DETtmp))/(2.0*Atmp);
		TLorentzVector Nulv_1(metpx*(pTnu_1)/(metpt),metpy*(pTnu_1)/(metpt),nuPz_1,TMath::Sqrt((pTnu_1)*(pTnu_1)+(nuPz_1)*(nuPz_1)));
		TLorentzVector Nulv_2(metpx*(pTnu_2)/(metpt),metpy*(pTnu_2)/(metpt),nuPz_2,TMath::Sqrt((pTnu_2)*(pTnu_2)+(nuPz_2)*(nuPz_2)));
		Wlv_1 = Nulv_1+lepton_lv;
		Wlv_2 = Nulv_2+lepton_lv;
		if (fabs(Wlv_1.M()-MW) < fabs(Wlv_2.M()-MW)) Wlv_2 = Wlv_1;
		else Wlv_1 = Wlv_2;
      }
      */
      
      // ----------------------------------------------------------------------------
      // top --> W b --> l nu b using W from above
      // ----------------------------------------------------------------------------
      
      /* From SingleLep
      double dMTOP = 1e8;
      unsigned int topIndex = 0;
      bool firstW = true;
      double MTop_1, MTop_2;
      for(unsigned int ijet=0; ijet < AK4JetPt_singleLepCalc_PtOrdered.size(); ijet++){
		jet_lv.SetPtEtaPhiE(AK4JetPt_singleLepCalc_PtOrdered.at(ijet),AK4JetEta_singleLepCalc_PtOrdered.at(ijet),AK4JetPhi_singleLepCalc_PtOrdered.at(ijet),AK4JetEnergy_singleLepCalc_PtOrdered.at(ijet));
		MTop_1 = (jet_lv + Wlv_1).M();
		MTop_2 = (jet_lv + Wlv_2).M();
		if(fabs(MTop_1 - MTOP) < dMTOP) {
		  if(fabs(MTop_1 - MTOP) < fabs(MTop_2 - MTOP)) {
			firstW = true;
			topIndex = ijet;
			dMTOP = fabs(MTop_1 - MTOP);
		  }
		  else {
			firstW = false;
			topIndex = ijet;
			dMTOP = fabs(MTop_2 - MTOP);
		  }
		}
		else if(fabs(MTop_2 - MTOP) < dMTOP) {
		  firstW = false;
		  topIndex = ijet;
		  dMTOP = fabs(MTop_2 - MTOP);
		}
      }

      if(firstW) {Wlv = Wlv_1;}
      else{Wlv = Wlv_2;}

      jet_lv.SetPtEtaPhiE(AK4JetPt_singleLepCalc_PtOrdered.at(topIndex),AK4JetEta_singleLepCalc_PtOrdered.at(topIndex),AK4JetPhi_singleLepCalc_PtOrdered.at(topIndex),AK4JetEnergy_singleLepCalc_PtOrdered.at(topIndex));
      lvTop = jet_lv + Wlv; //Top LV

      topPt = lvTop.Pt();
      topMass = lvTop.M();
      topPtGen = genTopPt;
      if(fabs(lvTop.Pt() - genTopPt) > fabs(lvTop.Pt() - genAntiTopPt)) topPtGen = genAntiTopPt;
      */

      // ----------------------------------------------------------------------------
      // AK4 Jet - lepton associations
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"AK4 Jet - lepton associations"<<std::endl;      

      NJetsBTagwithSF_singleLepCalc = 0;
      BJetLeadPt = -99;
      minMleppBjet = 1e8;
      minMleppJet = 1e8;
      deltaRlepJetInMinMljet = -99;
      deltaPhilepJetInMinMljet = -99;
      deltaRlepbJetInMinMlb = -99;
      deltaPhilepbJetInMinMlb = -99;
      minDR_lepJet = 1e8;
      minDR_lep1Jet = 1e8;
      minDR_lep2Jet = 1e8;
      //      minDR_lep3Jet = 1e8;
      minDR_lepMET = 1e8;
      minDR_METJet = 1e8;
      ptRel_lepJet = -99;
      BJetLeadPt_shifts.clear();
      deltaR_lepJets.clear();
      deltaR_lep1Jets.clear();
      deltaR_lep2Jets.clear();
      //     deltaR_lep3Jets.clear();
      deltaR_lepMETs.clear();
      deltaR_METJets.clear();
      deltaR_lepBJets.clear();
      deltaR_lepBJets_bSFup.clear();
      deltaR_lepBJets_bSFdn.clear();
      deltaR_lepBJets_lSFup.clear();
      deltaR_lepBJets_lSFdn.clear();
      deltaPhi_lepJets.clear();
      deltaPhi_lepBJets.clear();
      deltaPhi_lepBJets_bSFup.clear();
      deltaPhi_lepBJets_bSFdn.clear();
      deltaPhi_lepBJets_lSFup.clear();
      deltaPhi_lepBJets_lSFdn.clear();
      mass_lepJets.clear();
      mass_lepBJets.clear();
      mass_lepBJets_bSFup.clear();
      mass_lepBJets_bSFdn.clear();
      mass_lepBJets_lSFup.clear();
      mass_lepBJets_lSFdn.clear();
      NJetsBTagwithSF_singleLepCalc_shifts.clear();
      minMleppBjet_shifts.clear();
      deltaRlepbJetInMinMlb_shifts.clear();
      deltaPhilepbJetInMinMlb_shifts.clear();
      for(int i = 0; i < 4; i++){
		BJetLeadPt_shifts.push_back(-99);
		NJetsBTagwithSF_singleLepCalc_shifts.push_back(0);
		minMleppBjet_shifts.push_back(1e8);
		deltaRlepbJetInMinMlb_shifts.push_back(-99);
		deltaPhilepbJetInMinMlb_shifts.push_back(-99);
      }	

      for(unsigned int ijet=0; ijet < AK4JetPt_singleLepCalc_PtOrdered.size(); ijet++){
        jet_lv.SetPtEtaPhiE(AK4JetPt_singleLepCalc_PtOrdered.at(ijet),AK4JetEta_singleLepCalc_PtOrdered.at(ijet),AK4JetPhi_singleLepCalc_PtOrdered.at(ijet),AK4JetEnergy_singleLepCalc_PtOrdered.at(ijet));
        
        /* From SingleLep
		if((lepton_lv + jet_lv).M() < minMleppJet) {
		  minMleppJet = fabs((lepton_lv + jet_lv).M());
		  deltaRlepJetInMinMljet = jet_lv.DeltaR(lepton_lv);
		  deltaPhilepJetInMinMljet = jet_lv.DeltaPhi(lepton_lv);
		}

		deltaR_lepJets.push_back(lepton_lv.DeltaR(jet_lv));
		deltaPhi_lepJets.push_back(lepton_lv.DeltaPhi(jet_lv));
		mass_lepJets.push_back((lepton_lv + jet_lv).M());
		*/

		//calculate dR(leps,jets) and min - start
		for (unsigned int ilep=0; ilep < lepton_lv.size() ; ilep++){
			if(ilep==0)deltaR_lep1Jets.push_back(jet_lv.DeltaR(lepton_lv.at(0)));
			if(ilep==1)deltaR_lep2Jets.push_back(jet_lv.DeltaR(lepton_lv.at(1)));
			//			if(ilep==2)deltaR_lep3Jets.push_back(jet_lv.DeltaR(lepton_lv.at(2)));
			deltaR_lepJets.push_back(jet_lv.DeltaR(lepton_lv.at(ilep)));

			if(DEBUGjets||DEBUGleptons) std::cout << "dR(lep"<<ilep+1<<",jet"<<ijet+1<<") = "<< jet_lv.DeltaR(lepton_lv.at(ilep)) << std::endl;
		}
		//find minimum 
		vector<double>::const_iterator minDR_lep1Jet_it;  
		minDR_lep1Jet_it = std::min_element(deltaR_lep1Jets.begin(), deltaR_lep1Jets.end());
		if(minDR_lep1Jet > *minDR_lep1Jet_it) minDR_lep1Jet = *minDR_lep1Jet_it;

		vector<double>::const_iterator minDR_lep2Jet_it;  
		minDR_lep2Jet_it = std::min_element(deltaR_lep2Jets.begin(), deltaR_lep2Jets.end());
		if(minDR_lep2Jet > *minDR_lep2Jet_it) minDR_lep2Jet = *minDR_lep2Jet_it;

		// vector<double>::const_iterator minDR_lep3Jet_it;  
		// minDR_lep3Jet_it = std::min_element(deltaR_lep3Jets.begin(), deltaR_lep3Jets.end());
		// if(minDR_lep3Jet > *minDR_lep3Jet_it) minDR_lep3Jet = *minDR_lep3Jet_it;

		vector<double>::const_iterator minDR_lepJet_it;  
		minDR_lepJet_it = std::min_element(deltaR_lepJets.begin(), deltaR_lepJets.end());
		if(minDR_lepJet > *minDR_lepJet_it) minDR_lepJet = *minDR_lepJet_it;
		//calculate dR(leps,jets) and min - end
		
		//calculate dR(MET,jets) and min - start
		//calculate dR(MET,jets) and min - end

		if(AK4JetBTag_singleLepCalc_PtOrdered.at(ijet) == 1){
		  NJetsBTagwithSF_singleLepCalc += 1;
		  if(AK4JetPt_singleLepCalc_PtOrdered.at(ijet) > BJetLeadPt) BJetLeadPt = AK4JetPt_singleLepCalc_PtOrdered.at(ijet);
		  
		  /* From SingleLep
		  deltaR_lepBJets.push_back(lepton_lv.DeltaR(jet_lv));
		  deltaPhi_lepBJets.push_back(lepton_lv.DeltaPhi(jet_lv));
		  mass_lepBJets.push_back((lepton_lv + jet_lv).M());

		  if((lepton_lv + jet_lv).M() < minMleppBjet) {
		    minMleppBjet = fabs( (lepton_lv + jet_lv).M() );
		    deltaRlepbJetInMinMlb = jet_lv.DeltaR(lepton_lv);
		    deltaPhilepbJetInMinMlb = jet_lv.DeltaPhi(lepton_lv);
		  }
		  */
		  
		}
		if(AK4JetBTag_bSFup_singleLepCalc_PtOrdered.at(ijet) == 1){
		  NJetsBTagwithSF_singleLepCalc_shifts.at(0) += 1;
		  if(AK4JetPt_singleLepCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(0)) BJetLeadPt_shifts.at(0) = AK4JetPt_singleLepCalc_PtOrdered.at(ijet);
		  
		  /* From SingleLep
		  deltaR_lepBJets_bSFup.push_back(lepton_lv.DeltaR(jet_lv));
		  deltaPhi_lepBJets_bSFup.push_back(lepton_lv.DeltaPhi(jet_lv));
		  mass_lepBJets_bSFup.push_back((lepton_lv + jet_lv).M());

		  if((lepton_lv + jet_lv).M() < minMleppBjet_shifts.at(0)) {
		    minMleppBjet_shifts.at(0) = fabs( (lepton_lv + jet_lv).M() );
		    deltaRlepbJetInMinMlb_shifts.at(0) = jet_lv.DeltaR(lepton_lv);
		    deltaPhilepbJetInMinMlb_shifts.at(0) = jet_lv.DeltaPhi(lepton_lv);
		  }
		  */

		}
		if(AK4JetBTag_bSFdn_singleLepCalc_PtOrdered.at(ijet) == 1){
		  NJetsBTagwithSF_singleLepCalc_shifts.at(1) += 1;
		  if(AK4JetPt_singleLepCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(1)) BJetLeadPt_shifts.at(1) = AK4JetPt_singleLepCalc_PtOrdered.at(ijet);
		  
		  /*From SingleLep
		  deltaR_lepBJets_bSFdn.push_back(lepton_lv.DeltaR(jet_lv));
		  deltaPhi_lepBJets_bSFdn.push_back(lepton_lv.DeltaPhi(jet_lv));
		  mass_lepBJets_bSFdn.push_back((lepton_lv + jet_lv).M());

		  if((lepton_lv + jet_lv).M() < minMleppBjet_shifts.at(1)) {
		    minMleppBjet_shifts.at(1) = fabs( (lepton_lv + jet_lv).M() );
		    deltaRlepbJetInMinMlb_shifts.at(1) = jet_lv.DeltaR(lepton_lv);
		    deltaPhilepbJetInMinMlb_shifts.at(1) = jet_lv.DeltaPhi(lepton_lv);
		  }
		  */

		}
		if(AK4JetBTag_lSFup_singleLepCalc_PtOrdered.at(ijet) == 1){
		  NJetsBTagwithSF_singleLepCalc_shifts.at(2) += 1;
		  if(AK4JetPt_singleLepCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(2)) BJetLeadPt_shifts.at(2) = AK4JetPt_singleLepCalc_PtOrdered.at(ijet);
		  
		  /* From SingleLep
		  deltaR_lepBJets_lSFup.push_back(lepton_lv.DeltaR(jet_lv));
		  deltaPhi_lepBJets_lSFup.push_back(lepton_lv.DeltaPhi(jet_lv));
		  mass_lepBJets_lSFup.push_back((lepton_lv + jet_lv).M());

		  if((lepton_lv + jet_lv).M() < minMleppBjet_shifts.at(2)) {
		    minMleppBjet_shifts.at(2) = fabs( (lepton_lv + jet_lv).M() );
		    deltaRlepbJetInMinMlb_shifts.at(2) = jet_lv.DeltaR(lepton_lv);
		    deltaPhilepbJetInMinMlb_shifts.at(2) = jet_lv.DeltaPhi(lepton_lv);
		  }
		  */

		}
		if(AK4JetBTag_lSFdn_singleLepCalc_PtOrdered.at(ijet) == 1){
		  NJetsBTagwithSF_singleLepCalc_shifts.at(3) += 1;
		  if(AK4JetPt_singleLepCalc_PtOrdered.at(ijet) > BJetLeadPt_shifts.at(3)) BJetLeadPt_shifts.at(3) = AK4JetPt_singleLepCalc_PtOrdered.at(ijet);

		  /* From SingleLep
		  deltaR_lepBJets_lSFdn.push_back(lepton_lv.DeltaR(jet_lv));
		  deltaPhi_lepBJets_lSFdn.push_back(lepton_lv.DeltaPhi(jet_lv));
		  mass_lepBJets_lSFdn.push_back((lepton_lv + jet_lv).M());

		  if((lepton_lv + jet_lv).M() < minMleppBjet_shifts.at(3)) {
		    minMleppBjet_shifts.at(3) = fabs( (lepton_lv + jet_lv).M() );
		    deltaRlepbJetInMinMlb_shifts.at(3) = jet_lv.DeltaR(lepton_lv);
		    deltaPhilepbJetInMinMlb_shifts.at(3) = jet_lv.DeltaPhi(lepton_lv);
		  }
		  */

		}
      	
      	/* From SingleLep
		if(deltaR_lepJets[ijet] < minDR_lepJet) {
		  minDR_lepJet = deltaR_lepJets[ijet];
		  ptRel_lepJet = lepton_lv.P()*(jet_lv.Vect().Cross(lepton_lv.Vect()).Mag()/jet_lv.P()/lepton_lv.P());
		}
		*/
      }
      
      if(DEBUGjets||DEBUGleptons) std::cout << "min dR(lep1,jets) = "<< minDR_lep1Jet << std::endl;
      if(DEBUGjets||DEBUGleptons) std::cout << "min dR(lep2,jets) = "<< minDR_lep2Jet << std::endl;
      //      if(DEBUGjets||DEBUGleptons) std::cout << "min dR(lep3,jets) = "<< minDR_lep3Jet << std::endl;
      if(DEBUGjets||DEBUGleptons) std::cout << "min dR(leps,jets) = "<< minDR_lepJet << std::endl;
      
      /*
      // ----------------------------------------------------------------------------
      // AK8 Jet - lepton associations, Top and W taggging
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"AK8 Jet - lepton associations, Top and W taggging"<<std::endl;      

      NJetsWtagged_0p6 = 0;
      NJetsTtagged_0p81 = 0;
      deltaR_lepAK8s.clear();
      deltaPhi_lepAK8s.clear();
      mass_lepAK8s.clear();
      minDR_lepAK8 = 1000;
      minDR_leadAK8otherAK8 = 1000;
      if(theJetAK8Pt_JetSubCalc_PtOrdered.size() < 1) minDR_lepAK8 = -99.0;      
      if(theJetAK8Pt_JetSubCalc_PtOrdered.size() < 2) minDR_leadAK8otherAK8 = -99.0;
      WJetLeadPt = -99.0;
      TJetLeadPt = -99.0;
      deltaRtopWjet = -99;     deltaPhitopWjet = -99;
      deltaRlepWjet = -99;     deltaPhilepWjet = -99;	  
      deltaRlepTjet = -99;     deltaPhilepTjet = -99;	  

      NJetsWtagged_0p6_shifts.clear();
      NJetsTtagged_0p81_shifts.clear();
      theJetAK8Wmatch_JetSubCalc_PtOrdered.clear();
      theJetAK8Hmatch_JetSubCalc_PtOrdered.clear();
      theJetAK8Zmatch_JetSubCalc_PtOrdered.clear();
      theJetAK8Tmatch_JetSubCalc_PtOrdered.clear();
      theJetAK8MatchedPt_JetSubCalc_PtOrdered.clear();
      WJetLeadPt_shifts.clear();
      TJetLeadPt_shifts.clear();
      deltaRtopWjet_shifts.clear();  deltaPhitopWjet_shifts.clear(); 
      deltaRlepWjet_shifts.clear();  deltaPhilepWjet_shifts.clear(); 
      deltaRlepTjet_shifts.clear();  deltaPhilepTjet_shifts.clear(); 

      wjet1_lv.SetPtEtaPhiM(0,0,0,0);
      tjet1_lv.SetPtEtaPhiM(0,0,0,0);
      ak8_lv.SetPtEtaPhiM(0,0,0,0);
      TLorentzVector leadak8;
      leadak8.SetPtEtaPhiM(0,0,0,0);

      for(int i = 0; i < 2; i++){
		NJetsWtagged_0p6_shifts.push_back(0);
		NJetsTtagged_0p81_shifts.push_back(0);
		WJetLeadPt_shifts.push_back(-99.0);
		TJetLeadPt_shifts.push_back(-99.0);
		deltaRtopWjet_shifts.push_back(-99.0);  deltaPhitopWjet_shifts.push_back(-99.0); 
		deltaRlepWjet_shifts.push_back(-99.0);  deltaPhilepWjet_shifts.push_back(-99.0); 
		deltaRlepTjet_shifts.push_back(-99.0);  deltaPhilepTjet_shifts.push_back(-99.0); 
      }
      */
      
      /*

      for(unsigned int ijet=0; ijet < theJetAK8Pt_JetSubCalc_PtOrdered.size(); ijet++){

		// ----------------------------------------------------------------------------
		// AK8 - lepton and AK8 -- AK8 associations
		// ----------------------------------------------------------------------------
		if(DEBUG)std::cout<<"AK8 - lepton and AK8 -- AK8 associations"<<std::endl;      
	
		ak8_lv.SetPtEtaPhiE(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),theJetAK8Energy_JetSubCalc_PtOrdered.at(ijet));
		if(ijet == 0) leadak8 = ak8_lv;
		*/

		/* From SingleLep
		deltaR_lepAK8s.push_back(lepton_lv.DeltaR(ak8_lv));
		deltaPhi_lepAK8s.push_back(lepton_lv.DeltaPhi(ak8_lv));
		mass_lepAK8s.push_back((lepton_lv+ak8_lv).M());
	
		if(lepton_lv.DeltaR(ak8_lv) < minDR_lepAK8) minDR_lepAK8 = lepton_lv.DeltaR(ak8_lv);
		*/
		
		/*

		if(ijet > 0){
		  float tempdr = leadak8.DeltaR(ak8_lv);
		  if(tempdr < minDR_leadAK8otherAK8){
			minDR_leadAK8otherAK8 = tempdr;
		  }
		}

		// ----------------------------------------------------------------------------
		// W & top tagging on MC
		// ----------------------------------------------------------------------------
		if(DEBUG)std::cout<<"W & top tagging on MC"<<std::endl;      

		float tau21 = theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.at(ijet)/theJetAK8NjettinessTau1_JetSubCalc_PtOrdered.at(ijet);
		float tau32 = theJetAK8NjettinessTau3_JetSubCalc_PtOrdered.at(ijet)/theJetAK8NjettinessTau2_JetSubCalc_PtOrdered.at(ijet);
		float mass = theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered.at(ijet);
		float massSD = theJetAK8SoftDropMass_JetSubCalc_PtOrdered.at(ijet);

		// ------------------------------------------------------------------------------------------------------------------
		// MC Calculation first
		// ------------------------------------------------------------------------------------------------------------------
		if(DEBUG)std::cout<<"MC Calculation first"<<std::endl;      

		if(isMC){

		  // ------------------------------------------------------------------------------------------------------------------
		  // TRUTH MATCHING
		  // ------------------------------------------------------------------------------------------------------------------
		  float minDR = 1000;
		  float matchedPt= -99;
		  int matchedID = 0;
		  bool isWmatched = false;
		  bool isHmatched = false;
		  bool isZmatched = false;
		  bool isTmatched = false;
		  TLorentzVector trueW,d1,d2,d3;

		  for(unsigned int iW = 0; iW < HadronicVHtPt_JetSubCalc->size(); iW++){
			trueW.SetPtEtaPhiE(HadronicVHtPt_JetSubCalc->at(iW),HadronicVHtEta_JetSubCalc->at(iW),HadronicVHtPhi_JetSubCalc->at(iW),HadronicVHtEnergy_JetSubCalc->at(iW));

			if(ak8_lv.DeltaR(trueW) < minDR){
			  minDR = ak8_lv.DeltaR(trueW);
			  matchedPt = HadronicVHtPt_JetSubCalc->at(iW);
			  matchedID = abs(HadronicVHtID_JetSubCalc->at(iW));	      
			  d1.SetPtEtaPhiE(HadronicVHtD0Pt_JetSubCalc->at(iW),HadronicVHtD0Eta_JetSubCalc->at(iW),HadronicVHtD0Phi_JetSubCalc->at(iW),HadronicVHtD0E_JetSubCalc->at(iW));
			  d2.SetPtEtaPhiE(HadronicVHtD1Pt_JetSubCalc->at(iW),HadronicVHtD1Eta_JetSubCalc->at(iW),HadronicVHtD1Phi_JetSubCalc->at(iW),HadronicVHtD1E_JetSubCalc->at(iW));
			  d3.SetPtEtaPhiE(HadronicVHtD2Pt_JetSubCalc->at(iW),HadronicVHtD2Eta_JetSubCalc->at(iW),HadronicVHtD2Phi_JetSubCalc->at(iW),HadronicVHtD2E_JetSubCalc->at(iW));
			}
		  }	 
  
		  bool WallDsInJet = false;
		  bool TallDsInJet = false;
		  if(matchedID != 6 && ak8_lv.DeltaR(d1) < 0.8 && ak8_lv.DeltaR(d2) < 0.8) WallDsInJet = true;
		  if(matchedID == 6 && ak8_lv.DeltaR(d1) < 0.8 && ak8_lv.DeltaR(d2) < 0.8 && ak8_lv.DeltaR(d3) < 0.8) TallDsInJet = true;
		  if(minDR < 0.8 && matchedID == 24 && WallDsInJet) isWmatched = true;
		  if(minDR < 0.8 && matchedID == 25 && WallDsInJet) isHmatched = true;
		  if(minDR < 0.8 && matchedID == 23 && WallDsInJet) isZmatched = true;
		  if(minDR < 0.8 && matchedID == 6 && TallDsInJet) isTmatched = true;

		  theJetAK8Wmatch_JetSubCalc_PtOrdered.push_back(isWmatched);
		  theJetAK8Hmatch_JetSubCalc_PtOrdered.push_back(isHmatched);
		  theJetAK8Zmatch_JetSubCalc_PtOrdered.push_back(isZmatched);
		  theJetAK8Tmatch_JetSubCalc_PtOrdered.push_back(isTmatched);
		  if(isWmatched || isZmatched || isHmatched || isTmatched) theJetAK8MatchedPt_JetSubCalc_PtOrdered.push_back(matchedPt);
		  else theJetAK8MatchedPt_JetSubCalc_PtOrdered.push_back(-99.0);
		  */
	  
		  // ------------------------------------------------------------------------------------------------------------------
		  // W TAGGING
		  // ------------------------------------------------------------------------------------------------------------------
	  
		  /*
	  
		  float tau0p6SF = 1.0;
		  float tau0p6SFup = 1.0;
		  float tau0p6SFdn = 1.0;
		  double tau0p6Eff = 1.0;
		  if(isWmatched){	    
			// VALUES FOR 76X FROM TWIKI 76X with JEC v2
			tau0p6SF = 0.980;
			tau0p6SFup = 1.014;
			tau0p6SFdn = 0.946;
	  
			// Use matched W to find the efficiency -- calculated for TpTp and ttbar, EWK/QCD will almost never pass here (use ttbar eff when they do)
			if(isSig){
			  int bin = (std::upper_bound(ptRangeTpTp.begin(), ptRangeTpTp.end(), matchedPt)-ptRangeTpTp.begin())-1;
			  tau0p6Eff = SignalEff[SigMass][bin];
			}else{
			  int bin = (std::upper_bound(ptRangeTTbar.begin(), ptRangeTTbar.end(), matchedPt)-ptRangeTTbar.begin())-1;
			  if(isTT) tau0p6Eff = TTbarEff[bin]; // ttbar
			  else if(isST) tau0p6Eff = STEff[bin]; // single top (s and t channel had 0 boosted tops)
			  else if(isTTV) tau0p6Eff = TTVEff[bin]; // tt+V
			  else tau0p6Eff = WVEff[bin]; // WW, WZ, etc. 
			}
		  }

		  // Set the initial tagged/untagged state
		  bool isWtagged = (mass > 65) && (mass < 105) && (tau21 < 0.6);
 
		  // IF THE JET IS NOT TRUTH-MATCHED, THESE IFS WILL DO NOTHING, SF == 1
		  int tag_tau0p6 = applySF(isWtagged,tau0p6SF,tau0p6Eff);
		  int tag_tau0p6up = applySF(isWtagged,tau0p6SFup,tau0p6Eff);
		  int tag_tau0p6dn = applySF(isWtagged,tau0p6SFdn,tau0p6Eff);
	  
		  // Now increase the tag count in the right variable	  
		  NJetsWtagged_0p6 += tag_tau0p6;
		  NJetsWtagged_0p6_shifts[0] += tag_tau0p6up;
		  NJetsWtagged_0p6_shifts[1] += tag_tau0p6dn;
	  
		  */

		  // ------------------------------------------------------------------------------------------------------------------
		  // Variables for W tagged jets
		  // ------------------------------------------------------------------------------------------------------------------
	  
		  /*
		  if(tag_tau0p6 == 1){
			if(NJetsWtagged_0p6 == 1){
			  WJetLeadPt = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
			  wjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
						theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),mass);
			  deltaRtopWjet = wjet1_lv.DeltaR(lvTop);
			  deltaRlepWjet = wjet1_lv.DeltaR(lepton_lv);
			  deltaPhitopWjet = wjet1_lv.DeltaPhi(lvTop);
			  deltaPhilepWjet = wjet1_lv.DeltaPhi(lepton_lv);
			}
		  }
		  if(tag_tau0p6up == 1){
			if(NJetsWtagged_0p6_shifts[0] == 1){
			  WJetLeadPt_shifts.at(0) = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
			  wjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
						theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),mass);
			  deltaRtopWjet_shifts.at(0) = wjet1_lv.DeltaR(lvTop);
			  deltaRlepWjet_shifts.at(0) = wjet1_lv.DeltaR(lepton_lv);
			  deltaPhitopWjet_shifts.at(0) = wjet1_lv.DeltaPhi(lvTop);
			  deltaPhilepWjet_shifts.at(0) = wjet1_lv.DeltaPhi(lepton_lv);
			}
		  }
		  if(tag_tau0p6dn == 1){
			if(NJetsWtagged_0p6_shifts[1] == 1){
			  WJetLeadPt_shifts.at(1) = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
			  wjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
						theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),mass);
			  deltaRtopWjet_shifts.at(1) = wjet1_lv.DeltaR(lvTop);
			  deltaRlepWjet_shifts.at(1) = wjet1_lv.DeltaR(lepton_lv);
			  deltaPhitopWjet_shifts.at(1) = wjet1_lv.DeltaPhi(lvTop);
			  deltaPhilepWjet_shifts.at(1) = wjet1_lv.DeltaPhi(lepton_lv);
			}
		  }
		  */

		  // ------------------------------------------------------------------------------------------------------------------
		  // TOP TAGGING
		  // ------------------------------------------------------------------------------------------------------------------
	  
		  /*
		  float topTau81SF = 1.0;
		  float topTau81SFup = 1.0;
		  float topTau81SFdn = 1.0;
		  double topTau81Eff = 1.0;
		  if(isTmatched){	    
			// VALUES FOR 76X FROM PAS
			topTau81SF = 0.96;
			topTau81SFup = 1.04;
			topTau81SFdn = 0.88;
	  
			// Use matched T to find the efficiency -- calculated for TpTp and ttbar, EWK/QCD will almost never pass here (use ttbar eff when they do)
			if(isSig){
			  int bin = (std::upper_bound(ptRangeTpTpTop.begin(), ptRangeTpTpTop.end(), matchedPt)-ptRangeTpTpTop.begin())-1;
			  topTau81Eff = SignalEffTop[SigMass][bin];
			}else{
			  int bin = (std::upper_bound(ptRangeTTbarTop.begin(), ptRangeTTbarTop.end(), matchedPt)-ptRangeTTbarTop.begin())-1;
			  topTau81Eff = TTbarEffTop[bin];
			}
		  }

		  // Set the initial tagged/untagged state
		  bool isTtagged = (massSD > 105) && (massSD < 220) && (tau32 < 0.81);

		  // IF THE JET IS NOT TRUTH-MATCHED, THESE IFS WILL DO NOTHING, SF == 1
		  int tag_topTau81 = applySF(isTtagged,topTau81SF,topTau81Eff);
		  int tag_topTau81up = applySF(isTtagged,topTau81SFup,topTau81Eff);
		  int tag_topTau81dn = applySF(isTtagged,topTau81SFdn,topTau81Eff);
 
		  // Now increase the tag count in the right variable	  
		  NJetsTtagged_0p81 += tag_topTau81;
		  NJetsTtagged_0p81_shifts[0] += tag_topTau81up;
		  NJetsTtagged_0p81_shifts[1] += tag_topTau81dn;	  
		  */

		  // ------------------------------------------------------------------------------------------------------------------
		  // Variable for top tagged jets
		  // ------------------------------------------------------------------------------------------------------------------
	  
		  /*
		  if(tag_topTau81 == 1){
			TJetLeadPt = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
			if(NJetsTtagged_0p81 == 1){
			  tjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
						theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),massSD);
			  deltaRlepTjet = tjet1_lv.DeltaR(lepton_lv);
			  deltaPhilepTjet = tjet1_lv.DeltaPhi(lepton_lv);
			}
		  }
		  if(tag_topTau81up == 1){
			TJetLeadPt_shifts.at(0) = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
			if(NJetsTtagged_0p81_shifts[0] == 1){
			  tjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
						theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),massSD);
			  deltaRlepTjet_shifts.at(0) = tjet1_lv.DeltaR(lepton_lv);
			  deltaPhilepTjet_shifts.at(0) = tjet1_lv.DeltaPhi(lepton_lv);
			}
		  }
		  if(tag_topTau81dn == 1){
			TJetLeadPt_shifts.at(1) = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
			if(NJetsTtagged_0p81_shifts[1] == 1){
			  tjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
						theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),massSD);
			  deltaRlepTjet_shifts.at(1) = tjet1_lv.DeltaR(lepton_lv);
			  deltaPhilepTjet_shifts.at(1) = tjet1_lv.DeltaPhi(lepton_lv);
			}
		  }

		}
		
		
		// ------------------------------------------------------------------------------------------------------------------
		// DATA Calculation second
		// ------------------------------------------------------------------------------------------------------------------
		if(DEBUG)std::cout<<"DATA Calculation second"<<std::endl;
		      
		else{
	 
		  theJetAK8Wmatch_JetSubCalc_PtOrdered.push_back(0);
		  theJetAK8Hmatch_JetSubCalc_PtOrdered.push_back(0);
		  theJetAK8Zmatch_JetSubCalc_PtOrdered.push_back(0);
		  theJetAK8Tmatch_JetSubCalc_PtOrdered.push_back(0);
	  
		  if(tau21 < 0.6 && mass > 65.0 && mass < 105.0){

			NJetsWtagged_0p6 += 1;
			if(NJetsWtagged_0p6 == 1){
			  WJetLeadPt = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
			  wjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
						theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),mass);
			  deltaRtopWjet = wjet1_lv.DeltaR(lvTop);
			  deltaRlepWjet = wjet1_lv.DeltaR(lepton_lv);
			  deltaPhitopWjet = wjet1_lv.DeltaPhi(lvTop);
			  deltaPhilepWjet = wjet1_lv.DeltaPhi(lepton_lv);
			}
		  }
		  if(tau32 < 0.81 && massSD > 105.0 && massSD < 220.0){

			NJetsTtagged_0p81 += 1;
			if(NJetsTtagged_0p81 == 1){
			  TJetLeadPt = theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet);
			  tjet1_lv.SetPtEtaPhiM(theJetAK8Pt_JetSubCalc_PtOrdered.at(ijet),theJetAK8Eta_JetSubCalc_PtOrdered.at(ijet),
						theJetAK8Phi_JetSubCalc_PtOrdered.at(ijet),massSD);
			  deltaRlepTjet = tjet1_lv.DeltaR(lepton_lv);
			  deltaPhilepTjet = tjet1_lv.DeltaPhi(lepton_lv);
			}
		  }
		}
      }
	 */

      // ----------------------------------------------------------------------------
      // PDF and Matrix Element energy scale weights
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"PDF and Matrix Element energy scale weights"<<std::endl;      

      std::vector<double> renorm;
      std::vector<double> pdf;
      renormWeights.clear();
      pdfWeights.clear();
      if(isSig){
		// SEEMS TO APPLY TO ALL B2G MG+PYTHIA SIGNALS. LEADING ORDER 4-FLAVOR PDF
		for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
		  if(LHEweightids_singleLepCalc->at(i) > 1 && LHEweightids_singleLepCalc->at(i) < 10){
			if(LHEweightids_singleLepCalc->at(i) == 6 || LHEweightids_singleLepCalc->at(i) == 8) continue;
			renorm.push_back(LHEweights_singleLepCalc->at(i));
			renormWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		  if(LHEweightids_singleLepCalc->at(i) > 111 && LHEweightids_singleLepCalc->at(i) < 212){
			pdf.push_back(LHEweights_singleLepCalc->at(i));	    
			pdfWeights.push_back(LHEweights_singleLepCalc->at(i));	    
		  }
		}
      }
      else if(isMadgraphBkg){
		// SEEMS TO APPLY TO OTHER MG+PYTHIA BACKGROUNDS. LEADING ORDER 5-FLAVOR PDF
		for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
		  if(LHEweightids_singleLepCalc->at(i) > 1 && LHEweightids_singleLepCalc->at(i) < 10){
			if(LHEweightids_singleLepCalc->at(i) == 6 || LHEweightids_singleLepCalc->at(i) == 8) continue;
			renorm.push_back(LHEweights_singleLepCalc->at(i));
			renormWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		  if(LHEweightids_singleLepCalc->at(i) > 10 && LHEweightids_singleLepCalc->at(i) < 111){
			pdf.push_back(LHEweights_singleLepCalc->at(i));
			pdfWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		}
      }
      else{
		// SEEMS TO APPLY TO ALL POWHEG AND MC@NLO BACKGROUNDS. NLO PDFs
		for(unsigned int i = 0; i < LHEweightids_singleLepCalc->size(); i++){
		  if(LHEweightids_singleLepCalc->at(i) > 1001 && LHEweightids_singleLepCalc->at(i) < 1010){
			if(LHEweightids_singleLepCalc->at(i) == 1006 || LHEweightids_singleLepCalc->at(i) == 1008) continue;
			renorm.push_back(LHEweights_singleLepCalc->at(i));
			renormWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		  if(LHEweightids_singleLepCalc->at(i) > 2000 && LHEweightids_singleLepCalc->at(i) < 2101){
			pdf.push_back(LHEweights_singleLepCalc->at(i));
			pdfWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		  if(LHEweightids_singleLepCalc->at(i) == 2101 || LHEweightids_singleLepCalc->at(i) == 2102){
			alphaSWeights.push_back(LHEweights_singleLepCalc->at(i));
		  }
		}
      }

      if(renormWeights.size() == 0){
		for(int irn = 0; irn < 6; irn++){
		  renormWeights.push_back(1.0);
		}
      }
      if(pdfWeights.size() == 0){
		for(int ipdf = 0; ipdf < 100; ipdf++){
		  pdfWeights.push_back(1.0);
		}
      }

      // ----------------------------------------------------------------------------
      // DONE!! Write the tree
      // ----------------------------------------------------------------------------
      if(DEBUG)std::cout<<"DONE!! Write the tree"<<std::endl;      

      MCPastTrigger_dilep         = (int)   isPastTrigMC_dilep;
      DataPastTrigger_dilep       = (int)   isPastTrig_dilep;
      MCPastTrigger_dilepDZ4runH      = (int)   isPastTrigMC_dilepDZ4runH;
      DataPastTrigger_dilepDZ4runH    = (int)   isPastTrig_dilepDZ4runH;
      MCPastTrigger_dilepHT         = (int)   isPastTrigMC_dilepHT;
      DataPastTrigger_dilepHT       = (int)   isPastTrig_dilepHT;
      //MCPastTrigger_trilep         = (int)   isPastTrigMC_trilep;
      //DataPastTrigger_trilep       = (int)   isPastTrig_trilep;
      
      if(DEBUGjets)std::cout<< "NJets (just before filling tree) = " << NJets_singleLepCalc << std::endl;
 
      outputTree->Fill();
   }

   std::cout<<""<<std::endl;
   std::cout<<"=======END STATS==========   "<<std::endl;
   std::cout<<""<<std::endl;

   //std::cout<<"Nelectrons             = "<<Nelectrons<<" / "<<nentries<<std::endl;
   //std::cout<<"Nmuons                 = "<<Nmuons<<" / "<<nentries<<std::endl;
   //std::cout<<"Npassed_Mu500          = "<<npass_mu500<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_Trigger(DATA)  = "<<npass_trigger<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_MET            = "<<npass_met<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_dilepPt       = "<<npass_dilepPt<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_JetLeadPt      = "<<npass_JetLeadPt<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_JetSubLeadPt   = "<<npass_JetSubLeadPt<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_nJets          = "<<npass_njets<<" / "<<nentries<<std::endl;
   //std::cout<<"Npassed_ElEta          = "<<npass_ElEta<<" / "<<nentries<<std::endl;
   std::cout<<"Npassed_ALL            = "<<npass_all<<" / "<<nentries<<std::endl;

   printf("Counts of ee: LL(%i), LT(%i), TT(%i) : %i \n", Nee[0], Nee[1], Nee[2], EE_count);
   printf("Counts of em: LL(%i), LT(%i), TT(%i) : %i \n", Nem[0], Nem[1], Nem[2], EM_count);
   printf("Counts of mm: LL(%i), LT(%i), TT(%i) : %i \n", Nmm[0], Nmm[1], Nmm[2], MM_count);
//   printf("Counts of mmm: LLL(%i), LLT(%i), LTT(%i), TTT(%i) : %i \n", Nmmm[0], Nmmm[1], Nmmm[2], Nmmm[3], MMM_count);

   std::cout<<""<<std::endl;

   outputTree->Write();

}
