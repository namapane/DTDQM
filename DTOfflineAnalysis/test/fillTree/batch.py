#!/bin/env python3
#import sys
import imp
import copy
import os
import shutil
#import pickle
#import math


def chunks(l, n):
    return [l[i:i+n] for i in range(0, len(l), n)]


def condorSubScript( index, mainDir ):
   '''prepare the Condor submition script'''
   script = '''
executable              = $(directory)/batchScript.sh
arguments               = {mainDir}/$(directory) $(ClusterId)$(ProcId)
output                  = log/$(ClusterId).$(ProcId).out
error                   = log/$(ClusterId).$(ProcId).err
log                     = log/$(ClusterId).log
Initialdir              = $(directory)
request_memory          = 0
#Possible values: https://batchdocs.web.cern.ch/local/submit.html
+JobFlavour             = longlunch

x509userproxy           = {home}/x509up_u{uid}

#https://www-auth.cs.wisc.edu/lists/htcondor-users/2010-September/msg00009.shtml
periodic_remove         = JobStatus == 5

ShouldTransferFiles     = NO
'''   
   return script.format(home=os.path.expanduser("~"), uid=os.getuid(), mainDir=mainDir)


def batchScriptCERN( index, remoteDir=''):
   '''prepare the Condor version of the batch script, to run on HTCondor'''
#   print "INDEX", index
#   print "remotedir", remoteDir
   script = """#!/bin/bash
set -euo pipefail

if [ -z ${_CONDOR_SCRATCH_DIR+x} ]; then
  #running locally
  runninglocally=true
  _CONDOR_SCRATCH_DIR=$(mktemp -d)
  SUBMIT_DIR=$(pwd)
else
  runninglocally=false
  SUBMIT_DIR=$1
fi

cd $SUBMIT_DIR
eval $(scram ru -sh)

cp run_cfg.py $_CONDOR_SCRATCH_DIR
cd $_CONDOR_SCRATCH_DIR

echo 'Running at:' $(date)
echo path: `pwd`

cmsRunStatus=   #default for successful completion is an empty file
cmsRun run_cfg.py |& grep -v -e 'MINUIT WARNING' -e 'Second derivative zero' -e 'Negative diagonal element' -e 'added to diagonal of error matrix' > log.txt || cmsRunStatus=$?

echo -n $cmsRunStatus > exitStatus.txt
echo 'cmsRun done at: ' $(date) with exit status: ${cmsRunStatus+0}
gzip log.txt

export ROOT_HIST=0
if [ -s DTLocalReco.root ]; then
 root -q -b '${CMSSW_BASE}/src/DQM/DTOfflineAnalysis/test/fillTree/rootFileIntegrity.r(\"DTLocalReco.root\")'
else
 echo moving empty file
 mv DTLocalReco.root DTLocalReco.root.empty
fi

echo "Files on node:"
ls -la

#delete submission scripts, so that they are not copied back (which fails sometimes)
rm -f run_cfg.py batchScript.sh

echo '...done at' $(date)

#note cping back is handled automatically by condor
if $runninglocally; then
  cp DTLocalReco.root* *.txt *.gz $SUBMIT_DIR
fi

exit $cmsRunStatus
""" 
   return script




if __name__ == '__main__':
    cfgFileName = "fillDTTree_rereco.py"
    batchSet=""
    jobName = "Chunk"
    numFiles = 25

    if batchSet != "" :
        os.mkdir(batchSet)
    else :
        batchSet = "."

    handle = open(cfgFileName, 'r')
    cfo = imp.load_source("pycfg", cfgFileName, handle)
    handle.close()

    fullList = copy.deepcopy(cfo.process.source.fileNames)

    fileBlocks =  chunks(fullList,numFiles)


    condorscriptFileName = os.path.join(os.getcwd(), 'condor.sub')
    with open(condorscriptFileName,'w') as condorscriptFile:
        condorscriptFile.write(condorSubScript(0, os.getcwd()))
    

    i=0
    for files in fileBlocks :
       jobDir=jobName+"_"+str(i)
       print(jobDir)
       path = batchSet+"/"+jobDir
       os.mkdir(path)
       os.mkdir( jobDir + '/log' )
       cfo.process.source.fileNames = files
       cfo.process.maxEvents.input = -1
       i=i+1
       cfgFile = open(path+'/run_cfg.py','w')
       cfgFile.write( cfo.process.dumpPython() )
       cfgFile.write( '\n' )
       cfgFile.close()

       scriptFile = open(path+'/batchScript.sh','w')
       scriptFile.write( batchScriptCERN( i ) )
       scriptFile.close()
       if os.path.exists('*.db') :
           os.system('cp *.db '+path)
