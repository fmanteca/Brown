#ifndef _FAKERATE_H
#define _FAKERATE_H
#include <TRandom2.h>
#include "Math/Random.h"
#include <iostream>
// #include "CMSStyle.C"

#include "TStyle.h"
#include "TColor.h"
#include "TFile.h"
#include <TH1F.h>
#include <TH2.h>
#include "TCanvas.h"

using namespace std;

bool DEBUGfakerate_h = false;

float Pr(int mode,std::vector<double> lep_info);
inline float uPr(std::vector<double> lep_info);
float Fr(int mode,std::vector<double> lep_info);
inline float uFr(std::vector<double> lep_info);

inline float uQe();

inline double epsilon(double f);//these are guearenteed to be small numbers
inline double eta(double p);//these are guearenteed to be small numbers

inline int frModeBehavior(int mode,int flavour);
inline int prModeBehavior(int mode,int flavour);
inline int qeModeBehavior(int mode);


std::vector<double> SF3Lepbkg(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3);
//output: {0:N_ppp, 1:N_fpp, 2:N_ffp, 3:N_fff, 4:N_signal, 5:N_1fake, 6:N_2fakes, 7:N_3fakes, 8:N_bkg}
double SF3Lepbkg_simple(double f, double p, int N_t0, int N_t1, int N_t2, int N_t3);

// double ChiSquared(int k); //what are these for??
// int ThrowPoissonFromMeasurement(TRandom2* r, int n); //what are these for??


/////////////////// Double lepton ////////////////////////
double GetWeight(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info);
/////////////////////////////

// TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRatePlots/FakeRate_Data_subtr_El_PtEta.root");
// TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRatePlots/FakeRate_Data_subtr_Mu_PtEta.root");

TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_El_PtEta.root");
TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_Mu_PtEta.root");

// TFile* file_el = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_El_Pt_1bin.root");
// TFile* file_mu = TFile::Open("/uscms_data/d3/rsyarif/Spring2016/TprimeFakeRateReproduce/FromJulie/CMSSW_7_4_14/src/LJMet/macros/step1/FakeRateFiles/withWJetsIncl_subtrDenom/FakeRate_Data_subtr_Mu_Pt_1bin.root");


TCanvas* c_el = (TCanvas*) file_el->Get("c1");
TCanvas* c_mu = (TCanvas*) file_mu->Get("c1");
TH2D *h_el = (TH2D*) c_el->GetPrimitive("newratioEl");
TH2D *h_mu = (TH2D*) c_mu->GetPrimitive("newratioMu");


