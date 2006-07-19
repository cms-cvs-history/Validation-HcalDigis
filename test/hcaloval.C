#include <iostream.h>
#include "TFile.h"
#include "TTree.h"
#include "TText.h"

void hcaloval(const char* run, const char* drawhist = "none"){
 gROOT ->Reset();
 if (drawhist == "ps"){
   TCanvas *hcal = new TCanvas("Hcal","Hcal",0,0,707,500 );
   TString figure;
   figure = "figure";
   figure += run;
   figure += ".ps";
   ps = new TPostScript(figure , -112);
   ps->Range(29.7 , 21.0);
 }

 char name[50] ;
 char det[10] = run;
 
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

 char noise = "n";
 if( det[1] == noise ){

   TH1* meSumDigisHB_;
   TString name_meSumDigisHB = "DQMData/HcalDigiTask/HcalDigiTask_sum_over_digis(fC)";
   name_meSumDigisHB = name_meSumDigisHB + run + "_HB;1";
   rfile->GetObject(name_meSumDigisHB  , meSumDigisHB_  );
 
   TH1* meSumDigisHB_new;
   sfile->GetObject(name_meSumDigisHB ,meSumDigisHB_new ); 
   myPV->PVCompute(meSumDigisHB_ ,meSumDigisHB_new , drawhist);
   if (drawhist == "ps") { hcal->Update(); ps->NewPage();}
   //===============================
   TH1* meSumDigisHE_;
   TString name_meSumDigisHE = "DQMData/HcalDigiTask/HcalDigiTask_sum_over_digis(fC)";
   name_meSumDigisHE = name_meSumDigisHE + run + "_HE;1";
   rfile->GetObject(name_meSumDigisHE  , meSumDigisHE_  );
 
   TH1* meSumDigisHE_new;
   sfile->GetObject(name_meSumDigisHE ,meSumDigisHE_new ); 
   myPV->PVCompute(meSumDigisHE_ ,meSumDigisHE_new , drawhist);
   if (drawhist == "ps") { hcal->Update(); ps->NewPage();}
   //===================================
   TH1* meSumDigisHF_;
   TString name_meSumDigisHF = "DQMData/HcalDigiTask/HcalDigiTask_sum_over_digis(fC)";
   name_meSumDigisHF = name_meSumDigisHF + run + "_HF;1";
   rfile->GetObject(name_meSumDigisHF  , meSumDigisHF_  );
 
   TH1* meSumDigisHF_new;
   sfile->GetObject(name_meSumDigisHF ,meSumDigisHF_new ); 
   myPV->PVCompute(meSumDigisHF_ ,meSumDigisHF_new , drawhist);
   if (drawhist == "ps") { hcal->Update(); ps->NewPage();}
   //===================================
   TH1* meSumDigisHO_;
   TString name_meSumDigisHO = "DQMData/HcalDigiTask/HcalDigiTask_sum_over_digis(fC)";
   name_meSumDigisHO = name_meSumDigisHO + run + "_HO;1";
   rfile->GetObject(name_meSumDigisHO  , meSumDigisHO_  );
 
   TH1* meSumDigisHO_new;
   sfile->GetObject(name_meSumDigisHO ,meSumDigisHO_new ); 
   myPV->PVCompute(meSumDigisHO_ ,meSumDigisHO_new , drawhist);
   if (drawhist == "ps") { hcal->Update(); ps->NewPage();}
 }

 
if( det[1] != noise){

 TH1* meEta_;
 TString name_meEta = "DQMData/HcalDigiTask/HcalDigiTask_Eta_of_digis_";
 name_meEta = name_meEta + run + ";1";;
 rfile->GetObject( name_meEta ,meEta_);
 TH1* meEta_new;
 sfile->GetObject( name_meEta,meEta_new);
 
 myPV->PVCompute(meEta_ ,meEta_new  , drawhist);
 if (drawhist == "ps") { hcal->Update(); ps->NewPage();}
  
 
 TH1* mePhi_;
 TString name_mePhi = "DQMData/HcalDigiTask/HcalDigiTask_Phi_of_digis_";
 name_mePhi = name_mePhi + run + ";1";
 
 rfile->GetObject(name_mePhi,mePhi_);
 
 TH1* mePhi_new;
 sfile->GetObject(name_mePhi,mePhi_new);
 
 myPV->PVCompute(mePhi_ ,mePhi_new  , drawhist);
 if (drawhist == "ps") { hcal->Update(); ps->NewPage();}
 
 TH1* menDigis_;
 TString name_menDigis = "DQMData/HcalDigiTask/HcalDigiTask_number_of_digis_";
 name_menDigis = name_menDigis + run + ";1";
 
 rfile->GetObject(name_menDigis,menDigis_);
 
 TH1* menDigis_new;
 sfile->GetObject(name_menDigis,menDigis_new);
 
 myPV->PVCompute(menDigis_ ,menDigis_new , drawhist);
if (drawhist == "ps") { hcal->Update(); ps->NewPage();}

 
 TH2F* meDigiSimhit_;
 TString name_meDigiSimhit = "DQMData/HcalDigiTask/HcalDigiTask_energy_digis_vs_simhits_";

 name_meDigiSimhit = name_meDigiSimhit + run + ";1";
 rfile->GetObject(name_meDigiSimhit,meDigiSimhit_);
   
 
 TH2F* meDigiSimhit_new;
 sfile->GetObject(name_meDigiSimhit,meDigiSimhit_new); 
 
 myPV->PVCompute(meDigiSimhit_->ProfileX() ,meDigiSimhit_new->ProfileX() , drawhist);
 if (drawhist == "ps") { hcal->Update(); ps->NewPage();}
 //("",-1,-1,"i")
 
 
 TH1* meSumDigis_;
 TString name_meSumDigis = "DQMData/HcalDigiTask/HcalDigiTask_sum_over_digis(fC)_";
 name_meSumDigis = name_meSumDigis + run + ";1";
 rfile->GetObject(name_meSumDigis  , meSumDigis_  );
 
 TH1* meSumDigis_new;
 sfile->GetObject(name_meSumDigis ,meSumDigis_new ); 
 myPV->PVCompute(meSumDigis_ ,meSumDigis_new , drawhist);
 if (drawhist == "ps") { hcal->Update(); ps->NewPage();}
}  
 if (drawhist == "ps") ps->Close();
}
