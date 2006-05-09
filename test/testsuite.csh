#!/bin/csh

    eval `scramv1 ru -csh`
    rm *.log *.xml
    cmsRun --parameter-set HBDigiTester.cfg >& outputHB.log
    cmsRun --parameter-set HEDigiTester.cfg >& outputHE.log
    cmsRun --parameter-set HFDigiTester.cfg >& outputHF.log
    cmsRun --parameter-set HODigiTester.cfg >& outputHO.log

  
    root -b -q hcaloval.C\(\"HB\"\)
    root -b -q hcaloval.C\(\"HE\"\)
    root -b -q hcaloval.C\(\"HF\"\)
    root -b -q hcaloval.C\(\"HO\"\)

end

