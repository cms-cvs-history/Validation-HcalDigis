#include <iostream.h>
#include "TFile.h"
#include "TTree.h"
#include "TText.h"

void hcaloval(const char* run, Bool_t drawhist = false){
 gROOT ->Reset();
 char name[50] ;
 char det[50] = run;
 
 TString PathToRef = "../data/";
 TString rfilename;
 rfilename = PathToRef+ "HcalDigisValidation" +run + "_ref.root";
 TString sfilename= "";
 sfilename = sfilename +  "HcalDigisValidation" +run + ".root";


 delete gROOT->GetListOfFiles()->FindObject(rfilename);
 delete gROOT->GetListOfFiles()->FindObject(sfilename);

 // TText* te = new TText();
 // te->SetTextSize(0.1);
 TFile * rfile = new TFile(rfilename);
 TFile * sfile = new TFile(sfilename);

 rfile->cd("DQMData/HcalDigiTask");
 gDirectory->ls();

 sfile->cd("DQMData/HcalDigiTask");
 gDirectory->ls();

 Char_t histo[200];

 gStyle->SetOptStat("n");

 gROOT->ProcessLine(".x HistoCompare.C");
 HistoCompare * myPV = new HistoCompare();


 TH1* meEta_;
 TString name_meEta = "DQMData/HcalDigiTask/HcalDigiTask_Eta_of_digis_";
 name_meEta = name_meEta + run + ";1";;
 rfile->GetObject( name_meEta ,meEta_);
 TH1* meEta_new;
 sfile->GetObject( name_meEta,meEta_new);
 
 myPV->PVCompute(meEta_ ,meEta_new  , drawhist);
 
  
 
 TH1* mePhi_;
 TString name_mePhi = "DQMData/HcalDigiTask/HcalDigiTask_Phi_of_digis_";
 name_mePhi = name_mePhi + run + ";1";
 
 rfile->GetObject(name_mePhi,mePhi_);
 
 TH1* mePhi_new;
 sfile->GetObject(name_mePhi,mePhi_new);
 
 myPV->PVCompute(mePhi_ ,mePhi_new  , drawhist);
 
 
 TH1* menDigis_;
 TString name_menDigis = "DQMData/HcalDigiTask/HcalDigiTask_number_of_digis_";
 name_menDigis = name_menDigis + run + ";1";
 
 rfile->GetObject(name_menDigis,menDigis_);
 
 TH1* menDigis_new;
 sfile->GetObject(name_menDigis,menDigis_new);
 
 myPV->PVCompute(menDigis_ ,menDigis_new , drawhist);
 

 
 TH2* meDigiSimhit_;
 TString name_meDigiSimhit = "DQMData/HcalDigiTask/HcalDigiTask_energy_digis_vs_simhits_";
 name_meDigiSimhit = name_meDigiSimhit + run + ";1";
 rfile->GetObject(name_meDigiSimhit,meDigiSimhit_);
   
 
 TH2* meDigiSimhit_new;
 sfile->GetObject(name_meDigiSimhit,meDigiSimhit_new); 
 
 myPV->PVCompute(meDigiSimhit_->ProfileY() ,meDigiSimhit_new->ProfileY() , drawhist);
 
 
 
 TH1* meSumDigis_;
 TString name_meSumDigis = "DQMData/HcalDigiTask/HcalDigiTask_sum_over_digis(fC)_";
 name_meSumDigis = name_meSumDigis + run + ";1";
 rfile->GetObject(name_meSumDigis  , meSumDigis_  );
 
 TH1* meSumDigis_new;
 sfile->GetObject(name_meSumDigis ,meSumDigis_new ); 
 myPV->PVCompute(meSumDigis_ ,meSumDigis_new , drawhist);
   
   
}
