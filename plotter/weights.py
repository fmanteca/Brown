#!/usr/bin/python

# targetlumi = 36814. # 1/pb  https://hypernews.cern.ch/HyperNews/CMS/get/luminosity/662.html   
targetlumi = 35867. # 1/pb  https://mail.google.com/mail/u/0/#label/eDRAWER%2FCERN-HyperNews/15a2f9a2bd29c798 https://hypernews.cern.ch/HyperNews/CMS/get/physics-announcements/4495.html   

BR={}
BR['BW'] = 0.5
BR['TZ'] = 0.25
BR['TH'] = 0.25
BR['TTBWBW'] = BR['BW']*BR['BW']
BR['TTTHBW'] = 2*BR['TH']*BR['BW']
BR['TTTZBW'] = 2*BR['TZ']*BR['BW']
BR['TTTZTZ'] = BR['TZ']*BR['TZ']
BR['TTTZTH'] = 2*BR['TZ']*BR['TH']
BR['TTTHTH'] = BR['TH']*BR['TH']

# Number of processed MC events (before selections)
nRun={}

# nRun['DY50'] = 1.95549e+07 # DYJetsToLL_M-50_TuneCUETHS1_13TeV-madgraphMLM-herwigpp - from WeightAnalyzer
# nRun['DY50'] = 8.17811e+07 # from 1.22055e+08 DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8  - from WeightAnalyzer
nRun['DY50'] = 1.45405e+08 # DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_combined  - from WeightAnalyzer
# 
# nRun['DY50'] = 96658943. # madgraph - ext2 - from DAS https://cmsweb.cern.ch/das/request?input=dataset%3D%2FDYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8%2FRunIISummer16MiniAODv2-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext2-v1%2FMINIAODSIM&instance=prod%2Fglobal

nRun['DYMG100'] = 10607207.
nRun['DYMG200'] = 9653731.
nRun['DYMG400'] = 10008776.
nRun['DYMG600'] = 8292957.
nRun['DYMG800'] = 2668730.
nRun['DYMG1200']= 596079.
nRun['DYMG2500']= 399492.

nRun['DY10to50'] = 29386500. # from 40381400. # calculated using WeightAnalyzer.
#nRun['DY50'] = 19403300. # from 28968300. # calculated using WeightAnalyzer. 
# nRun['DY50'] = 16912500. # from 25249500. # calculated using WeightAnalyzer few jobs failed!.

nRun['WJets'] = 16183300. # from 23662100. # calculated using WeightAnalyzer.

nRun['TTJetsPH'] = 155119000. # calculated using WeightAnalyzer.
# numbers not updated to 80x ! - start
nRun['TTJets'] = 14188545. # from 42784971
nRun['TTJetsPH0to700inc'] = nRun['TTJetsPH']
nRun['TTJetsPH700to1000inc'] = nRun['TTJetsPH']*0.0921 + 3877762. #filtering efficiency coeff.
nRun['TTJetsPH1000toINFinc'] = nRun['TTJetsPH']*0.02474 + 2360497. #filtering efficiency coeff.
nRun['TTJetsPH700mtt'] = nRun['TTJetsPH']*0.0921 + 3877762.
nRun['TTJetsPH1000mtt'] = nRun['TTJetsPH']*0.02474 + 2360497.
# numbers not updated to 80x ! - end

nRun['WW'] = 6987120. # mg inclusive calculated using WeightAnalyzer.
nRun['WZ'] = 1993200. #WZTo3LNu # calculated using WeightAnalyzer.
nRun['WZinc'] = 3.79256e+06 #WZ mg inclusive # calculated using WeightAnalyzer.
nRun['ZZ'] = 6669990. #ZZTo4L # calculated using WeightAnalyzer.
nRun['ZZinc'] = 1.9881e+06 #ZZ mg inclusive # calculated using WeightAnalyzer.
nRun['WWW'] = 210538. #out of 240000 - # calculated using WeightAnalyzer. 
nRun['WWZ'] = 221468. #out of 250000 - # calculated using WeightAnalyzer.	
nRun['WZZ'] = 216366. #out of 246800 - # calculated using WeightAnalyzer.  
nRun['ZZZ'] = 213197. #out of 249237 - # calculated using WeightAnalyzer.	
nRun['TTWl'] = 1603530. #from 3120400 - # calculated using WeightAnalyzer. 
nRun['TTWq'] = 430310 #from 833298 - # calculated using WeightAnalyzer. 
nRun['TTZl'] = 927976. #from 1992440 - # calculated using WeightAnalyzer. 
nRun['TTZq'] = 351164 #from 749400 - # calculated using WeightAnalyzer. 

