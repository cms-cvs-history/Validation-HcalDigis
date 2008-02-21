// Commands executed in a GLOBAL scope, e.g. created hitograms aren't erased...
{

   TCanvas *myc = new TCanvas("myc","",800,600);
      
   TFile f1("~/Validation/173_on_simhits_173/CaloTowersValidationHO.root");
   TFile f2("~/Validation/180_pre5_on_simhits_180_pre5/CaloTowersValidationHO.root");

   
   // service variables
   //
   const int Nhist1 = 3;
   const int Nhist2 = 1;
   TH1F* f1_hist1[Nhist1];
   TH1F* f2_hist1[Nhist1];
   TH2F* f1_hist2[Nhist2];
   TH2F* f2_hist2[Nhist2];

   char *label1[Nhist1];
   char *label2[Nhist2];

   label1[0] = &"HcalDigiTask_signal_amplitude_depth4_HO.gif";
   label1[1] = &"HcalDigiTask_ratio_amplitude_vs_simhits_depth4_HO.gif";
   label1[2] = &"HcalDigiTask_number_of_amplitudes_above_10fC_HO.gif";

   label2[0] = &"HcalDigiTask_amplitude_vs_simhits_depth4_HO.gif";

   f1->cd("DQMData/HcalDigiTask");
   gDirectory->pwd();
   f1_hist1[0] = HcalDigiTask_signal_amplitude_depth4_HO;
   f1_hist1[1] = HcalDigiTask_ratio_amplitude_vs_simhits_depth4_HO;
   f1_hist1[2] = HcalDigiTask_number_of_amplitudes_above_10fC_HO;

   f1_hist2[0] = HcalDigiTask_amplitude_vs_simhits_depth4_HO;


   f2->cd("DQMData/HcalDigiTask");
   gDirectory->pwd();
   f2_hist1[0] = HcalDigiTask_signal_amplitude_depth4_HO;
   f2_hist1[1] = HcalDigiTask_ratio_amplitude_vs_simhits_depth4_HO;
   f2_hist1[2] = HcalDigiTask_number_of_amplitudes_above_10fC_HO;

   f2_hist2[0] = HcalDigiTask_amplitude_vs_simhits_depth4_HO;


   f1_hist1[0]->GetXaxis()->SetTitle("HO signal amplitude (fC)");
   f1_hist1[1]->GetXaxis()->SetTitle("HO ratio amplitute (fC) to SimHits (GeV)");
   f1_hist1[2]->GetXaxis()->SetTitle("HO N(ampl) > 10 fC");

   f1_hist2[0]->GetXaxis()->SetTitle("HO signal amplitude (fC) vs SimHits (pe)");

   f1_hist2[0]->GetXaxis()->SetRangeUser(0.,0.12);

   // f1_hist[0]->SetMaximum(600.);

   // f1_hist[2]->GetXaxis()->SetRangeUser(0.,1200.);
   // f1_hist[7]->GetXaxis()->SetRangeUser(0.,160.);
   // hist1->GetXaxis()->SetNdivisions(-21);
   // hist1->GetYaxis()->SetNdivisions(-1003);


   //  1D-histo

   for (int i = 0; i < Nhist1; i++){


    f1_hist1[i]->SetStats(kFALSE);   
    f2_hist1[i]->SetStats(kFALSE); 
    
    f1_hist1[i]->SetTitle("");
    f2_hist1[i]->SetTitle("");

    f1_hist1[i]->SetLineWidth(2); 
    f2_hist1[i]->SetLineWidth(3); 
    
    // diffferent histo colors and styles
    f1_hist1[i]->SetLineColor(41);
    f1_hist1[i]->SetLineStyle(1); 
    
    f2_hist1[i]->SetLineColor(42);
    f2_hist1[i]->SetLineStyle(2);  
    
    
    TLegend *leg = new TLegend(0.68, 0.82, 0.98, 0.97, "","brNDC");
    
    leg->SetBorderSize(2);
    //  leg->SetFillColor(51); // see new color definition above
    leg->SetFillStyle(1001); //
    leg->AddEntry(f1_hist1[i],"CMSSW_170","l");
    leg->AddEntry(f2_hist1[i],"CMSSW_180","l");
    
    if(i == 0 || i == 2) gPad->SetLogy(1);
    else  gPad->SetLogy(0);
    
    f1_hist1[i]->Draw("hist");   
     f2_hist1[i]->Draw("hist same");   
     
     leg->Draw();   
     
     myc->SaveAs(label1[i]);
   }     
   

   //  2D-histo
  for (int i = 0; i < Nhist2; i++){
    gPad->SetLogy(0);

    f1_hist2[i]->SetStats(kFALSE);   
    f2_hist2[i]->SetStats(kFALSE); 
    
    f1_hist2[i]->SetTitle("");
    f2_hist2[i]->SetTitle("");

    f1_hist2[i]->SetLineColor(2);
    f1_hist2[i]->SetLineWidth(2); 
    f1_hist2[i]->SetMarkerColor(41);
    f1_hist2[i]->SetMarkerStyle(20);
    f1_hist2[i]->SetMarkerSize(0.5);  

    f2_hist2[i]->SetLineColor(3);
    f2_hist2[i]->SetLineWidth(3); 
    f2_hist2[i]->SetMarkerColor(42);
    f2_hist2[i]->SetMarkerStyle(22);
    f2_hist2[i]->SetMarkerSize(0.5);  

    f1_hist2[i]->Draw("P");   
    f2_hist2[i]->Draw("PSAME");   

    TLegend *leg = new TLegend(0.28, 0.82, 0.58, 0.97, "","brNDC");    
     leg->SetBorderSize(2);
     leg->SetFillStyle(1001); 
     leg->AddEntry(f1_hist2[i],"CMSSW_170","pl");
     leg->AddEntry(f2_hist2[i],"CMSSW_180","pl");

     leg->Draw();   
     
     myc->SaveAs(label2[i]);

  }

   // close ROOT files
   //
   f1.Close() ;  
   f2.Close() ;
   
   return ;  
     
}