float Pr(int mode, std::vector<double> lep_info){
  if(lep_info.at(0)==0){
    //ele prompt rate
    double pt_el = lep_info.at(2);
    double eta_el = lep_info.at(3);
    double weight = 0.0;
    
    //PRv5test, PRv7test, PRvElPRtest - to see how el fr affects things.
    // weight = 1.0;
    // return weight;

    //PRv6, PRv8test - from Clint https://mail.google.com/mail/u/0/#search/clint/159dc97c5d3fb221
    /* as given by Clint
       [1]
       30 < pt < 40 = 0.881
       40 < pt < 50 = 0.918
       50 < pt < 60 = 0.931
       60 < pt < 70 = 0.940
       70 < pt         = 0.950
    */
    // if(pt_el>=30. && pt_el < 40.) weight = 0.881;
    //         else if(pt_el<50) weight = 0.918;
    //         else if(pt_el<60) weight = 0.931;
    //         else if(pt_el<70)weight = 0.940;
    //         else weight = 0.950;
    // //if(DEBUGfakerate_h)std::cout << "elPR used (mode:"<<mode<<") = " << weight << " + " << "("<<prModeBehavior(mode)<<")"<<uPr(lep_info)<< std::endl;
    // if(DEBUGfakerate_h)std::cout << "Ele PR -- Mode: " << mode << ", " << weight <<" + "<< prModeBehavior(mode,lep_info.at(0)) <<  " * " << uPr(lep_info)<< endl;
    // return weight + uPr(lep_info)*prModeBehavior(mode,lep_info.at(0));

    //PRvMuPRtest,PRv9 from http://cms.cern.ch/iCMS/jsp/db_notes/noteInfo.jsp?cmsnoteid=CMS%20AN-2016/242 v16
    if(pt_el>=30. && pt_el < 40.) weight = 0.904;
    else if(pt_el<50) weight = 0.928;
    else if(pt_el<60) weight = 0.934;
    else if(pt_el<70) weight = 0.942;
    else if(pt_el<80) weight = 0.947;
    else if(pt_el<90) weight = 0.953;
    else if(pt_el<100) weight = 0.955;
    else if(pt_el<125) weight = 0.948;
    else if(pt_el<150) weight = 0.951;
    else if(pt_el<200) weight = 0.946;
    else if(pt_el<300) weight = 0.935;
    else if(pt_el<400) weight = 0.920;
    else if(pt_el<500) weight = 0.902;
    else weight = 0.800;
    //if(DEBUGfakerate_h)std::cout << "elPR used (mode:"<<mode<<") = " << weight << " + " << "("<<prModeBehavior(mode)<<")"<<uPr(lep_info)<< std::endl;
    if(DEBUGfakerate_h)std::cout << "Ele PR -- Mode: " << mode << ", " << weight <<" + "<< prModeBehavior(mode,lep_info.at(0)) <<  " * " << uPr(lep_info)<< endl;
    return weight + uPr(lep_info)*prModeBehavior(mode,lep_info.at(0));

  }
  else{
    //muon prompt rate
    double pt_mu = lep_info.at(2);
    double eta_mu = lep_info.at(3);
    double weight = 0.0;

    // PRv6, PRv7test, PRvElPRtest PRv9 - From Clint, https://indico.cern.ch/event/605620/contributions/2441087/attachments/1398025/2132153/VHFMeeting_X53_01.18.17.pdf http://cms.cern.ch/iCMS/jsp/db_notes/noteInfo.jsp?cmsnoteid=CMS%20AN-2016/242 v16 
    weight = 0.943; 
    //if(DEBUGfakerate_h)std::cout << "muPR used (mode:"<<mode<<") = " << weight << " + " << "("<<prModeBehavior(mode)<<")"<<uPr(lep_info)<< std::endl;
    if(DEBUGfakerate_h)std::cout << "Mu  PR -- Mode: " << mode << ", " << weight <<" + "<<  prModeBehavior(mode,lep_info.at(0)) << " * " << uPr(lep_info)<< endl;
    return weight + uPr(lep_info)*prModeBehavior(mode,lep_info.at(0)); 

    //PRvMuPRtest,PRv8test - to see how mu fr affects things.
    // weight = 1.0;
    // return weight;
  }
}

