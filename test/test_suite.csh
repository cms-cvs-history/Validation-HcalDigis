#!/bin/csh

    eval `scramv1 ru -csh`
    SealPluginRefresh
        
    rm *.xml*
    if ( -e outputDigisHB.log ) rm outputDigisHB.log
    if ( -e outputDigisHB.log ) rm outputDigisHE.log
    if ( -e outputDigisHB.log ) rm outputDigisHF.log
    if ( -e outputDigisHB.log ) rm outputDigisHO.log
    if ( -e outputDigis_noise.log ) rm outputDigis_noise.log

    cmsRun --parameter-set HBDigiTester.cfg >& outputDigisHB.log
    cmsRun --parameter-set HEDigiTester.cfg >& outputDigisHE.log
    cmsRun --parameter-set HFDigiTester.cfg >& outputDigisHF.log
    cmsRun --parameter-set HODigiTester.cfg >& outputDigisHO.log
    cmsRun --parameter-set noiseDigiTester.cfg >& outputDigis_noise.log
  
    root -b -q HcalOval.C\(\"HB\"\)
    root -b -q HcalOval.C\(\"HE\"\)
    root -b -q HcalOval.C\(\"HF\"\)
    root -b -q HcalOval.C\(\"HO\"\)
    root -b -q HcalOval.C\(\"_noise\"\)