# numbers not updated to 80x ! - start
nRun['WJetsMG100'] = 27546978. # MG, from DAS
nRun['WJetsMG200'] = 14888384. # MG, from DAS
nRun['WJetsMG400'] = 5469282. # MG, from DAS
nRun['WJetsMG600'] = 14410862. # MG, from DAS
nRun['WJetsMG800'] = 6314257. # MG, from DAS
nRun['WJetsMG1200'] = 6817172. # MG, from DAS
nRun['WJetsMG2500'] = 2254248. # MG, from DAS
nRun['Ts'] = 613384. #from 984400
nRun['Tt'] = 4291728. #from 19904330 (was 29892343 in miniAODv1)
nRun['TtW'] = 995600.
nRun['TbtW'] = 988500.
# numbers not updated to 80x ! - end

nRun['TTM700BWBW'] = 798600.0*0.333*0.333 #number not updated

nRun['TTM800BWBW'] = 795000.0*0.333*0.333
nRun['TTM900BWBW'] = 831200.0*0.333*0.333
nRun['TTM1000BWBW'] = 829600.0*0.333*0.333
nRun['TTM1100BWBW'] = 832800.0*0.333*0.333
nRun['TTM1200BWBW'] = 832600.0*0.333*0.333
nRun['TTM1300BWBW'] = 831000.0*0.333*0.333
nRun['TTM1400BWBW'] = 832600.0*0.333*0.333
nRun['TTM1500BWBW'] = 832800.0*0.333*0.333
nRun['TTM1600BWBW'] = 832600.0*0.333*0.333
nRun['TTM1700BWBW'] = 797000.0*0.333*0.333
nRun['TTM1800BWBW'] = 833000.0*0.333*0.333

nRun['TTM700THBW'] = 798600.0*0.333*0.333*2 #number not updated

nRun['TTM800THBW'] = 795000.0*0.333*0.333*2
nRun['TTM900THBW'] = 831200.0*0.333*0.333*2
nRun['TTM1000THBW'] = 829600.0*0.333*0.333*2
nRun['TTM1100THBW'] = 832800.0*0.333*0.333*2
nRun['TTM1200THBW'] = 832600.0*0.333*0.333*2
nRun['TTM1300THBW'] = 831000.0*0.333*0.333*2
nRun['TTM1400THBW'] = 832600.0*0.333*0.333*2
nRun['TTM1500THBW'] = 832800.0*0.333*0.333*2
nRun['TTM1600THBW'] = 832600.0*0.333*0.333*2
nRun['TTM1700THBW'] = 797000.0*0.333*0.333*2
nRun['TTM1800THBW'] = 833000.0*0.333*0.333*2

nRun['TTM700TZBW'] = 798600.0*0.333*0.333*2 #number not updated

nRun['TTM800TZBW'] = 795000.0*0.333*0.333*2
nRun['TTM900TZBW'] = 831200.0*0.333*0.333*2
nRun['TTM1000TZBW'] = 829600.0*0.333*0.333*2
nRun['TTM1100TZBW'] = 832800.0*0.333*0.333*2
nRun['TTM1200TZBW'] = 832600.0*0.333*0.333*2
nRun['TTM1300TZBW'] = 831000.0*0.333*0.333*2
nRun['TTM1400TZBW'] = 832600.0*0.333*0.333*2
nRun['TTM1500TZBW'] = 832800.0*0.333*0.333*2
nRun['TTM1600TZBW'] = 832600.0*0.333*0.333*2
nRun['TTM1700TZBW'] = 797000.0*0.333*0.333*2
nRun['TTM1800TZBW'] = 833000.0*0.333*0.333*2

nRun['TTM700TZTZ'] = 798600.0*0.333*0.333 #number not updated