float Fr(int mode, std::vector<double> lep_info){
  if(lep_info.at(0)==0){
    //ele fake rate
    double pt_el = lep_info.at(2);
    double eta_el = lep_info.at(3);
    double weight = 0.0;
    
    if(lep_info.size()==4){ //before scan size is 4

      //FRv18b,18bSys - CR2 letPt PRv6 2 1bjet leppt>30 GeV, FRv19test
      // weight = 0.25 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv20b - CR2 letPt PRv6 2 1bjet leppt>30 GeV, fixedLumi, newMllOS
      // weight = 0.24 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv21test - applying zjets ttx SR/CR2 ratio
      // weight = 0.186 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv22 - CR2 letPt PRv6 latestLJMEtFeb242017
      // weight = 0.22 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv24 - CR2 letPt PRv6 latestLJMEtFeb242017_newMuTrkSF
      weight = 0.23 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv25ttbar
      // weight = 0.0 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv26ttbar
      // weight = 0.5 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv27
      // weight = 0.26 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv28ttbar
      // weight = 0.01 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv29CR1
      // weight = 0.29 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv30CR2 - CR2 letPt PRv9 latestLJMEtMar312017_newRunH, FRvMuEtatest
      // weight = 0.23 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv31CR1 - CR1 letPt PRv9 latestLJMEtMar312017_newRunH
      // weight = 0.29 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv32CR1CR2 - CR1CR2 letPt PRv9 latestLJMEtMar312017_newRunH
      // weight = 0.26 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

    }
    else{
      weight = lep_info.at(5);
    }

    // if(DEBUGfakerate_h)std::cout << "elFR used = " << weight << std::endl;
    if(DEBUGfakerate_h)std::cout << "Ele FR -- Mode: " << mode << ", " << frModeBehavior(mode,lep_info.at(0)) << " * " << uFr(lep_info)<<  endl;
    
    return weight; 


  }
  else{
    //muon fake rate
    double pt_mu = lep_info.at(2);
    double eta_mu = lep_info.at(3);
    double weight = 0.0;

    if(lep_info.size()==4) {  //before scan size is 4

      //FRv18b,18bSys - CR2 LepPt PRv6 1bjet lepPt>30 GeV
      // weight = 0.11 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv19test - model after Clints eta dependence
      // weight = ( 0.1203392 - 3.849218e-18*eta_mu + 0.0257206*(eta_mu*eta_mu) ) + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

      //FRv20b - CR2 letPt PRv6 2 1bjet leppt>30 GeV, fixedLumi, newMllOS
      // weight = 0.11 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv21test - applying zjets ttx SR/CR2 ratio
      // weight = 0.125 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv22 - CR2 letPt PRv6 latestLJMEtFeb242017, FRv24 - _newMuTrkSF
      weight = 0.15 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv26ttbar,FRv25ttbar
      // weight = 0.5 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv27
      // weight = 0.13 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv28ttbar
      // weight = 0.42 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRv29CR1
      // weight = 0.13 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRvMuEtatest - model after Clints eta dependence
      // weight = ( 0.15 - 3.849218e-18*eta_mu + 0.0257206*(eta_mu*eta_mu) ) + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

      //FRv30CR2,FRv31CR1 - letPt PRv9 latestLJMEtMar312017 _newRunH
      // weight = 0.16 + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0)); 

      //FRvMuEtatest - model after Clints eta dependence - central=FRv30CR2
      // weight = ( 0.16 - 3.849218e-18*eta_mu + 0.0257206*(eta_mu*eta_mu) ) + uFr(lep_info)*frModeBehavior(mode,lep_info.at(0));

    } 
    else{
      weight = lep_info.at(4);
    }
    
    // if(DEBUGfakerate_h)std::cout << "muFR used = " << weight << std::endl;
    if(DEBUGfakerate_h)std::cout << "Mu  FR -- Mode: " << mode << ", " << frModeBehavior(mode,lep_info.at(0)) << " * " << uFr(lep_info)<<  endl;

    return weight;

  }
}

inline float uPr(std::vector<double> lep_info){

  if(lep_info.at(0)==0){
    //ele prompt rate unc

    //PRv5test,PRv7test,PRvElPRtest
    // return 0.0;

    //PRv6,PRv8test,PRv9,PRvMuPRtest
    return 0.001;

  }
  else{
    //mu prompt rate unc

    return 0.001; // PRv3, PRv4, PRv5test, PRv6,PRv7test,PRv9,PRvElPRtest

    //PRv8test, PRvMuPRtest
    // return 0.0;

  }
}

inline float uFr(std::vector<double> lep_info){
  if(lep_info.at(0)==0){
    //ele fake rate unc

    //FRv18bSystaking into account systematics from closure test: sqrt(stat^2 +sys^2), FRv19test
    // return sqrt(0.04*0.04 + 0.05*0.05); 

    //FRv20b, FRv21test
    // return sqrt(0.03*0.03 + 0.06*0.06);

    //FRv22, FRv24, FRvMuEtatest
    return sqrt(0.03*0.03 + 0.06*0.06);

    //FRv26ttbar,FRv25ttbar,FRv28ttbar --> arbitraty/dummmy approx.
    // return sqrt(0.05*0.05);

    //FRv27
    // return sqrt(0.03*0.03);

    //FRv29CR1
    // return sqrt(0.06*0.06);

    //FRv30CR2, FRvMuEtatest
    // return sqrt(0.02*0.02 + 0.06*0.06);

    //FRv31CR1
    // return sqrt(0.01*0.01 + 0.06*0.06);

  }
  else{
    //mu fake rate unc

    //FRv18bSystaking into account systematics from closure test sqrt(stat^2 +sys^2), FRv19test
    // return sqrt(0.03*0.03 + 0.04*0.04); 

    //FRv20b, FRv21test
    // return sqrt(0.02*0.02 + 0.03*0.03);

    //FRv22, FRv24, FRvMuEtatest
    return sqrt(0.03*0.03 + 0.02*0.02);

    //FRv26ttbar,FRv25ttbar,FRv28ttbar --> arbitraty/dummmy approx.
    // return sqrt(0.05*0.05);

    //FRv27
    // return sqrt(0.02*0.02);

    //FRv29CR1
    // return sqrt(0.02*0.02);

    //FRv30CR2, FRv31CR2, FRvMuEtatest
    // return sqrt(0.02*0.02 + 0.0*0.0);

  }
}


