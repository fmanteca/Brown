#!/usr/bin/python

samples = {


'TTM700BWBW':'TprimeTprime_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM800BWBW':'TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM900BWBW':'TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM1000BWBW':'TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM1100BWBW':'TprimeTprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM1200BWBW':'TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM1300BWBW':'TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM1400BWBW':'TprimeTprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM1500BWBW':'TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM1600BWBW':'TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM1700BWBW':'TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',
'TTM1800BWBW':'TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8_BWBW',

'TTM700THBW':'TprimeTprime_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM800THBW':'TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM900THBW':'TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM1000THBW':'TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM1100THBW':'TprimeTprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM1200THBW':'TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM1300THBW':'TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM1400THBW':'TprimeTprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM1500THBW':'TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM1600THBW':'TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM1700THBW':'TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',
'TTM1800THBW':'TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8_THBW',

'TTM700TZBW':'TprimeTprime_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM800TZBW':'TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM900TZBW':'TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM1000TZBW':'TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM1100TZBW':'TprimeTprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM1200TZBW':'TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM1300TZBW':'TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM1400TZBW':'TprimeTprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM1500TZBW':'TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM1600TZBW':'TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM1700TZBW':'TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',
'TTM1800TZBW':'TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8_TZBW',

'TTM700TZTZ':'TprimeTprime_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM800TZTZ':'TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM900TZTZ':'TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM1000TZTZ':'TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM1100TZTZ':'TprimeTprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM1200TZTZ':'TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM1300TZTZ':'TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM1400TZTZ':'TprimeTprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM1500TZTZ':'TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM1600TZTZ':'TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM1700TZTZ':'TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',
'TTM1800TZTZ':'TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTZ',

'TTM700TZTH':'TprimeTprime_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM800TZTH':'TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM900TZTH':'TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM1000TZTH':'TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM1100TZTH':'TprimeTprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM1200TZTH':'TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM1300TZTH':'TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM1400TZTH':'TprimeTprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM1500TZTH':'TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM1600TZTH':'TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM1700TZTH':'TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',
'TTM1800TZTH':'TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8_TZTH',

'TTM700THTH':'TprimeTprime_M-700_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM800THTH':'TprimeTprime_M-800_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM900THTH':'TprimeTprime_M-900_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM1000THTH':'TprimeTprime_M-1000_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM1100THTH':'TprimeTprime_M-1100_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM1200THTH':'TprimeTprime_M-1200_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM1300THTH':'TprimeTprime_M-1300_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM1400THTH':'TprimeTprime_M-1400_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM1500THTH':'TprimeTprime_M-1500_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM1600THTH':'TprimeTprime_M-1600_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM1700THTH':'TprimeTprime_M-1700_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',
'TTM1800THTH':'TprimeTprime_M-1800_TuneCUETP8M1_13TeV-madgraph-pythia8_THTH',

# 'DY10to50': 'DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'DY10to50':'DYJetsToLL_M-10to50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8',
# 'DY50':'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'DY50':'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_combined',
# 'DY50':'DYJetsToLL_M-50_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8',
# 'DY50':DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',

'DYMG100':'DYJetsToLL_M-50_HT-100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'DYMG200':'DYJetsToLL_M-50_HT-200to400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'DYMG400':'DYJetsToLL_M-50_HT-400to600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'DYMG600':'DYJetsToLL_M-50_HT-600to800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'DYMG800':'DYJetsToLL_M-50_HT-800to1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'DYMG1200':'DYJetsToLL_M-50_HT-1200to2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'DYMG2500':'DYJetsToLL_M-50_HT-2500toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',

'WJetsMG100':'WJetsToLNu_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'WJetsMG200':'WJetsToLNu_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'WJetsMG400':'WJetsToLNu_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'WJetsMG600':'WJetsToLNu_HT-600To800_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'WJetsMG800':'WJetsToLNu_HT-800To1200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'WJetsMG1200':'WJetsToLNu_HT-1200To2500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
'WJetsMG2500':'WJetsToLNu_HT-2500ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',

'WW':'WW_TuneCUETP8M1_13TeV-pythia8',
'WZinc':'WZ_TuneCUETP8M1_13TeV-pythia8',
'WZ':'WZTo3LNu_TuneCUETP8M1_13TeV-powheg-pythia8',
'ZZinc':'ZZ_TuneCUETP8M1_13TeV-pythia8',
'ZZ':'ZZTo4L_13TeV_powheg_pythia8',

'WWW':'WWW_4F_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
'WWZ':'WWZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
'WZZ':'WZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
'ZZZ':'ZZZ_TuneCUETP8M1_13TeV-amcatnlo-pythia8',

'WJets':'WJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8',
# 'WJets':'WJetsToLNu_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',


'TTJetsPH':'TT_TuneCUETP8M2T4_13TeV-powheg-pythia8',
# 'TTJets':'TTJets_TuneCUETP8M1_13TeV-amcatnloFXFX-pythia8',
# 'TTJetsPH':'TT_TuneCUETP8M1_13TeV-powheg-pythia8_highstats',
# 'TTJetsPHQ2U':'TT_TuneCUETP8M1_13TeV-powheg-scaleup-pythia8',
# 'TTJetsPHQ2D':'TT_TuneCUETP8M1_13TeV-powheg-scaledown-pythia8',
# 'TTJetsPH0to700inc':'TT_TuneCUETP8M1_13TeV-powheg-pythia8_highstats_Mtt0to700',
# 'TTJetsPH700to1000inc':'TT_TuneCUETP8M1_13TeV-powheg-pythia8_highstats_Mtt700to1000',
# 'TTJetsPH1000toINFinc':'TT_TuneCUETP8M1_13TeV-powheg-pythia8_highstats_Mtt1000toInf',
# 'TTJetsPH700mtt':'TT_Mtt-700to1000_TuneCUETP8M1_13TeV-powheg-pythia8',
# 'TTJetsPH1000mtt':'TT_Mtt-1000toInf_TuneCUETP8M1_13TeV-powheg-pythia8',

'TTWl':'TTWJetsToLNu_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8',
'TTWq':'TTWJetsToQQ_TuneCUETP8M1_13TeV-amcatnloFXFX-madspin-pythia8',
'TTZl':'TTZToLLNuNu_M-10_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
'TTZq':'TTZToQQ_TuneCUETP8M1_13TeV-amcatnlo-pythia8',

# 'Tt':'ST_t-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1',      #amcnlo t and tbar
# 'TtQ2U':'ST_t-channel_4f_scaleup_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1',
# 'TtQ2D':'ST_t-channel_4f_scaledown_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1',
# 'Ts':'ST_s-channel_4f_leptonDecays_13TeV-amcatnlo-pythia8_TuneCUETP8M1',
# 'TtW':'ST_tW_top_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1',    #pow-pyth t -> tW
# 'TtWQ2U':'ST_tW_top_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1',
# 'TtWQ2D':'ST_tW_top_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1',
# 'TbtW':'ST_tW_antitop_5f_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1',  #pow-pyth tbar -> tW
# 'TbtWQ2U':'ST_tW_antitop_5f_scaleup_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1',
# 'TbtWQ2D':'ST_tW_antitop_5f_scaledown_inclusiveDecays_13TeV-powheg-pythia8_TuneCUETP8M1',

# 'QCDht100':'QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
# 'QCDht200':'QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
# 'QCDht300':'QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
# 'QCDht500':'QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
# 'QCDht700':'QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
# 'QCDht1000':'QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
# 'QCDht1500':'QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
# 'QCDht2000':'QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
}

dilep = ['EE','MM','ME']
dict_dilep = {dilep[0]:'DoubleEG',dilep[1]:'DoubleMuon',dilep[2]:'MuonEG'}
run = ['RRB','RRC','RRD','RRE','RRF','RRG','RRH']
ddbkgCat = ['TTT','TTL','TLT','LTT','TLL','LTL','LLT','LLL']

for run_ in run:
	for dilep_ in dilep:
		samples['Data'+dilep_+run_]=dict_dilep[dilep_]+'_'+run_
		samples['DataDrivenBkg'+dilep_+run_]=dict_dilep[dilep_]+'_'+run_
		for ddbkgCat_ in ddbkgCat:
			samples['DataDrivenBkg'+ddbkgCat_+dilep_+run_]=dict_dilep[dilep_]+'_'+run_