nRun['TTM800TZTZ'] = 795000.0*0.333*0.333
nRun['TTM900TZTZ'] = 831200.0*0.333*0.333
nRun['TTM1000TZTZ'] = 829600.0*0.333*0.333
nRun['TTM1100TZTZ'] = 832800.0*0.333*0.333
nRun['TTM1200TZTZ'] = 832600.0*0.333*0.333
nRun['TTM1300TZTZ'] = 831000.0*0.333*0.333
nRun['TTM1400TZTZ'] = 832600.0*0.333*0.333
nRun['TTM1500TZTZ'] = 832800.0*0.333*0.333
nRun['TTM1600TZTZ'] = 832600.0*0.333*0.333
nRun['TTM1700TZTZ'] = 797000.0*0.333*0.333
nRun['TTM1800TZTZ'] = 833000.0*0.333*0.333

nRun['TTM700TZTH'] = 798600.0*0.333*0.333*2 #number not updated

nRun['TTM800TZTH'] = 795000.0*0.333*0.333*2
nRun['TTM900TZTH'] = 831200.0*0.333*0.333*2
nRun['TTM1000TZTH'] = 829600.0*0.333*0.333*2
nRun['TTM1100TZTH'] = 832800.0*0.333*0.333*2
nRun['TTM1200TZTH'] = 832600.0*0.333*0.333*2
nRun['TTM1300TZTH'] = 831000.0*0.333*0.333*2
nRun['TTM1400TZTH'] = 832600.0*0.333*0.333*2
nRun['TTM1500TZTH'] = 832800.0*0.333*0.333*2
nRun['TTM1600TZTH'] = 832600.0*0.333*0.333*2
nRun['TTM1700TZTH'] = 797000.0*0.333*0.333*2
nRun['TTM1800TZTH'] = 833000.0*0.333*0.333*2

nRun['TTM700THTH'] = 798600.0*0.333*0.333 #number not updated

nRun['TTM800THTH'] = 795000.0*0.333*0.333
nRun['TTM900THTH'] = 831200.0*0.333*0.333
nRun['TTM1000THTH'] = 829600.0*0.333*0.333
nRun['TTM1100THTH'] = 832800.0*0.333*0.333
nRun['TTM1200THTH'] = 832600.0*0.333*0.333
nRun['TTM1300THTH'] = 831000.0*0.333*0.333
nRun['TTM1400THTH'] = 832600.0*0.333*0.333
nRun['TTM1500THTH'] = 832800.0*0.333*0.333
nRun['TTM1600THTH'] = 832600.0*0.333*0.333
nRun['TTM1700THTH'] = 797000.0*0.333*0.333
nRun['TTM1800THTH'] = 833000.0*0.333*0.333

# numbers not updated to 80x ! - start
nRun['QCDht100'] = 81637494.
# numbers not updated to 80x ! - end

nRun['QCDht200'] = 38812676.
nRun['QCDht300'] = 37875602.
nRun['QCDht500'] = 44138665.
nRun['QCDht700'] = 29832311.
nRun['QCDht1000'] = 10335975.
nRun['QCDht1500'] = 7803965.
nRun['QCDht2000'] = 4047532.

# Not sure, but maybe numbers not updated to 80x ! - start
#energy scale samples (Q^2)
nRun['TTJetsPHQ2U'] = 9921174.
nRun['TTJetsPHQ2D'] = 9860774.
nRun['TtWQ2U'] = 497600.
nRun['TtWQ2D'] = 499200.
nRun['TbtWQ2U'] = 500000.
nRun['TbtWQ2D'] = 497600.
# Not sure, but maybe numbers not updated to 80x ! - end

# Cross sections for MC samples (in pb)
xsec={}
xsec['DY10to50'] = 18610 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
# xsec['DY50'] = 6025.2 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['DY50'] = 5765.4 #1921.8*3 +-0.6*3 (integration err) +- 33.2*3 pb (pdf+alpha_s err) : https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns#DY_Z 

xsec['DYMG100'] = 147.4*1.23 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['DYMG200'] = 40.99*1.23 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['DYMG400'] = 5.678*1.23 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['DYMG600'] = 1.367*1.23 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['DYMG800'] = 0.6304*1.23 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['DYMG1200'] = 0.1514*1.23 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['DYMG2500'] = 0.003565*1.23 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns

