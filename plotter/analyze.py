#!/usr/bin/python

import ROOT as R
from array import array
from weights import *

"""
--This function will make kinematic plots for a given distribution for electron, muon channels and their combination
--Check the cuts below to make sure those are the desired full set of cuts!
--The applied weights are defined in "weights.py". Also, the additional weights (SFs, 
negative MC weights, ets) applied below should be checked!
"""

debugANALYZE=True
lumiStr = str(targetlumi/1000).replace('.','p') # 1/fb

def analyze(tTree,process,cutList,doAllSys,discriminantName,discriminantDetails,category,cutType):
	if(debugANALYZE):print "*****"*20
	if(debugANALYZE):print "*****"*20
	if(debugANALYZE):print "DISTRIBUTION:", discriminantName
	if(debugANALYZE):print "            -name in ljmet trees:", discriminantDetails[0]
	if(debugANALYZE):print "            -x-axis label is set to:", discriminantDetails[2]
	if(debugANALYZE):print "            -using the binning as:", discriminantDetails[1]
	discriminantLJMETName=discriminantDetails[0]
	xbins=array('d', discriminantDetails[1])
	xAxisLabel=discriminantDetails[2]
	
	wtagvar = 'NJetsWtagged_JMR'
	if 'Data' in process: wtagvar = 'NJetsWtagged'

	if(debugANALYZE):print "/////"*5
	if(debugANALYZE):print "PROCESSING: ", process, " CATEGORY: ", category
	if(debugANALYZE):print "/////"*5
	cut = '1'
	cut += ' && (AllLeptonPt_PtOrdered[0] >= '+str(cutList['lep1PtCut'])+')'
	cut += ' && (AllLeptonPt_PtOrdered[1] >= '+str(cutList['lep1PtCut'])+')'
	cut += ' && (AllLeptonPt_PtOrdered[2] >= '+str(cutList['lep1PtCut'])+')'

	cut += ' && (corr_met_singleLepCalc >= '+str(cutList['metCut'])+')'

	if ('CR' in cutType and cutType!='CR1CR2'): cut += ' && (NJets_singleLepCalc == '+str(cutList['njetsCut'])+')'
	elif(cutType=='CR1CR2'): cut += ' && (NJets_singleLepCalc <= '+str(cutList['njetsCut'])+' && NJets_singleLepCalc >= 1 )'
	else : cut += ' && (NJets_singleLepCalc >= '+str(cutList['njetsCut'])+')'

	cut += ' && (NJetsBTagwithSF_singleLepCalc >= '+str(cutList['nbjetsCut'])+')'

	if ('Data' in process and 'Bkg' not in process): 
		if 'RRH' in process: #for runH use DZ version of HLT
			if cutList['isPassTrig_dilep']==1:cut += ' && DataPastTrigger_dilepDZ4runH == 1'
			if cutList['isPassTrilepton']==1 :  cut += ' && isPassTrilepton == 1'
		else:
			if cutList['isPassTrig']==1:        cut += ' && DataPastTrigger == 1'
			if cutList['isPassTrig_dilep']==1:  cut += ' && DataPastTrigger_dilep == 1'
			if cutList['isPassTrig_dilep_anth']==1:cut += ' && DataPastTrigger_dilep_anth == 1'
			if cutList['isPassTrig_trilep']==1: cut += ' && DataPastTrigger_trilep == 1'
			if cutList['isPassTrilepton']==1 :  cut += ' && isPassTrilepton == 1'
	elif ('DataDrivenBkg' in process): 
		if 'RRH' in process: #for runH use DZ version of HLT
			if cutList['isPassTrig_dilep']==1:cut += ' && DataPastTrigger_dilepDZ4runH == 1'
		else:
			if cutList['isPassTrig']==1:        cut += ' && DataPastTrigger == 1'
			if cutList['isPassTrig_dilep']==1:  cut += ' && DataPastTrigger_dilep == 1'
			if cutList['isPassTrig_dilep_anth']==1:cut += ' && DataPastTrigger_dilep_anth == 1'
			if cutList['isPassTrig_trilep']==1: cut += ' && DataPastTrigger_trilep == 1'
	elif ('Data' not in process): 
		if cutList['isPassTrig']==1:        cut += ' && MCPastTrigger == 1'
		if cutList['isPassTrig_dilep']==1:  cut += ' && MCPastTrigger_dilep == 1'
		if cutList['isPassTrig_dilep_anth']==1:cut += ' && MCPastTrigger_dilep_anth == 1'
		if cutList['isPassTrig_trilep']==1: cut += ' && MCPastTrigger_trilep == 1'
		if cutList['isPassTrilepton']==1 :  cut += ' && isPassTrilepton == 1'	
 	cut += ' && (AK4HTpMETpLepPt >= '+str(cutList['stCut'])+')'

	if ('FR' in cutType): cut += ' && AllLeptonCount_PtOrdered == 3' #require exactly 3 leptons
