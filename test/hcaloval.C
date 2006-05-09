#include <iostream.h>
#include "TFile.h"
#include "TTree.h"
#include "TText.h"

void hcaloval(const char* run){
 gROOT ->Reset();
 char name[50] ;
 char det[50] = run;

 TString PathToRef = "";
 TString rfilename;
 rfilename = PathToRef+ "HcalDigisValidation" +run + "_ref.root";
 TString sfilename= "";
 sfilename = sfilename +  "HcalDigisValidation" +run + ".root";


 delete gROOT->GetListOfFiles()->FindObject(rfilename);
 delete gROOT->GetListOfFiles()->FindObject(sfilename);

 TText* te = new TText();
 te->SetTextSize(0.1);
 TFile * rfile = new TFile(rfilename);
 TFile * sfile = new TFile(sfilename);

 rfile->cd("DQMData/HcalDigiTask");
 gDirectory->ls();

 sfile->cd("DQMData/HcalDigiTask");
 gDirectory->ls();

 Char_t histo[200];

 gStyle->SetOptStat("n");

 gROOT->ProcessLine(".x HistoCompare.C");
 gROOT->ProcessLine(".x ChangeName.C");
 HistoCompare * myPV = new HistoCompare();

 

 //  TCanvas * Hcal = new TCanvas("Hcal","Hcal",800,1000);

   TH1* meEta_;
   TString name_meEta = "DQMData/HcalDigiTask/HcalDigiTask Eta of digis ";
   name_meEta = name_meEta + run + ";1";;
   rfile->GetObject( name_meEta ,meEta_);
   TH1* meEta_new;
   sfile->GetObject( name_meEta,meEta_new);

   myPV->PVCompute(meEta_ ,meEta_new  , te);



   TH1* mePhi_;
    TString name_mePhi = "DQMData/HcalDigiTask/HcalDigiTask Phi of digis ";
   name_mePhi = name_mePhi + run + ";1";

   rfile->GetObject(name_mePhi,mePhi_);

   TH1* mePhi_new;
   sfile->GetObject(name_mePhi,mePhi_new);

   myPV->PVCompute(mePhi_ ,mePhi_new  , te);

   
   TH1* menDigis_;
   TString name_menDigis = "DQMData/HcalDigiTask/HcalDigiTask number of digis ";
   name_menDigis = name_menDigis + run + ";1";

   rfile->GetObject(name_menDigis,menDigis_);

   TH1* menDigis_new;
   sfile->GetObject(name_menDigis,menDigis_new);

   myPV->PVCompute(menDigis_ ,menDigis_new , te);
   


   TH2* meDigiSimhit_;
   TString name_meDigiSimhit = "DQMData/HcalDigiTask/HcalDigiTask energy digis vs simhits ";
   name_meDigiSimhit = name_meDigiSimhit + run + ";1";
   rfile->GetObject(name_meDigiSimhit,meDigiSimhit_);

   TH2* meDigiSimhit_new;
   sfile->GetObject(name_meDigiSimhit,meDigiSimhit_new); 
   myPV->PVCompute(meDigiSimhit_ ,meDigiSimhit_new , te);


   
   TH1* meSumDigis_;
   TString name_meSumDigis = "DQMData/HcalDigiTask/HcalDigiTask sum over digis(fC) ";
   name_meSumDigis = name_meSumDigis + run + ";1";
   rfile->GetObject(name_meSumDigis  , meSumDigis_  );

   TH1* meSumDigis_new;
   sfile->GetObject(name_meSumDigis ,meSumDigis_new ); 
   myPV->PVCompute(meSumDigis_ ,meSumDigis_new , te);
   
   
}
