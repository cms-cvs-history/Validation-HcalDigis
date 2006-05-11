#include <iostream.h>

class HistoCompare {

 public:

  HistoCompare() { std::cout << "Initializing HistoCompare... " << std::endl; } ;

  void PVCompute(TH1 * oldHisto , TH1 * newHisto ,  Bool_t histdraw);
  void PVCompute(TH2 * oldHisto , TH2 * newHisto ,  Bool_t histdraw);
  void PVCompute(TProfile * oldHisto , TProfile * newHisto , Bool_t histdraw);

 private:
  
  Double_t mypv;

  TH1 * myoldHisto1;
  TH1 * mynewHisto1;

  TH2 * myoldHisto2;
  TH2 * mynewHisto2;

  TProfile * myoldProfile;
  TProfile * mynewProfile;

  TText * myte;
  Bool_t  myhistdraw;

};

HistoCompare::PVCompute(TH1 * oldHisto , TH1 * newHisto , Bool_t histdraw )
{
  myoldHisto1 = oldHisto;
  mynewHisto1 = newHisto;
  if ( histdraw ) {
    TCanvas * Hcal = new TCanvas("Hcal","Hcal",800,600);
    oldHisto->UseCurrentStyle();
    newHisto->UseCurrentStyle();
    oldHisto->SetLineColor(45);
    newHisto->SetLineColor(47);
    oldHisto->Draw();
    newHisto->Draw("same");
    TString name = oldHisto->GetTitle(); 
    name +=  ".gif" ;
    Hcal->Print(name);
  } 
  Double_t mypv = myoldHisto1->Chi2Test(mynewHisto1,"OU");
  std::strstream buf;
  std::string value;
  buf<<"PV="<<mypv<<std::endl;
  buf>>value;
  
  //  myte->DrawTextNDC(0.2,0.7, value.c_str());

  std::cout << "[OVAL] " << myoldHisto1->GetName() << " PV = " << mypv << std::endl;
  return;
  
}

HistoCompare::PVCompute(TH2 * oldHisto , TH2 * newHisto , Bool_t  histdraw )
{
  
  myoldHisto2 = oldHisto;
  mynewHisto2 = newHisto;
  if ( histdraw ) {
    TCanvas * Hcal = new TCanvas("Hcal","Hcal",800,600);
    oldHisto->UseCurrentStyle();
    newHisto->UseCurrentStyle();
    oldHisto->SetLineColor(45);
    newHisto->SetLineColor(47);
    oldHisto->Draw();
    newHisto->Draw("same");
    TString name = oldHisto->GetTitle(); 
    name +=  ".gif" ;
    Hcal->Print(name);
  } 

  Double_t mypv = myoldHisto2->Chi2Test(mynewHisto2,"OU");
  std::strstream buf;
  std::string value;
  buf<<"PV="<<mypv<<std::endl;
  buf>>value;
  
  //  myte->DrawTextNDC(0.2,0.7, value.c_str());
  
  std::cout << "[OVAL] " << myoldHisto2->GetName() << " PV = " << mypv << std::endl;
  return;
  
}


HistoCompare::PVCompute(TProfile * oldHisto , TProfile * newHisto , Bool_t histdraw )
{
  if ( histdraw ) {
    TCanvas * Hcal = new TCanvas("Hcal","Hcal",800,600);
    oldHisto->UseCurrentStyle();
    newHisto->UseCurrentStyle();
    oldHisto->SetLineColor(45);
    newHisto->SetLineColor(47); 
    oldHisto->Draw();
    newHisto->Draw("same");
    TString name = oldHisto->GetTitle(); 
    name +=  ".gif" ;
    Hcal->Print(name);
  }
  myoldProfile = oldHisto;
  mynewProfile = newHisto;
 

  Double_t mypv = myoldProfile->Chi2Test(mynewProfile,"OU");
  std::strstream buf;
  std::string value;
  buf<<"PV="<<mypv<<std::endl;
  buf>>value;
  
  //  myte->DrawTextNDC(0.2,0.7, value.c_str());

  std::cout << "[OVAL] " << myoldProfile->GetName() << " PV = " << mypv << std::endl;
  return;

}
