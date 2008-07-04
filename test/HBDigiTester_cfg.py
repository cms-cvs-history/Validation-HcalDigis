import FWCore.ParameterSet.Config as cms

process = cms.Process("HCALDIGISVALIDATION")
process.load("Validation.HcalDigis.HcalDigiTester_cfi")

process.PoolSource.fileNames = ['file:/afs/cern.ch/cms/data/CMSSW/Validation/HcalDigis/data/2_1_0/simhits_pi50_etaphi44.root']

process.hcalDigiAnalyzer.outputFile = 'HcalDigisValidationHB.root'
process.hcalDigiAnalyzer.hcalselector = 'HB'