xsec['TTJets'] = 831.76
xsec['WJets'] = 61526.7
xsec['TTJetsPH'] = 831.76 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['TTJetsPH0to700inc'] = 831.76
xsec['TTJetsPH700to1000inc'] = 831.76*0.0921 #(xsec*filtering coeff.)
xsec['TTJetsPH1000toINFinc'] = 831.76*0.02474 #(xsec*filtering coeff.)
xsec['TTJetsPH700mtt'] = 831.76*0.0921 #(xsec*filtering coeff.)
xsec['TTJetsPH1000mtt'] = 831.76*0.02474 #(xsec*filtering coeff.)
xsec['WJetsMG100'] = 1345.*1.21 # (1.21 = k-factor )# https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['WJetsMG200'] = 359.7*1.21 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['WJetsMG400'] = 48.91*1.21 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['WJetsMG600'] = 12.05*1.21 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['WJetsMG800'] = 5.501*1.21 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['WJetsMG1200'] = 1.329*1.21 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns
xsec['WJetsMG2500'] = 0.03216*1.21 # https://twiki.cern.ch/twiki/bin/view/CMS/SummaryTable1G25ns 
xsec['WW'] = 118.7 # https://twiki.cern.ch/twiki/bin/viewauth/CMS/StandardModelCrossSectionsat13TeVInclusive
xsec['WZinc'] = 47.13 # https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Diboson
xsec['WZ'] = 4.4297 # WZTo1L3Nu https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Diboson
xsec['ZZinc'] = 16.523 # https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Diboson
xsec['ZZ'] = 1.256 # ZZTo4: https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Diboson
xsec['WWW'] = 0.2086 # from McM Generator Parameters - WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8 but also https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Triboson
xsec['WWZ'] = 0.1651 #cs = 0.1651 pb at NLO, frac_negW = 0.0571 (from CMS AN-2015/148) but also https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Triboson
xsec['WZZ'] = 0.05565 #cs = 0.05565 pb at NLO, frac_negW = 0.0617 (from CMS AN-2015/148) but also https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Triboson
xsec['ZZZ'] = 0.01398 #cs = 0.01398 pb at NLO, frac_negW = 0.0723 (from CMS AN-2015/148) but also https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#Triboson
xsec['TTZl'] = 0.2529 # from McM but also https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#TT_X
xsec['TTZq'] = 0.5297 # from McM but also https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#TT_X
xsec['TTWl'] = 0.2043 # from McM but also https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#TT_X
xsec['TTWq'] = 0.4062 # from McM but also https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#TT_X
xsec['Tt'] = 216.99/3 #(1/3 was suggested by Thomas Peiffer to account for the leptonic branching ratio)# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SingleTopSigma
xsec['Ts'] = 11.36/3 #(1/3 was suggested by Thomas Peiffer to account for the leptonic branching ratio)# https://twiki.cern.ch/twiki/bin/viewauth/CMS/SingleTopSigma
xsec['TtW'] = 35.6 # https://twiki.cern.ch/twiki/bin/viewauth/CMS/SingleTopSigma
xsec['TbtW'] = 35.6 # https://twiki.cern.ch/twiki/bin/viewauth/CMS/SingleTopSigma

xsec['TTM700']   = 0.455 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM800']  = 0.196 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM900']   = 0.0903 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM1000']  = 0.0440 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM1100']  = 0.0224 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM1200'] = 0.0118 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM1300']  = 0.00639 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM1400'] = 0.00354 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM1500']  = 0.00200 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM1600'] = 0.001148 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM1700']  = 0.000666 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo
xsec['TTM1800'] = 0.000391 # from https://twiki.cern.ch/twiki/bin/view/CMS/B2GMonteCarlo


xsec['QCDht100'] = 27990000. # from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD
xsec['QCDht200'] = 1712000. # from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD 
xsec['QCDht300'] = 347700. # from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD 
xsec['QCDht500'] = 32100. # from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD
xsec['QCDht700'] = 6831. # from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD 
xsec['QCDht1000'] = 1207. # from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD
xsec['QCDht1500'] = 119.9 # from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD 
xsec['QCDht2000'] = 25.24 # from https://twiki.cern.ch/twiki/bin/viewauth/CMS/SummaryTable1G25ns#QCD

#energy scale samples (Q^2)
xsec['TTJetsPHQ2U'] = xsec['TTJetsPH']
xsec['TTJetsPHQ2D'] = xsec['TTJetsPH']
xsec['TtWQ2U'] = xsec['TtW']
xsec['TtWQ2D'] = xsec['TtW']
xsec['TbtWQ2U'] = xsec['TbtW']
xsec['TbtWQ2D'] = xsec['TbtW']

