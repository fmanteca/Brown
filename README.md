# Muon identification and isolation scale factors for 2016 legacy re-reco

## 1. General information

- JIRA: [CMSMUONS-148](https://its.cern.ch/jira/browse/CMSMUONS-148)

- Contact person: Pedro Fernandez Manteca

- Relevant presentations: [June 27th 2018](https://indico.cern.ch/event/735342/contributions/3052342/attachments/1675781/2690375/MuonEff_POG_180627.pdf)

## 2. Datasets

- Data:

  + Datasets: /SingleMuon/Run2016*-07Aug17*/AOD, /Charmonium/Run2016*-07Aug17*/AOD
  + JSON: /afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions16/13TeV/ReReco/Final/Cert_271036-284044_13TeV_23Sep2016ReReco_Collisions16_JSON.txt
  + NTuples: /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v6

- MC: 

  + Datasets: /DYJetsToLL_M-50_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/RunIISummer16DR80Premix-PUMoriond17_80X_mcRun2_asymptotic_2016_TrancheIV_v6_ext1-v1/AODSIM
  + NTuples: /eos/cms/store/group/phys_muon/hbrun/muonPOGtnpTrees/MCDR80X/DY_Summer16PremixMoriond/MC_Moriond17_DY_tranch4Premix_part[1-11].root

## 3. Rootfiles, jsons and code

  - Rootfiles: [rootfiles](rootfiles) 
  - JSON files: [jsonfiles](jsonfiles)
  - Code: [code](code)


## 4. Instructions


   ### 4.1. skimTree
   
   Example for Run2016B:

   ```
   ./skimTree /eos/cms/store/group/phys_muon/TagAndProbe/Run2016/80X_v6/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016Bver2_GoldenJSON.root path/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016Bver2_GoldenJSON_skimmedID.root -r "all" -k "pair_deltaR HighPt Medium PF TMOST Tight2012 Track_HP abseta combRelIsoPF04dBeta dB dzPV eta mass pair_newTuneP_mass pair_newTuneP_probe_pt pair_probeMultiplicity pt relTkIso tag_IsoMu24 tag_combRelIsoPF04dBeta tag_nVertices tag_pt tag_instLumi tkHitFract TM numberOfMatchedStations tkValidHits tkExpHitIn tkExpHitOut tkPixelLay tkTrackerLay weight" -c "((pt > 10 || pair_newTuneP_probe_pt >10) && mass > 70 && mass < 130.1  && tag_combRelIsoPF04dBeta < 0.2 && tag_combRelIsoPF04dBeta> -0.5 && tag_pt > 26 && tag_IsoMu24==1 && abseta <2.501 && pair_probeMultiplicity == 1)"

   ```	
   Do it for all the data and MC samples


   ### 4.2. MC pile-up reweighting

   ```
   ./addNVtxWeight "/eos/cms/store/group/phys_muon/fernanpe/2016trees_rereco/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016Bver2_GoldenJSON_skimmedID.root /eos/cms/store/group/phys_muon/fernanpe/2016trees_rereco/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016C_GoldenJSON_skimmedID.root /eos/cms/store/group/phys_muon/fernanpe/2016trees_rereco/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016D_GoldenJSON_skimmedID.root /eos/cms/store/group/phys_muon/fernanpe/2016trees_rereco/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016E_GoldenJSON_skimmedID.root /eos/cms/store/group/phys_muon/fernanpe/2016trees_rereco/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016F_GoldenJSON_skimmedID.root" "/eos/cms/store/group/phys_muon/fernanpe/2016trees_rereco/MC_Moriond17_DY_tranch4Premix_skimmedID.root" /eos/cms/store/group/phys_muon/fernanpe/2016trees_rereco/MC_Moriond17_DY_tranch4Premix_skimmedID_weightedBCDEF.root

   ```	

   ### 4.3. Do the fits

   In order to avoid the known TnP memory issue you should add the Dima's split_mode to your CMSSW_9_4_4 release: https://github.com/drkovalskyi/cmssw/tree/split_read_mode (it has not pushed into a CMS release yet)

   + Note that the fit jobs take a long time to finish because of the large number of eta bins for this production. That's why a eta split has been applied: part1 (-2.4, 1.2), part2 (-1.2, 1.2), and part3 (1.2, 2.4)

   Send the jobs to the lxplus batch:    

   ```
   ./submit.sh

   ```

   Check the jobs status and resubmit the failed ones

   ```
   ./check-jobs.sh

   ```


   ### 4.4. Get the final jsons and rootfiles

   ```
   cd TnP_SFfromFitTool/
   
   python Make2016RerecoJsonDY.py

   ```

   
   	
