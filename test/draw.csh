#!/bin/csh

    eval `scramv1 ru -csh`
    SealPluginRefresh
        

    root -b -q HcalOval.C\(\"HB\",\"gif\"\)
    root -b -q HcalOval.C\(\"HE\",\"gif\"\)
    root -b -q HcalOval.C\(\"HF\",\"gif\"\)
    root -b -q HcalOval.C\(\"HO\",\"gif\"\)
    root -b -q HcalOval.C\(\"_noise\",\"gif\"\)