# Calculate lumi normalization weights
weight = {}
for sample in sorted(nRun.keys()): 
        if 'BBM' not in sample and 'TTM' not in sample: 
                weight[sample] = (targetlumi*xsec[sample]) / (nRun[sample])
                #print sample, (xsec[sample]) / (nRun[sample])
        else: weight[sample] = (targetlumi*BR[sample[:2]+sample[-4:]]*xsec[sample[:-4]]) / (nRun[sample])


# # Calculate lumi normalization weights
# weight = {}
# weight['DY10to50'] = (targetlumi*xsec['DY10to50']) / (nRun['DY10to50'])
# weight['DY50'] = (targetlumi*xsec['DY50']) / (nRun['DY50'])
# weight['TTJets'] = (targetlumi*xsec['TTJets']) / (nRun['TTJets'])
# weight['WJets'] = (targetlumi*xsec['WJets']) / (nRun['WJets'])
# weight['TTJetsPH'] = (targetlumi*xsec['TTJetsPH']) / (nRun['TTJetsPH'])
# weight['TTJetsPH0to700inc'] = (targetlumi*xsec['TTJetsPH0to700inc']) / (nRun['TTJetsPH0to700inc'])
# weight['TTJetsPH700to1000inc'] = (targetlumi*xsec['TTJetsPH700to1000inc']) / (nRun['TTJetsPH700to1000inc'])
# weight['TTJetsPH1000toINFinc'] = (targetlumi*xsec['TTJetsPH1000toINFinc']) / (nRun['TTJetsPH1000toINFinc'])
# weight['TTJetsPH700mtt'] = (targetlumi*xsec['TTJetsPH700mtt']) / (nRun['TTJetsPH700mtt'])
# weight['TTJetsPH1000mtt'] = (targetlumi*xsec['TTJetsPH1000mtt']) / (nRun['TTJetsPH1000mtt'])
# weight['WJetsMG100'] = (targetlumi*xsec['WJetsMG100']) / (nRun['WJetsMG100'])
# weight['WJetsMG200'] = (targetlumi*xsec['WJetsMG200']) / (nRun['WJetsMG200'])
# weight['WJetsMG400'] = (targetlumi*xsec['WJetsMG400']) / (nRun['WJetsMG400'])
# weight['WJetsMG600'] = (targetlumi*xsec['WJetsMG600']) / (nRun['WJetsMG600'])
# weight['WJetsMG800'] = (targetlumi*xsec['WJetsMG800']) / (nRun['WJetsMG800'])
# weight['WJetsMG1200'] = (targetlumi*xsec['WJetsMG1200']) / (nRun['WJetsMG1200'])
# weight['WJetsMG2500'] = (targetlumi*xsec['WJetsMG2500']) / (nRun['WJetsMG2500'])
# weight['WW'] = (targetlumi*xsec['WW']) / (nRun['WW'])
# weight['WZ'] = (targetlumi*xsec['WZ']) / (nRun['WZ'])
# weight['WZinc'] = (targetlumi*xsec['WZinc']) / (nRun['WZinc'])
# weight['ZZ'] = (targetlumi*xsec['ZZ']) / (nRun['ZZinc'])
# weight['ZZinc'] = (targetlumi*xsec['ZZinc']) / (nRun['ZZ'])
# weight['WWW'] = (targetlumi*xsec['WWW']) / (nRun['WWW'])
# weight['WWZ'] = (targetlumi*xsec['WWZ']) / (nRun['WWZ'])
# weight['WZZ'] = (targetlumi*xsec['WZZ']) / (nRun['WZZ'])
# weight['ZZZ'] = (targetlumi*xsec['ZZZ']) / (nRun['ZZZ'])
# weight['TTWl'] = (targetlumi*xsec['TTWl']) / (nRun['TTWl'])
# weight['TTWq'] = (targetlumi*xsec['TTWq']) / (nRun['TTWq'])
# weight['TTZl'] = (targetlumi*xsec['TTZl']) / (nRun['TTZl'])
# weight['TTZq'] = (targetlumi*xsec['TTZq']) / (nRun['TTZq'])
# weight['Tt'] = (targetlumi*xsec['Tt']) / (nRun['Tt'])
# weight['Ts'] = (targetlumi*xsec['Ts']) / (nRun['Ts'])
# weight['TtW'] = (targetlumi*xsec['TtW']) / (nRun['TtW'])
# weight['TbtW'] = (targetlumi*xsec['TbtW']) / (nRun['TbtW'])
# weight['QCDht100'] = (targetlumi*xsec['QCDht100']) / (nRun['QCDht100'])
# weight['QCDht200'] = (targetlumi*xsec['QCDht200']) / (nRun['QCDht200'])
# weight['QCDht300'] = (targetlumi*xsec['QCDht300']) / (nRun['QCDht300'])
# weight['QCDht500'] = (targetlumi*xsec['QCDht500']) / (nRun['QCDht500'])
# weight['QCDht700'] = (targetlumi*xsec['QCDht700']) / (nRun['QCDht700'])
# weight['QCDht1000'] = (targetlumi*xsec['QCDht1000']) / (nRun['QCDht1000'])
# weight['QCDht1500'] = (targetlumi*xsec['QCDht1500']) / (nRun['QCDht1500'])
# weight['QCDht2000'] = (targetlumi*xsec['QCDht2000']) / (nRun['QCDht2000'])
# weight['TTM700BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM700']) / (nRun['TTM700BWBW'])
# weight['TTM800BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM800']) / (nRun['TTM800BWBW'])
# weight['TTM900BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM900']) / (nRun['TTM900BWBW'])
# weight['TTM1000BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM1000']) / (nRun['TTM1000BWBW'])
# weight['TTM1100BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM1100']) / (nRun['TTM1100BWBW'])
# weight['TTM1200BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM1200']) / (nRun['TTM1200BWBW'])
# weight['TTM1300BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM1300']) / (nRun['TTM1300BWBW'])
# weight['TTM1400BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM1400']) / (nRun['TTM1400BWBW'])
# weight['TTM1500BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM1500']) / (nRun['TTM1500BWBW'])
# weight['TTM1600BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM1600']) / (nRun['TTM1600BWBW'])
# weight['TTM1700BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM1700']) / (nRun['TTM1700BWBW'])
# weight['TTM1800BWBW'] = (targetlumi*BR['TTBWBW']*xsec['TTM1800']) / (nRun['TTM1800BWBW'])
# weight['TTM700THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM700']) / (nRun['TTM700THBW'])
# weight['TTM800THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM800']) / (nRun['TTM800THBW'])
# weight['TTM900THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM900']) / (nRun['TTM900THBW'])
# weight['TTM1000THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM1000']) / (nRun['TTM1000THBW'])
# weight['TTM1100THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM1100']) / (nRun['TTM1100THBW'])
# weight['TTM1200THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM1200']) / (nRun['TTM1200THBW'])
# weight['TTM1300THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM1300']) / (nRun['TTM1300THBW'])
# weight['TTM1400THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM1400']) / (nRun['TTM1400THBW'])
# weight['TTM1500THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM1500']) / (nRun['TTM1500THBW'])
# weight['TTM1600THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM1600']) / (nRun['TTM1600THBW'])
# weight['TTM1700THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM1700']) / (nRun['TTM1700THBW'])
# weight['TTM1800THBW'] = (targetlumi*BR['TTTHBW']*xsec['TTM1800']) / (nRun['TTM1800THBW'])
# weight['TTM700TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM700']) / (nRun['TTM700TZBW'])
# weight['TTM800TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM800']) / (nRun['TTM800TZBW'])
# weight['TTM900TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM900']) / (nRun['TTM900TZBW'])
# weight['TTM1000TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM1000']) / (nRun['TTM1000TZBW'])
# weight['TTM1100TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM1100']) / (nRun['TTM1100TZBW'])
# weight['TTM1200TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM1200']) / (nRun['TTM1200TZBW'])
# weight['TTM1300TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM1300']) / (nRun['TTM1300TZBW'])
# weight['TTM1400TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM1400']) / (nRun['TTM1400TZBW'])
# weight['TTM1500TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM1500']) / (nRun['TTM1500TZBW'])
# weight['TTM1600TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM1600']) / (nRun['TTM1600TZBW'])
# weight['TTM1700TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM1700']) / (nRun['TTM1700TZBW'])
# weight['TTM1800TZBW'] = (targetlumi*BR['TTTZBW']*xsec['TTM1800']) / (nRun['TTM1800TZBW'])
# weight['TTM700TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM700']) / (nRun['TTM700TZTZ'])
# weight['TTM800TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM800']) / (nRun['TTM800TZTZ'])
# weight['TTM900TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM900']) / (nRun['TTM900TZTZ'])
# weight['TTM1000TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM1000']) / (nRun['TTM1000TZTZ'])
# weight['TTM1100TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM1100']) / (nRun['TTM1100TZTZ'])
# weight['TTM1200TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM1200']) / (nRun['TTM1200TZTZ'])
# weight['TTM1300TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM1300']) / (nRun['TTM1300TZTZ'])
# weight['TTM1400TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM1400']) / (nRun['TTM1400TZTZ'])
# weight['TTM1500TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM1500']) / (nRun['TTM1500TZTZ'])
# weight['TTM1600TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM1600']) / (nRun['TTM1600TZTZ'])
# weight['TTM1700TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM1700']) / (nRun['TTM1700TZTZ'])
# weight['TTM1800TZTZ'] = (targetlumi*BR['TTTZTZ']*xsec['TTM1800']) / (nRun['TTM1800TZTZ'])
# weight['TTM700TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM700']) / (nRun['TTM700TZTH'])
# weight['TTM800TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM800']) / (nRun['TTM800TZTH'])
# weight['TTM900TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM900']) / (nRun['TTM900TZTH'])
# weight['TTM1000TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM1000']) / (nRun['TTM1000TZTH'])
# weight['TTM1100TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM1100']) / (nRun['TTM1100TZTH'])
# weight['TTM1200TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM1200']) / (nRun['TTM1200TZTH'])
# weight['TTM1300TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM1300']) / (nRun['TTM1300TZTH'])
# weight['TTM1400TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM1400']) / (nRun['TTM1400TZTH'])
# weight['TTM1500TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM1500']) / (nRun['TTM1500TZTH'])
# weight['TTM1600TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM1600']) / (nRun['TTM1600TZTH'])
# weight['TTM1700TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM1700']) / (nRun['TTM1700TZTH'])
# weight['TTM1800TZTH'] = (targetlumi*BR['TTTZTH']*xsec['TTM1800']) / (nRun['TTM1800TZTH'])
# weight['TTM700THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM700']) / (nRun['TTM700THTH'])
# weight['TTM800THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM800']) / (nRun['TTM800THTH'])
# weight['TTM900THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM900']) / (nRun['TTM900THTH'])
# weight['TTM1000THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM1000']) / (nRun['TTM1000THTH'])
# weight['TTM1100THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM1100']) / (nRun['TTM1100THTH'])
# weight['TTM1200THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM1200']) / (nRun['TTM1200THTH'])
# weight['TTM1300THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM1300']) / (nRun['TTM1300THTH'])
# weight['TTM1400THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM1400']) / (nRun['TTM1400THTH'])
# weight['TTM1500THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM1500']) / (nRun['TTM1500THTH'])
# weight['TTM1600THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM1600']) / (nRun['TTM1600THTH'])
# weight['TTM1700THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM1700']) / (nRun['TTM1700THTH'])
# weight['TTM1800THTH'] = (targetlumi*BR['TTTHTH']*xsec['TTM1800']) / (nRun['TTM1800THTH'])
# 
# #energy scale samples (Q^2)
# weight['TTJetsPHQ2U'] = (targetlumi*xsec['TTJetsPHQ2U']) / (nRun['TTJetsPHQ2U'])
# weight['TTJetsPHQ2D'] = (targetlumi*xsec['TTJetsPHQ2D']) / (nRun['TTJetsPHQ2D'])
# weight['TtWQ2U'] = (targetlumi*xsec['TtWQ2U']) / (nRun['TtWQ2U'])
# weight['TtWQ2D'] = (targetlumi*xsec['TtWQ2D']) / (nRun['TtWQ2D'])
# weight['TbtWQ2U'] = (targetlumi*xsec['TbtWQ2U']) / (nRun['TbtWQ2U'])
# weight['TbtWQ2D'] = (targetlumi*xsec['TbtWQ2D']) / (nRun['TbtWQ2D'])
# 
# 