#  	cut += ' && AllLeptonCount_PtOrdered > 3' #require more than 3 leptons

	### cut only events where there is a OS lepton pair and that it has 0<MllOS<cutvalue 
# 	cut += ' && ( (MllOS_allComb[0] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[0] < 0)' 
# 	cut += ' && (MllOS_allComb[1] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[1] < 0)' 
# 	cut += ' && (MllOS_allComb[2] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[2] < 0) )' 

	### cut only events where there is a OS lepton pair and that it has 0<MllOS<cutvalue - to account for up to 6 leptons! - only works with step1 starting Mar 1, 2017 !!
	cut += ' && ( (MllOS_allComb[0] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[0] < 0)' 
	cut += ' && (MllOS_allComb[1] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[1] < 0)' 
	cut += ' && (MllOS_allComb[2] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[2] < 0)' 
	cut += ' && (MllOS_allComb[3] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[3] < 0)' 
	cut += ' && (MllOS_allComb[4] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[4] < 0)' 
	cut += ' && (MllOS_allComb[5] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[5] < 0)' 
	cut += ' && (MllOS_allComb[6] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[6] < 0)' 
	cut += ' && (MllOS_allComb[7] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[7] < 0)' 
	cut += ' && (MllOS_allComb[8] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[8] < 0)' 
	cut += ' && (MllOS_allComb[9] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[9] < 0)' 
	cut += ' && (MllOS_allComb[10] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[10] < 0)' 
	cut += ' && (MllOS_allComb[11] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[11] < 0)' 
	cut += ' && (MllOS_allComb[12] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[12] < 0)' 
	cut += ' && (MllOS_allComb[13] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[13] < 0)' 
	cut += ' && (MllOS_allComb[14] > '+str(cutList['mllOSCut'])+' || MllOS_allComb[14] < 0) )' 


# 	cut += ' && MllOS_allComb_min > '+str(cutList['mllOSCut']) #to make sure the OS pair are same sign cut above 0. 

# 	cut += ' && Mll_sameFlavorOS > '+str(cutList['mllOSCut']) #to make sure the OS pair are same sign cut above 0. 

# 	cut += ' && ( (MllOS_allComb[0] > 80 && MllOS_allComb[0] < 100)' #on Z cut
# 	cut += ' || (MllOS_allComb[1] > 80 && MllOS_allComb[1] < 100)' #on Z cut
# 	cut += ' || (MllOS_allComb[2] > 80 && MllOS_allComb[2] < 100) )' #on Z cut

# 	cut += ' && !( (MllOS_allComb[0] > 80 && MllOS_allComb[0] < 100)' #off Z cut
# 	cut += ' || (MllOS_allComb[1] > 80 && MllOS_allComb[1] < 100)' #off Z cut
# 	cut += ' || (MllOS_allComb[2] > 80 && MllOS_allComb[2] < 100) )' #off Z cut

# 	cut += ' && ( (MllOS_allComb[0] <= 80 || MllOS_allComb[0] >= 100)' #off Z cut
# 	cut += ' || (MllOS_allComb[1] <= 80 || MllOS_allComb[1] >= 100)' #off Z cut
# 	cut += ' || (MllOS_allComb[2] <= 80 || MllOS_allComb[2] >= 100) )' #off Z cut


	isLepCut=''
	if category=='EEE': isLepCut+=' && isEEE==1'
	if category=='EEM': isLepCut+=' && isEEM==1'
	if category=='EMM': isLepCut+=' && isEMM==1'
	if category=='MMM': isLepCut+=' && isMMM==1'
	


