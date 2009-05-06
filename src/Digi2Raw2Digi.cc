#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "Validation/HcalDigis/interface/Digi2Raw2Digi.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"
#include "DataFormats/HcalDetId/interface/HcalElectronicsId.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDigi/interface/HcalQIESample.h"

#include "DQMServices/Core/interface/DQMStore.h"

#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"
#include "DataFormats/HcalDigi/interface/HFDataFrame.h"
#include "DataFormats/HcalDigi/interface/HODataFrame.h"
#include <vector>
#include <utility>
#include <ostream>
#include <string>
#include <algorithm>
#include <cmath>


// Qunatities of interest in :
// DataFormats/HcalDigi/test/HcalDigiDump.cc - example of Digi dumping...
// DataFormats/HcalDigi/interface/HcalQIESample.h - adc, capid etc.
// DataFormats/HcalDigi/interface/HBHEDataFrame.h -
// zsMarkAndPass, zsUnsuppressed etc.

template<class Digi>

void Digi2Raw2Digi::compare(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  typename edm::Handle<edm::SortedCollection<Digi> > digiCollection1;
  typename edm::SortedCollection<Digi>::const_iterator digiItr1;
  typename edm::Handle<edm::SortedCollection<Digi> > digiCollection2;
  typename edm::SortedCollection<Digi>::const_iterator digiItr2;
  
   
  iEvent.getByLabel (inputTag1_, digiCollection1);
  iEvent.getByLabel (inputTag2_, digiCollection2);

  // CYCLE over first DIGI collection ======================================

  for (digiItr1=digiCollection1->begin();digiItr1!=digiCollection1->end();digiItr1++) {
    
    HcalDetId cell(digiItr1->id()); 
    int depth = cell.depth();
    int iphi  = cell.iphi()-1;
    int ieta  = cell.ieta();
    int sub   = cell.subdet();
    //    if(ieta > 0) ieta--;
    
    //    std::cout << " Cell subdet=" << sub << "  ieta=" << ieta 
    //	      << "  inphi=" << iphi << "  depth=" << depth << std::endl;
	       
    int tsize =  (*digiItr1).size();
    int match = 0;

  // CYCLE over second DIGI collection ======================================
    
    for (digiItr2=digiCollection2->begin();digiItr2!=digiCollection2->end();digiItr2++) {
         
      HcalDetId cell2(digiItr2->id()); 
  
      if( cell == cell2) {
	match = 1;
	for (int i=0; i<tsize; i++) {
	  double adc  =  (*digiItr1)[i].adc();     
	  int capid   =  (*digiItr1)[i].capid();
	  //	  std::cout << std::endl << "     capid1=" << capid 
          //                << " adc1=" << adc 
	  //		    << std::endl;
	  double adc2 =  (*digiItr2)[i].adc();     
	  int capid2  =  (*digiItr2)[i].capid();
	  //	  std::cout << "     capid2=" << capid2 << " adc2=" << adc2 
	  //		    << std::endl;
	  if( capid != capid2 || adc !=  adc2) {
	    std::cout << "===> PROBLEM !!!  subdet=" << sub << "  ieta="
		      << ieta  << "  inphi=" << iphi << "  depth=" << depth
		      << std::endl;
	    std::cout << "     capid1["<< i << "]=" << capid 
		      << " adc1["<< i << "]=" << adc 
		      << "     capid2["<< i << "]=" << capid2 
		      << " adc2["<< i << "]=" << adc2
		      << std::endl;
            break;
	  }


	} // end of DataFrames array
	break; // matched HcalID  is processed,
              //  go to next (primary collection) cell  

      } 

    } // end of cycle over 2d DIGI collection 
    if (!match)
      std::cout << "===> PROBLEM !!!  subdet=" << sub << "  ieta="
		<< ieta  << "  inphi=" << iphi << "  depth=" << depth
                << " HcalID match is not found !!!" 
 		<< std::endl;

  } // end of cycle over 1st DIGI collection    
  
}


Digi2Raw2Digi::Digi2Raw2Digi(const edm::ParameterSet& iConfig)
  : inputTag1_(iConfig.getParameter<edm::InputTag>("digiLabel1")),
    inputTag2_(iConfig.getParameter<edm::InputTag>("digiLabel2"))
{ }


Digi2Raw2Digi::~Digi2Raw2Digi() { }


void Digi2Raw2Digi::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  //  std::cout << "=== HBHE ==================" << std::endl; 
  compare<HBHEDataFrame>(iEvent,iSetup);

  //  std::cout << "=== HO ====================" << std::endl; 
  compare<HODataFrame>(iEvent,iSetup);

  //  std::cout << "=== HF ====================" << std::endl; 
  compare<HFDataFrame>(iEvent,iSetup);  

}

DEFINE_SEAL_MODULE ();
DEFINE_ANOTHER_FWK_MODULE (Digi2Raw2Digi) ;
