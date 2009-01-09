import FWCore.ParameterSet.Config as cms

process = cms.Process("HCALDIGISVALIDATION")
process.load("Validation.HcalDigis.HcalDigiTester_cfi")
process.load("Configuration.StandardSequences.GeometryHCAL_cff")

process.PoolSource.fileNames = ['file:/afs/cern.ch/cms/data/CMSSW/Validation/HcalDigis/data/2_1_0/simhits_pi50_etaphi344.root']

process.hcalDigiAnalyzer.outputFile = 'HcalDigisValidationHF.root'
process.hcalDigiAnalyzer.hcalselector = 'HF'


