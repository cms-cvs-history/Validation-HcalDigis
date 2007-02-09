#include <iostream>
// comparison of digi histograms with reference ones.
//  root -b -q hcaloval.C\(\"HB\"\) - just for PV comparison.
//  root -b -q hcaloval.C\(\"HB\",\"gif\"\) - PV comparison and creation of gif for each histo
//  root -b -q hcaloval.C\(\"HB\",\"ps\"\) - PV comparison and creation of ps file for each subdetector

#include "TFile.h"
#include "TTree.h"
#include "TText.h"
#include "TStyle.h"
#include "TPostScript.h"
#include "TString.h"

class HcalOval
{
public:
  HcalOval(const char* runtype, const char* drawhisto="none",string path2ref = "../data/", string path2data ="");
  ~HcalOval();

  void process(string name, string subdet);
  void runNoise();
  void runStandard();
  void runAll();


private:
  string path2ref;
  string path2data;
  string run;
  string drawhist;
  bool isNoise;
  TFile * rfile;
  TFile * sfile;
  TCanvas * canvas;
  TPostScript * ps;
};


HcalOval::HcalOval(const char* runtype, const char* drawhisto, string path2ref, string path2data)
: run(runtype),
  drawhist(drawhisto),
  isNoise(runtype == "_noise"),
  rfile(0),
  sfile(0),
  canvas(0),
  ps(0)
{
  gROOT->Reset();
  if(drawhist == "ps"){
    canvas = new TCanvas("Hcal","Hcal",0,0,707,500 );
    string figure = "figure";
    figure += run;
    figure += ".ps";
    ps = new TPostScript(figure.c_str()  , -112);
    ps->Range(29.7 , 21.0);
  }


  string rfilename;
  rfilename = path2ref+ "HcalDigisValidation" +run + "_ref.root";
  string sfilename;
  sfilename = path2data + "HcalDigisValidation" +run + ".root";



  delete gROOT->GetListOfFiles()->FindObject(rfilename.c_str());
  delete gROOT->GetListOfFiles()->FindObject(sfilename.c_str());

  // TText* te = new TText();
  // te->SetTextSize(0.1);
  rfile = new TFile(rfilename.c_str());
  sfile = new TFile(sfilename.c_str());
  rfile->cd("DQMData/HcalDigiTask");
  gDirectory->ls();

  sfile->cd("DQMData/HcalDigiTask");
  gDirectory->ls();

  gStyle->SetOptStat("n");

  gROOT->ProcessLine(".x HistoCompare.C");

  runAll();
}

HcalOval::~HcalOval()
{
  if (drawhist == "ps") ps->Close();
}


void HcalOval::process(string histname, string subdet)
{
  TH1 * oldHist;
  TH1 * newHist;
  string tname = histname + "_"+ subdet + ";1";
  std::cout << "PROCESS " << tname << std::endl;

  rfile->GetObject(tname.c_str(), oldHist);
  sfile->GetObject(tname.c_str(), newHist); 
  HistoCompare comp;
  comp.PVCompute(oldHist, newHist, drawhist.c_str(),"");
  if (drawhist == "ps") 
  { 
    canvas->Update(); 
    ps->NewPage();
  }
}


void HcalOval::runNoise()
{
  string histname = "DQMData/HcalDigiTask/HcalDigiTask_sum_over_digis_fC";
  process(histname, "noise_HB");
  process(histname, "noise_HE");
  process(histname, "noise_HF");
  process(histname, "noise_HO");
  histname = "DQMData/HcalDigiTask/HcalDigiTask_pedestal";
  process(histname, "HB");
  process(histname, "HE");
  process(histname, "HF");
  process(histname, "HO");

}


void HcalOval::runStandard()
{
  string etaHist("DQMData/HcalDigiTask/HcalDigiTask_eta_of_digis");
  string phiHist = "DQMData/HcalDigiTask/HcalDigiTask_phi_of_digis";
  string ndigiHist =  "DQMData/HcalDigiTask/HcalDigiTask_number_of_digis";
  process(etaHist, run);
  process(phiHist, run);
  process(ndigiHist, run);
  process("DQMData/HcalDigiTask/HcalDigiTask_bin_5_frac", run);
  process("DQMData/HcalDigiTask/HcalDigiTask_bin_6_7_frac", run);
  process("DQMData/HcalDigiTask/HcalDigiTask_ratio_energy_digis_vs_simhits", run);
  process("DQMData/HcalDigiTask/HcalDigiTask_sum_over_digis_fC", run);
  process("DQMData/HcalDigiTask/HcalDigiTask_energy_digis_vs_simhits_profile",run);

}




 

void HcalOval::runAll()
{

    if (run != "_noise") runStandard();
    if (run == "_noise") runNoise(); 
}


