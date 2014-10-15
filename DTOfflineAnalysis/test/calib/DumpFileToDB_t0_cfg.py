import FWCore.ParameterSet.Config as cms


FILE = "t0"


process = cms.Process("DumpFileToDB")

process.load("CondCore.DBCommon.CondDBSetup_cfi")

process.source = cms.Source("EmptySource",
    numberEventsInRun = cms.untracked.uint32(1),
    firstRun = cms.untracked.uint32(1)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)


# VDrift, TTrig, TZero, Noise or channels Map into DB
process.PoolDBOutputService = cms.Service("PoolDBOutputService",
                                          process.CondDBSetup,
                                          connect = cms.string("sqlite_file:" + FILE + ".db"),
#                                           toPut = cms.VPSet(cms.PSet(record = cms.string("DTTtrigRcd"),
#                                                                      tag = cms.string("ttrig"))))

#                                           toPut = cms.VPSet(cms.PSet(record = cms.string("DTMtimeRcd"),
#                                                                      tag = cms.string("vdrift"))))
                                          toPut = cms.VPSet(cms.PSet(record = cms.string("DTT0Rcd"),
                                                                     tag = cms.string("t0"))))



#Module to dump a file into a DB
process.dumpToDB = cms.EDAnalyzer("DumpFileToDB",
                                  calibFileConfig = cms.untracked.PSet(calibConstFileName = cms.untracked.string(FILE+".txt"),
#                                                                     calibConstGranularity = cms.untracked.string('bySL'),
                                                                     calibConstGranularity = cms.untracked.string('byWire'),
                                                                     nFields = cms.untracked.int32(7)
                                                                     # VDrift & TTrig
                                                                     #untracked string calibConstGranularity = "bySL"
                                                                     #untracked int32 nFields = 4
                                                                     # TZero
                                                                     #untracked string calibConstGranularity = "byWire"
                                                                     #untracked int32 nFields = 6
                                                                     # Noise
                                                                     #untracked string calibConstGranularity = "byWire"
                                                                     #untracked int32 nFields = 7
                                                                     # Dead
                                                                     #untracked string calibConstGranularity = "byWire"
                                                                     #untracked int32 nFields = 7
                                                                     # No parameters required for ChannelDB
                                                                     ),
                                #Choose what database you want to write
#                                  dbToDump = cms.untracked.string("VDriftDB")
                                dbToDump = cms.untracked.string('TZeroDB')
                                #untracked string dbToDump = "TTrigDB"
                                #untracked string dbToDump = "NoiseDB"
                                #untracked string dbToDump = "DeadDB"
#                                  dbToDump = cms.untracked.string('TTrigDB')
                                  )
                                

process.p = cms.Path(process.dumpToDB)
    

