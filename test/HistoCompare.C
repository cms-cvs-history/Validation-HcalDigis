#include "TCanvas.h"
#include <strstream>
#include "TString.h"
#include "TH1.h"
#include "TH2.h"
#include "TProfile.h"
#include "TText.h"
#include "TCanvas.h"
#include <iostream>

class HistoCompare {

 public:

  HistoCompare() {}

  void PVCompute(TH1 * oldHisto , TH1 * newHisto , char* drawhist);
  void PVCompute(TH2 * oldHisto , TH2 * newHisto , const char* drawhist);
  void PVCompute(TProfile * oldHisto , TProfile * newHisto , const char* drawhist);

 private:

  Double_t mypv;

  TH1 * myoldHisto1;
  TH1 * mynewHisto1;

  TH2 * myoldHisto2;
  TH2 * mynewHisto2;

  TProfile * myoldProfile;
  TProfile * mynewProfile;

  TCanvas * canvas;

  TText * myte;
  Bool_t  myhistdraw;

};


void HistoCompare::PVCompute(TH1 * oldHisto , TH1 * newHisto , char* drawoption)
{
  string histdraw(drawoption);
  myoldHisto1 = oldHisto;
  mynewHisto1 = newHisto;
  if ( histdraw == "ps" || histdraw == "gif"  ) {
    if ( histdraw == "gif" )  
      {canvas = new TCanvas("Hcal","Hcal",800,600);}
    oldHisto->UseCurrentStyle();
    newHisto->UseCurrentStyle();
    oldHisto->SetLineColor(45);
    newHisto->SetLineColor(47);
    oldHisto->Draw();
    newHisto->Draw("same");
    string name = oldHisto->GetTitle(); 
    name +=  ".gif" ;
    if ( histdraw == "gif" ) canvas->Print(name.c_str());
  } 
  
  Double_t *res;
  Double_t mypv = myoldHisto1->Chi2Test( mynewHisto1,"UU", res);

  std::strstream buf;
  std::string value;
  buf<<"PV="<<mypv<<std::endl;
  buf>>value;
  
  //  myte->DrawTextNDC(0.2,0.7, value.c_str());

  std::cout << "[OVAL] " << myoldHisto1->GetName() << " PV = " << mypv << std::endl;
  return;
  
}

void HistoCompare::PVCompute(TH2 * oldHisto , TH2 * newHisto , const char* drawoption)
{
  string histdraw(drawoption); 
  myoldHisto2 = oldHisto;
  mynewHisto2 = newHisto;
  if ( histdraw == "ps" || histdraw == "gif"  ) {
   
     if ( histdraw == "gif" )  
      {canvas = new TCanvas("Hcal","Hcal",800,600);}

    oldHisto->UseCurrentStyle();
    newHisto->UseCurrentStyle();
    oldHisto->SetLineColor(45);
    newHisto->SetLineColor(47);
    oldHisto->Draw();
    newHisto->Draw("same");
    string name = oldHisto->GetTitle(); 
    name +=  ".gif" ;
  
    if ( histdraw == "gif" ) canvas->Print(name.c_str());
  } 

  Double_t *res;
  Double_t mypv = myoldHisto2->Chi2Test( mynewHisto2,"UU", res);

  std::strstream buf;
  std::string value;
  buf<<"PV="<<mypv<<std::endl;
  buf>>value;
  
  //  myte->DrawTextNDC(0.2,0.7, value.c_str());
  
  std::cout << "[OVAL] " << myoldHisto2->GetName() << " PV = " << mypv << std::endl;
  return;
  
}


void HistoCompare::PVCompute(TProfile * oldHisto , TProfile * newHisto , const char* drawoption)
{
  string histdraw(drawoption);
  if ( histdraw == "ps" || histdraw == "gif"  ) {
   
    if ( histdraw == "gif" )  
      {canvas = new TCanvas("Hcal","Hcal",800,600);}
    oldHisto->UseCurrentStyle();
    newHisto->UseCurrentStyle();
    oldHisto->SetLineColor(45);
    newHisto->SetLineColor(47); 
    oldHisto->Draw();
    newHisto->Draw("same");
    string name = oldHisto->GetTitle(); 
    name +=  ".gif" ;
name = "test.gif";
    if ( histdraw == "gif" ) canvas->Print(name.c_str());
  }
  myoldProfile = oldHisto;
  mynewProfile = newHisto;
 

  Double_t *res;
  Double_t mypv = myoldProfile->Chi2Test( mynewProfile,"UU", res);
  std::strstream buf;
  std::string value;
  buf<<"PV="<<mypv<<std::endl;
  buf>>value;
  
  //  myte->DrawTextNDC(0.2,0.7, value.c_str());

  std::cout << "[OVAL] " << myoldProfile->GetName() << " PV = " << mypv << std::endl;
  return;

}
