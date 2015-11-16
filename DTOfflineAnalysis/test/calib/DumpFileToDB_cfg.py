
####### Specify input and output

#INPUTFILE = "FT_R_53_V21_999999_t0_ModCorr.txt"
#INPUTFILE = "GR_R_74_V12A_999999_ttrig.txt"
#INPUTFILE = "MCRUN2_74_V6A_999999_ttrig.txt"
#INPUTFILE = "MCRUN2_74_V6A_999999_vdrift.txt"
#INPUTFILE = "MCRUN2_74_V6A_999999_uncert.txt"
INPUTFILE = "ttrig_residuals_256675_corrRun258443-258445.txt"

#TYPE = "TZeroDB"
TYPE = "TTrigDB"
#TYPE = "VDriftDB"
#TYPE = "RecoUncertDB"

DBFORMAT = "Legacy"
#DBFORMAT="DTRecoConditions"
#######

import FWCore.ParameterSet.Config as cms
import os

process = cms.Process("DumpFileToDB")

process.load("CondCore.DBCommon.CondDBSetup_cfi")

process.source = cms.Source("EmptySource",
    numberEventsInRun = cms.untracked.uint32(1),
    firstRun = cms.untracked.uint32(1)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)



FILE = TYPE+"_"+DBFORMAT+".db"


RECORD=""
GRANULARITY = "bySL"

if TYPE=="TZeroDB" :
    RECORD = "DTT0Rcd"
    GRANULARITY = "byWire"
if DBFORMAT=="Legacy" :
    if TYPE=="TTrigDB" : RECORD = "DTTtrigRcd"
    if TYPE=="VDriftDB" : RECORD = "DTMtimeRcd"
    if TYPE=="RecoUncertDB" : RECORD = "DTRecoUncertaintiesRcd"
elif DBFORMAT=="DTRecoConditions" :
    if TYPE=="TTrigDB" : RECORD = "DTRecoConditionsTtrigRcd"
    if TYPE=="VDriftDB" : RECORD = "DTRecoConditionsVdriftRcd"
    if TYPE=="RecoUncertDB" : RECORD = "DTRecoConditionsUncertRcd"

try:
    os.remove(FILE)
except OSError:
    pass


print INPUTFILE, FILE, RECORD, TYPE, GRANULARITY

# VDrift, TTrig, TZero, Noise or channels Map into DB
process.PoolDBOutputService = cms.Service("PoolDBOutputService",
                                          process.CondDBSetup,
                                          connect = cms.string("sqlite_file:"+FILE),
                                          toPut = cms.VPSet(cms.PSet(record = cms.string(RECORD),
#FIXME                                                                     tag = cms.string(TYPE)))
                                                                     tag = cms.string("ttrig")))
#                                           toPut = cms.VPSet(cms.PSet(record = cms.string("DTT0Rcd"),
#                                                                      tag = cms.string("t0"))))
                                          )



#Module to dump a file into a DB
process.dumpToDB = cms.EDAnalyzer("DumpFileToDB",
                                  calibFileConfig = cms.untracked.PSet(
                                      calibConstFileName = cms.untracked.string(INPUTFILE),
                                      calibConstGranularity = cms.untracked.string(GRANULARITY),
                                      ),
                                  dbFormat = cms.untracked.string(DBFORMAT),
                                  dbToDump = cms.untracked.string(TYPE),
#                                dbToDump = cms.untracked.string('NoiseDB')
#                                dbToDump = cms.untracked.string('DeadDB')
                                )




process.p = cms.Path(process.dumpToDB)
    