#Start -- Method if isTTT doesnt exist
# 	'''
	if 'DataDrivenBkgTTT' in process: 
		cut+=' && (AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==1 && AllLeptonIsTight_PtOrdered[2]==1)'

	if 'DataDrivenBkgTTL' in process: 
		cut+=' && (AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==1 && AllLeptonIsTight_PtOrdered[2]==0)'
		if category=='EEE':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==0)'
		if category=='EEM':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==1)'
		if category=='EMM':
			cut+=' &&  ( (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==1)'
			cut+=' ||    (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==1) )'
		if category=='MMM':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==1)'
	if 'DataDrivenBkgTLT' in process: 
		cut+=' && (AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==1 && AllLeptonIsTight_PtOrdered[2]==0)'
		if category=='EEE':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==0)'
		if category=='EEM':
			cut+=' &&  ( (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==0)'
			cut+=' ||    (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==0) )'
		if category=='EMM':
			cut+=' &&  ( (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==1)'
			cut+=' ||    (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==1) )'
		if category=='MMM':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==1)'
	if 'DataDrivenBkgLTT' in process: 
		cut+=' && (AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==1 && AllLeptonIsTight_PtOrdered[2]==0)'
		if category=='EEE':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==0)'
		if category=='EEM':
			cut+=' &&  ( (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==0)'
			cut+=' ||    (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==0) )'
		if category=='EMM':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==0)'
		if category=='MMM':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==1)'

	if 'DataDrivenBkgTLL' in process: 
		cut+=' && (AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==0 && AllLeptonIsTight_PtOrdered[2]==0)'
		if category=='EEE':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==0)'
		if category=='EEM':
			cut+=' &&  ( (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==1)'
			cut+=' ||    (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==0) )'
		if category=='EMM':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==1)'
		if category=='MMM':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==1)'
	if 'DataDrivenBkgLTL' in process: 
		cut+=' && (AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==0 && AllLeptonIsTight_PtOrdered[2]==0)'
		if category=='EEE':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==0)'
		if category=='EEM':
			cut+=' &&  ( (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==1)'
			cut+=' ||    (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==0) )'
		if category=='EMM':
			cut+=' &&  ( (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==1)'
			cut+=' ||    (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==0) )'
		if category=='MMM':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==1)'
	if 'DataDrivenBkgLLT' in process: 
		cut+=' && (AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==0 && AllLeptonIsTight_PtOrdered[2]==0)'
		if category=='EEE':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==0 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==0)'
		if category=='EEM':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==0)'
		if category=='EMM':
			cut+=' &&  ( (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==0 && AllLeptonFlavor_PtOrdered[2]==1)'
			cut+=' ||    (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==0) )'
		if category=='MMM':
			cut+=' && (AllLeptonFlavor_PtOrdered[0]==1 && AllLeptonFlavor_PtOrdered[1]==1 && AllLeptonFlavor_PtOrdered[2]==1)'

	if 'DataDrivenBkgLLL' in process: 
		cut+=' && (AllLeptonIsTight_PtOrdered[0]==0 && AllLeptonIsTight_PtOrdered[1]==0 && AllLeptonIsTight_PtOrdered[2]==0)'
# 	'''
#End -- Method if isTTT doesnt exist

#Start -- Method if isTTT  exist
	'''
	if 'DataDrivenBkgTTT' in process: cut+=' && isTTT==1'
	if 'DataDrivenBkgTTL' in process: cut+=' && isTTL==1'
	if 'DataDrivenBkgTLT' in process: cut+=' && isTLT==1'
	if 'DataDrivenBkgLTT' in process: cut+=' && isLTT==1'
	if 'DataDrivenBkgTLL' in process: cut+=' && isTLL==1'
	if 'DataDrivenBkgLTL' in process: cut+=' && isLTL==1'
	if 'DataDrivenBkgLLT' in process: cut+=' && isLLT==1'
	if 'DataDrivenBkgLLL' in process: cut+=' && isLLL==1'
	'''