inline float uQe(){return 0.30;}//percent

inline double epsilon(double f){return f/(1.0-f);} 
inline double eta(double p){return (1.0-p)/p;}


//    ____  
//   |___ \
//     __) |
//    |__ < 
//    ___) |
//   |____/ 
//          
//          


/////////////////////// FUNCTIONS FOR WEIGHTS /////////////////////
///////////////////////coifs for SS emu////////////////////////////
//mode 0 = nominal. 1 = elfakerate plus, 2 = elfakerate minus, 3 = elpassrate plus, 4 = elpassrate minus, 5 = mufakerate plus, 6 = mufakerate minus, 7 = mupassrate plus, 8 = mupassrate minus
inline int frModeBehavior(int mode,int flavour){
  int temp = 0; 
  if(flavour==0){
    if(mode==1) temp = 1;
    if(mode==2) temp = -1;
  }
  if(flavour==1){
    if(mode==5) temp = 1;
    if(mode==6) temp = -1;
  }
  return temp;
} //if electron:+1,-1 for 1,2 ; if muon:+1,-1 for 5,6, else 0
inline int prModeBehavior(int mode,int flavour){ 
  int temp = 0; 
  if(flavour==0){
    if(mode==3) temp = 1;
    if(mode==4) temp = -1;
  }
  if(flavour==1){
    if(mode==7) temp = 1;
    if(mode==8) temp = -1;
  }
  return temp;
} //if electron:+1,-1 for 3,4 ; if muon:+1,-1 for 7,8, else 0


inline double Det_em(double fe, double pe, double fm, double pm, double q){ return -(1.0 - 2.0* q)*(pe - fe)*(pm - fm); } //det is always negative.


/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
/////////////////Double Lepton /////////////////////////
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

/* Calculation: CMS AN-2010/261 */


double GetWeight(int mode, std::vector<double> lep1_info, std::vector<double> lep2_info){

  double promptProbability[2] = {1.0, 1.0};
  double fakeProbability[2] = {1.0, 1.0};

  int nTight = 0; 
 
  double f1 = Fr(mode, lep1_info);
  double p1 = Pr(mode, lep1_info);
  double f2 = Fr(mode, lep2_info);
  double p2 = Pr(mode, lep2_info);
  
  if (lep1_info.at(1) == 1)
      {
	nTight++;

	promptProbability[0] = p1 * (1 - f1) / (p1 - f1);
	fakeProbability[0]   = f1 * (1 - p1) / (p1 - f1);

	//cout << lep.flavour << "  "  << lep.pt << "  " << lep.eta << "  " << p << "  " << f << "  " << promptProbability[i] << "  " << fakeProbability[i]  << endl;

      }
  else if (lep1_info.at(1) == 0 ) 
      {
	promptProbability[0] = p1 * f1 / (p1 - f1);
	fakeProbability[0]   = p1 * f1 / (p1 - f1);
      }


  if (lep2_info.at(1) == 1)
      {
	nTight++;

	promptProbability[1] = p2 * (1 - f2) / (p2 - f2);
	fakeProbability[1]   = f2 * (1 - p2) / (p2 - f2);

	//cout << lep.flavour << "  "  << lep.pt << "  " << lep.eta << "  " << p << "  " << f << "  " << promptProbability[i] << "  " << fakeProbability[i]  << endl;

      }
  else if (lep2_info.at(1) == 0 ) 
      {
	promptProbability[1] = p2 * f2 / (p2 - f2);
	fakeProbability[1]   = p2 * f2 / (p2 - f2);
      }


  double PF = promptProbability[0] * fakeProbability[1];
  double FP = promptProbability[1] * fakeProbability[0];
  double FF = fakeProbability  [0] * fakeProbability[1];

  if (nTight == 1){
    FF *= -1.;
  }else {
    PF *= -1.;
    FP *= -1.;
  }

  double result = PF + FP + FF;
    
  return result;



}



#endif
