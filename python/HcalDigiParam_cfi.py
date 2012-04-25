import FWCore.ParameterSet.Config as cms

hcalDigiAnalyzer = cms.EDAnalyzer("HcalDigiTester",
    digiLabel = cms.InputTag("mix", "simHcalUnsuppressedDigis"),
    zside = cms.untracked.string('*'),
    outputFile = cms.untracked.string(''),
    hcalselector = cms.untracked.string('HB')
)