#End -- Method if isTTT exist


# 	if 'DataDrivenBkg' in process:
# 		cut+=' && (AllLeptonIsTight_PtOrdered[0]==0 || AllLeptonIsTight_PtOrdered[1]==0 || AllLeptonIsTight_PtOrdered[2]==0)'
# 	if 'DataDrivenBkg' not in process:
# 		cut+=' && (AllLeptonIsTight_PtOrdered[0]==1 && AllLeptonIsTight_PtOrdered[1]==1 && AllLeptonIsTight_PtOrdered[2]==1)'

	if 'PrunedSmearedNm1' in discriminantName: cut += ' && (theJetAK8NjettinessTau2_JetSubCalc_PtOrdered/theJetAK8NjettinessTau1_JetSubCalc_PtOrdered < 0.6)'

	massvar = 'theJetAK8PrunedMassJMRSmeared_JetSubCalc'
	if 'Data' in process: massvar = 'theJetAK8PrunedMass_JetSubCalc_PtOrdered'

	if 'Tau21Nm1' in discriminantName:  cut += ' && ('+massvar+' > 65 && '+massvar+' < 105)'

	TrigEff = 'TrigEffWeight'
		
	if(debugANALYZE):print "Applying Cuts: ", cut
	
	doDDBKGsys = True

	hists = {}
	hists[discriminantName+'_'+lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'_'+lumiStr+'fb_'+category+'_' +process,xAxisLabel,len(xbins)-1,xbins)
	if doAllSys or doDDBKGsys:
		if doDDBKGsys and 'DataDrivenBkg' in process: 	
			hists[discriminantName+'elPRUp_'     +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'elPRUp_'     +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'elPRDown_'   +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'elPRDown_'   +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'elFRUp_'     +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'elFRUp_'     +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'elFRDown_'   +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'elFRDown_'   +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'muPRUp_'     +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'muPRUp_'     +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'muPRDown_'   +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'muPRDown_'   +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'muFRUp_'     +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'muFRUp_'     +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'muFRDown_'   +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'muFRDown_'   +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
		elif doAllSys:			
			hists[discriminantName+'pileupUp_'  +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'pileupUp_'  +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'pileupDown_'+lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'pileupDown_'+lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'muRFcorrdUp_'  +lumiStr+'fb_'+category+'_'+process]=R.TH1D(discriminantName+'muRFcorrdUp_'  +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'muRFcorrdDown_'+lumiStr+'fb_'+category+'_'+process]=R.TH1D(discriminantName+'muRFcorrdDown_'+lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'muRUp_'     +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'muRUp_'     +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'muRDown_'   +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'muRDown_'   +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'muFUp_'     +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'muFUp_'     +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'muFDown_'   +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'muFDown_'   +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)

			hists[discriminantName+'btagUp_'    +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'btagUp_'    +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'btagDown_'  +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'btagDown_'  +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'mistagUp_'    +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'mistagUp_'    +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			hists[discriminantName+'mistagDown_'  +lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'mistagDown_'  +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)


			if tTree[process+'jecUp']:		
				hists[discriminantName+'jecUp_'   +lumiStr+'fb_'+category+'_'+process]  = R.TH1D(discriminantName+'jecUp_'   +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
				hists[discriminantName+'jecDown_' +lumiStr+'fb_'+category+'_'+process]  = R.TH1D(discriminantName+'jecDown_' +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
			if tTree[process+'jerUp']:		
				hists[discriminantName+'jerUp_'   +lumiStr+'fb_'+category+'_'+process]  = R.TH1D(discriminantName+'jerUp_'   +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
				hists[discriminantName+'jerDown_' +lumiStr+'fb_'+category+'_'+process]  = R.TH1D(discriminantName+'jerDown_' +lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)

			for i in range(100): hists[discriminantName+'pdf'+str(i)+'_'+lumiStr+'fb_'+category+'_'+process] = R.TH1D(discriminantName+'pdf'+str(i)+'_'+lumiStr+'fb_'+category+'_'+process,xAxisLabel,len(xbins)-1,xbins)
	for key in hists.keys(): hists[key].Sumw2()
		
	if 'Data' in process: 
		if ('DataDrivenBkg' in process):
			if ('TTT' in process or 'TTL' in process or 'TLT' in process or 'LTT' in process or 'TLL' in process or 'LTL' in process or 'LLT' in process or 'LLL' in process):  
				weightStr         ='1'
				weightelPRUpStr     ='1'
				weightelPRDownStr   ='1'
				weightelFRUpStr     ='1'
				weightelFRDownStr   ='1'
				weightmuPRUpStr     ='1'
				weightmuPRDownStr   ='1'
				weightmuFRUpStr     ='1'
				weightmuFRDownStr   ='1'
				print 'weightStr-------------------------------------------------------->', weightStr
			else: 
				print 'process----------------------------------------------------------> ', process
				weightStr         ='ddBkgWeights[0]'
				weightelPRUpStr     ='ddBkgWeights[3]'
				weightelPRDownStr   ='ddBkgWeights[4]'
				weightelFRUpStr     ='ddBkgWeights[1]'
				weightelFRDownStr   ='ddBkgWeights[2]'
				weightmuPRUpStr     ='ddBkgWeights[7]'
				weightmuPRDownStr   ='ddBkgWeights[8]'
				weightmuFRUpStr     ='ddBkgWeights[5]'
				weightmuFRDownStr   ='ddBkgWeights[6]'
		else: 
			weightStr         ='1'
			weightelPRUpStr     ='1'
			weightelPRDownStr   ='1'
			weightelFRUpStr     ='1'
			weightelFRDownStr   ='1'
			weightmuPRUpStr     ='1'
			weightmuPRDownStr   ='1'
			weightmuFRUpStr     ='1'
			weightmuFRDownStr   ='1'

		weightPileupUpStr   = '1'
		weightPileupDownStr = '1'
		weightmuRFcorrdUpStr   = '1'
		weightmuRFcorrdDownStr = '1'
		weightmuRUpStr   = '1'
		weightmuRDownStr = '1'
		weightmuFUpStr   = '1'
		weightmuFDownStr = '1'
		weighttopptUpStr    = '1'
		weighttopptDownStr  = '1'
		weightjsfUpStr    = '1'
		weightjsfDownStr  = '1'		

	else: 
		weightStr           = TrigEff+' * pileupWeight * 1 * isoSF * lepIdSF * EGammaGsfSF * MuTrkSF * MCWeight_singleLepCalc/abs(MCWeight_singleLepCalc) * '+str(weight[process])
# 		weightStr           = TrigEff+' * pileupWeight * 1 * isoSF * lepIdSF * EGammaGsfSF * MCWeight_singleLepCalc/abs(MCWeight_singleLepCalc) * '+str(weight[process])
# 		weightStr           = TrigEff+' * pileupWeight * 1 * isoSF * lepIdSF * MCWeight_singleLepCalc/abs(MCWeight_singleLepCalc) * '+str(weight[process])
# 		weightStr           = TrigEff+' * pileupWeight * JetSF_pTNbwflat * isoSF * lepIdSF * MCWeight_singleLepCalc/abs(MCWeight_singleLepCalc) * '+str(weight[process])
		weightPileupUpStr   = weightStr.replace('pileupWeight','pileupWeightUp')
		weightPileupDownStr = weightStr.replace('pileupWeight','pileupWeightDown')
		weightmuRFcorrdUpStr   = 'renormWeights[5] * '+weightStr
		weightmuRFcorrdDownStr = 'renormWeights[3] * '+weightStr
		weightmuRUpStr      = 'renormWeights[4] * '+weightStr
		weightmuRDownStr    = 'renormWeights[2] * '+weightStr
		weightmuFUpStr      = 'renormWeights[1] * '+weightStr
		weightmuFDownStr    = 'renormWeights[0] * '+weightStr
		weighttopptUpStr    = weightStr
		weighttopptDownStr  = 'topPtWeight * '+weightStr
		weightjsfUpStr      = weightStr.replace('JetSF','JetSFupwide')
		weightjsfDownStr    = weightStr.replace('JetSF','JetSFdnwide')
		if('noWeight' in cutType): 	weightStr = '1.'

	if 'Data' in process:
		origname = discriminantLJMETName
		if discriminantName == 'NWJetsSmeared':
			discriminantLJMETName = 'NJetsWtagged_0p6'
		if '0p55' in discriminantName:
			discriminantLJMETName = 'NJetsWtagged_0p55'
		if discriminantName == 'PrunedSmeared':
			discriminantLJMETName = 'theJetAK8PrunedMass_JetSubCalc_PtOrdered'
			#discriminantLJMETName = 'theJetAK8PrunedMass_JetSubCalc_new'
		if origname != discriminantLJMETName:
			print 'NEW LJMET NAME:',discriminantLJMETName

	if 'Bjet1' in discriminantName or 'Mlb' in discriminantName or 'b1' in discriminantName:
		cut += ' && (NJetsCSVwithSF_JetSubCalc > 0)'
	if 'b2' in discriminantName:
		cut += ' && (NJetsCSVwithSF_JetSubCalc > 1)'

	if 'Mlj' in discriminantName: cut += ' && (NJetsCSVwithSF_JetSubCalc == 0)'
	
	#print discriminantLJMETName+' >> '+discriminantName+''+'_'+lumiStr+'fb_'+category+'_' +process, weightStr+'*('+cut+isLepCut+')', 'GOFF'

	try:
		tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+''+'_'+lumiStr+'fb_'+category+'_' +process, weightStr+'*('+cut+isLepCut+')', 'GOFF')
		print '++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> DRAW SUCCESSFULL!!!!!'
	except:
		print '--------------------------------------------------------------------------------------------------------------------------------------------------->>>>>>>>>>>>>>>>>>>>>>>>>Skip DRAW'

	if doAllSys or doDDBKGsys:
		if doDDBKGsys and 'DataDrivenBkg' in process: 
			print 'Processing ddbkg sys !'
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'elPRUp_'     +lumiStr+'fb_'+category+'_'+process, weightelPRUpStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'elPRDown_'   +lumiStr+'fb_'+category+'_'+process, weightelPRDownStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'elFRUp_'     +lumiStr+'fb_'+category+'_'+process, weightelFRUpStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'elFRDown_'   +lumiStr+'fb_'+category+'_'+process, weightelFRDownStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'muPRUp_'     +lumiStr+'fb_'+category+'_'+process, weightmuPRUpStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'muPRDown_'   +lumiStr+'fb_'+category+'_'+process, weightmuPRDownStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'muFRUp_'     +lumiStr+'fb_'+category+'_'+process, weightmuFRUpStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'muFRDown_'   +lumiStr+'fb_'+category+'_'+process, weightmuFRDownStr+'*('+cut+isLepCut+')', 'GOFF')
		if doAllSys:
			print 'Processing ALL other sys !'
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'pileupUp_'  +lumiStr+'fb_'+category+'_'+process, weightPileupUpStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'pileupDown_'+lumiStr+'fb_'+category+'_'+process, weightPileupDownStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'muRFcorrdUp_'  +lumiStr+'fb_'+category+'_'+process, weightmuRFcorrdUpStr  +'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'muRFcorrdDown_'+lumiStr+'fb_'+category+'_'+process, weightmuRFcorrdDownStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'muRUp_'     +lumiStr+'fb_'+category+'_'+process, weightmuRUpStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'muRDown_'   +lumiStr+'fb_'+category+'_'+process, weightmuRDownStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'muFUp_'     +lumiStr+'fb_'+category+'_'+process, weightmuFUpStr+'*('+cut+isLepCut+')', 'GOFF')
			tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'muFDown_'   +lumiStr+'fb_'+category+'_'+process, weightmuFDownStr+'*('+cut+isLepCut+')', 'GOFF')

			# replace cuts for shifts
			nbtagLJMETname = 'NJetsBTagwithSF_singleLepCalc'
			cut_btagUp = cut.replace(nbtagLJMETname,'NJetsBTagwithSF_singleLepCalc_shifts[0]')#nbtagLJMETname+'_shifts[0]')
			cut_btagDn = cut.replace(nbtagLJMETname,'NJetsBTagwithSF_singleLepCalc_shifts[1]')#nbtagLJMETname+'_shifts[1]')
			cut_mistagUp = cut.replace(nbtagLJMETname,'NJetsBTagwithSF_singleLepCalc_shifts[2]')#nbtagLJMETname+'_shifts[2]')
			cut_mistagDn = cut.replace(nbtagLJMETname,'NJetsBTagwithSF_singleLepCalc_shifts[3]')#nbtagLJMETname+'_shifts[3]')
			
			bTagSFshiftName = discriminantLJMETName
			if 'NJetsBTag' in discriminantLJMETName: 
				bTagSFshiftName = discriminantLJMETName+'_shifts[0]'
			print 'BTAGup LJMET NAME',bTagSFshiftName.replace('_shifts[0]','_shifts[0]')
			tTree[process].Draw(bTagSFshiftName.replace('_shifts[0]','_shifts[0]')+' >> '+discriminantName+'btagUp'+'_'+lumiStr+'fb_'+category+'_' +process, weightStr+'*('+cut_btagUp+isLepCut+')', 'GOFF')
			print 'BTAGdn LJMET NAME',bTagSFshiftName.replace('_shifts[0]','_shifts[1]')
			tTree[process].Draw(bTagSFshiftName.replace('_shifts[0]','_shifts[1]')+' >> '+discriminantName+'btagDown'+'_'+lumiStr+'fb_'+category+'_' +process, weightStr+'*('+cut_btagDn+isLepCut+')', 'GOFF')
			print 'MISTAGup LJMET NAME',bTagSFshiftName.replace('_shifts[0]','_shifts[2]')
			tTree[process].Draw(bTagSFshiftName.replace('_shifts[0]','_shifts[2]')+' >> '+discriminantName+'mistagUp'+'_'+lumiStr+'fb_'+category+'_' +process, weightStr+'*('+cut_mistagUp+isLepCut+')', 'GOFF')
			print 'MISTAGdn LJMET NAME',bTagSFshiftName.replace('_shifts[0]','_shifts[3]')
			tTree[process].Draw(bTagSFshiftName.replace('_shifts[0]','_shifts[3]')+' >> '+discriminantName+'mistagDown'+'_'+lumiStr+'fb_'+category+'_' +process, weightStr+'*('+cut_mistagDn+isLepCut+')', 'GOFF')


			if 'DataDriven' not in process:
				if tTree[process+'jecUp']:
					tTree[process+'jecUp'].Draw(discriminantLJMETName   +' >> '+discriminantName+'jecUp'+'_'+lumiStr+'fb_'+category+'_' +process, weightStr+'*('+cut+isLepCut+')', 'GOFF')
					tTree[process+'jecDown'].Draw(discriminantLJMETName +' >> '+discriminantName+'jecDown'+'_'+lumiStr+'fb_'+category+'_' +process, weightStr+'*('+cut+isLepCut+')', 'GOFF')
				if tTree[process+'jerUp']:
					tTree[process+'jerUp'].Draw(discriminantLJMETName   +' >> '+discriminantName+'jerUp'+'_'+lumiStr+'fb_'+category+'_' +process, weightStr+'*('+cut+isLepCut+')', 'GOFF')
					tTree[process+'jerDown'].Draw(discriminantLJMETName +' >> '+discriminantName+'jerDown'+'_'+lumiStr+'fb_'+category+'_' +process, weightStr+'*('+cut+isLepCut+')', 'GOFF')

			for i in range(100): tTree[process].Draw(discriminantLJMETName+' >> '+discriminantName+'pdf'+str(i)+'_'+lumiStr+'fb_'+category+'_'+process, 'pdfWeights['+str(i)+'] * '+weightStr+'*('+cut+isLepCut+')', 'GOFF')
	
	for key in hists.keys(): 
		#print key
		hists[key].SetDirectory(0)	

	#print hists
	
	return hists
