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

  void PVCompute(TH1 * oldHisto , TH1 * newHisto , char* drawhist, char* addname);

 private:

  TCanvas * canvas;

  TText * myte;
  Bool_t  myhistdraw;

};


void HistoCompare::PVCompute(TH1 * oldHisto , TH1 * newHisto , char* drawoption, char* addname)
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
    name += addname;
    name +=  ".gif" ;
    if ( histdraw == "gif" ) canvas->Print(name.c_str());
  } 
  
  Double_t *res;
  Double_t mypv = oldHisto->Chi2Test( newHisto,"UU", res);

  std::strstream buf;
  std::string value;
  buf<<"PV="<<mypv<<std::endl;
  buf>>value;
  
  //  myte->DrawTextNDC(0.2,0.7, value.c_str());

  std::cout << "[OVAL] " << oldHisto->GetName() << " PV = " << mypv << std::endl;
  return;
  
}

