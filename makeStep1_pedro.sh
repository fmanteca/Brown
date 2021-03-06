#!/bin/bash

hostname

infilename=${1}
outfilename=${2}
inputDir=${3}
outputDir=${4}

scratch=${PWD}
macroDir=${PWD}
source /cvmfs/cms.cern.ch/cmsset_default.sh
#scramv1 project CMSSW CMSSW_7_4_14
#cd CMSSW_7_4_14
eval `scramv1 runtime -sh`
#cd -

export PATH=$PATH:$macroDir

XRDpath=root://cmseos.fnal.gov/$inputDir
root -l -b -q makeStep1.C\(\"$macroDir\",\"$XRDpath/$infilename\",\"$outputDir/$outfilename\"\)

# echo "ROOT Files:"
# ls -l *.root

# # copy output to eos

# echo "xrdcp output for condor"
# for FILE in *.root
# do
#   echo "xrdcp -f $outputDir/$outputfilename root://cmseos.fnal.gov/${outputDir}/$outputDir/$outputfilename"
#   cp output_trees/$outputfilename /eos/uscms/store/user/fernanpe/slimmedTrees/
#   XRDEXIT=$?
#   if [[ $XRDEXIT -ne 0 ]]; then
#     rm *.root
#     echo "exit code $XRDEXIT, failure in xrdcp"
#     exit $XRDEXIT
#   fi
#   rm ${FILE}
#done
