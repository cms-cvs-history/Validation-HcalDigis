#!/bin/csh

    eval `scramv1 ru -csh`
    SealPluginRefresh
        

    root  -q hcaloval.C\(\"HB\",\"gif\"\)
    root  -q hcaloval.C\(\"HE\",\"gif\"\)
    root  -q hcaloval.C\(\"HF\",\"gif\"\)
    root  -q hcaloval.C\(\"HO\",\"gif\"\)
    root  -q hcaloval.C\(\"_noise\",\"gif\"\)


