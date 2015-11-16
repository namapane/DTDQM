
#TYPE = "TZeroDB"
TYPE = "TTrigDB"
#TYPE = "VDriftDB"
#TYPE = "RecoUncertDB"

#GLOBALTAG = "START53_V7G"
#GLOBALTAG = "MC_53_V7A"
#GLOBALTAG = "PRE_ST62_V8"
#GLOBALTAG = "GR_R_71_V3"
#GLOBALTAG = "START72_V1" #
#GLOBALTAG = "MCRUN2_74_V6A"
#GLOBALTAG = "GR_R_74_V12A"
#GLOBALTAG = "DESRUN2_75_V0"
#GLOBALTAG = "MCRUN1_75_V0"
#GLOBALTAG = "GR_R_75_V0A"
#GLOBALTAG = "GR_H_V59A"
#GLOBALTAG = "75X_mcRun2_asymptotic_v1"

INPUTFILE = ""
#INPUTFILE = "TTrigDB_Legacy.db"
#INPUTFILE = "VDriftDB_Legacy.db"
#INPUTFILE = "RecoUncertDB_Legacy.db"
#INPUTFILE = "TTrigDB_DTRecoConditions.db"
#INPUTFILE = "VDriftDB_DTRecoConditions.db"
#INPUTFILE = "RecoUncertDB_DTRecoConditions.db"
#INPUTFILE = "DTRecoConditions_RecoUncertDB.db"
#INPUTFILE = "DTRecoConditionsRecoUncert_True_v0.db"
#INPUTFILE = "FT_R_53_V21_999999_t0_ModCorr.db"
#INPUTFILE = "TZeroDB_ModCorr.db"
#INPUTFILE = "DT_t0_cosmic2009_V01_ModCorr_express.db"
#INPUTFILE = "DT_t0_cosmic2009_V01_ModCorr_hlt.db"
#INPUTFILE = "ttrig_residuals_254879.db"
INPUTFILE = "ttrig_residuals_256675.db"
#INPUTFILE = "ttrig_residuals_258443_new.db"
#INPUTFILE = "ttrig_residuals_258443_151106.db"

INPUTTAG=""
#INPUTTAG = "DT_t0_cosmic2009_V01_ModCorr_express"
#INPUTTAG="DTRecoConditionsRecoUncert_True_v0"


DBFORMAT = "Legacy"
#DBFORMAT = "DTRecoConditions"


#GLOBALTAG = "FT_R_53_V21" 
#GLOBALTAG = "GR_P_V42"
#GLOBALTAG = "FT_53_V21_AN3" #for 22Jan2013
#GLOBALTAG = "GR_R_74_V8" #used for 7_4_0_pre9 rereco
#GLOBALTAG = "GR_R_53_V21A" # last for Run I rereco

GLOBALTAG = "74X_dataRun2_Prompt_v4" #used for 2015D prompt

#RUN=160404 # approx start of 2012C
#RUN=198049 # approx start of 2012C
#RUN=202305 # approx end of 2012C
#RUN=203894 # approx stary of 2012D
#RUN=125644
RUN=999999

if INPUTTAG!="" and INPUTFILE!="" :
    print 'ERROR!'
    exit

if INPUTFILE!="":
    OUTPUTFILE=INPUTFILE #[type].txt is appended
elif INPUTTAG!="" :
    OUTPUTFILE=INPUTTAG
else :
    OUTPUTFILE=GLOBALTAG+"_"+str(RUN)


###########

RECORD=""
if TYPE=="TZeroDB" : RECORD = "DTT0Rcd"
elif DBFORMAT=="Legacy" :
    if TYPE=="TTrigDB" : RECORD = "DTTtrigRcd"
    if TYPE=="VDriftDB" : RECORD = "DTMtimeRcd"
    if TYPE=="RecoUncertDB" : RECORD = "DTRecoUncertaintiesRcd"
elif DBFORMAT=="DTRecoConditions" :
    if TYPE=="TTrigDB" : RECORD = "DTRecoConditionsTtrigRcd"
    if TYPE=="VDriftDB" : RECORD = "DTRecoConditionsVdriftRcd"
    if TYPE=="RecoUncertDB" : RECORD = "DTRecoConditionsUncertRcd"



import FWCore.ParameterSet.Config as cms

process = cms.Process("DumpDBToFile")
process.load("CondCore.DBCommon.CondDBSetup_cfi")

process.source = cms.Source("EmptySource",
    numberEventsInRun = cms.untracked.uint32(1),
    firstRun = cms.untracked.uint32(RUN)
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(1)
)


#v1
#process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
#process.GlobalTag.globaltag = GLOBALTAG+"::All"

#v2
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff')
from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.GlobalTag = GlobalTag(process.GlobalTag, GLOBALTAG, '')

print "GT:", GLOBALTAG, "Record:", RECORD, "Tag:", TYPE


if INPUTFILE!="" :
    print "Read from: ", INPUTFILE
    process.GlobalTag.toGet = cms.VPSet(
        cms.PSet(record = cms.string(RECORD),
#                 tag = cms.string(TYPE),
                 tag = cms.string("ttrig"),
#                 tag = cms.string('t0'),
#                 tag = cms.string('T0DB'),
#                 tag = cms.string('DT_t0_cosmic2009_V01_ModCorr_hlt'),
                 connect = cms.untracked.string("sqlite_file:"+INPUTFILE)
                 )
        )

if INPUTTAG!="" :
    print "Read from tag: ", INPUTTAG
    process.GlobalTag.toGet = cms.VPSet(
        cms.PSet(record = cms.string(RECORD),
                 tag = cms.string(INPUTTAG),
#                 connect = cms.untracked.string('frontier://FrontierProd/CMS_CONDITIONS'),
#                 connect = cms.untracked.string('frontier://FrontierProd/CMS_COND_DT_000')
                 )
        )


process.dumpT0ToFile = cms.EDAnalyzer("DumpDBToFile",
    dbToDump = cms.untracked.string('TZeroDB'),
    dbLabel = cms.untracked.string(''),
    calibFileConfig = cms.untracked.PSet(
        nFields = cms.untracked.int32(8),
        calibConstGranularity = cms.untracked.string('byWire')
    ),
    outputFileName = cms.untracked.string(OUTPUTFILE+'_t0.txt')
)

process.dumpTTrigToFile = cms.EDAnalyzer("DumpDBToFile",
    dbToDump = cms.untracked.string('TTrigDB'),
    dbLabel = cms.untracked.string(''),
    dbFormat = cms.untracked.string(DBFORMAT),
    calibFileConfig = cms.untracked.PSet(
        nFields = cms.untracked.int32(8),
        calibConstGranularity = cms.untracked.string('bySL')
    ),
    outputFileName = cms.untracked.string(OUTPUTFILE+'_ttrig.txt')
)


process.dumpVdToFile = cms.EDAnalyzer("DumpDBToFile",
    dbToDump = cms.untracked.string('VDriftDB'),
    dbLabel = cms.untracked.string(''),
    dbFormat = cms.untracked.string(DBFORMAT),
    calibFileConfig = cms.untracked.PSet(
        nFields = cms.untracked.int32(8),
        calibConstGranularity = cms.untracked.string('bySL')
    ),
    outputFileName = cms.untracked.string(OUTPUTFILE+'_vdrift.txt')
)


process.dumpUncertToFile = cms.EDAnalyzer("DumpDBToFile",
    dbToDump = cms.untracked.string('RecoUncertDB'),
    dbLabel = cms.untracked.string(''),
    dbFormat = cms.untracked.string(DBFORMAT),
    calibFileConfig = cms.untracked.PSet(
        nFields = cms.untracked.int32(8),
        calibConstGranularity = cms.untracked.string('bySL')
    ),
    outputFileName = cms.untracked.string(OUTPUTFILE+'_uncert.txt')
)


#process.p1 = cms.Path(process.dumpT0ToFile)
if TYPE=="TZeroDB" :  process.p2 = cms.Path(process.dumpT0ToFile)
if TYPE=="TTrigDB" :  process.p2 = cms.Path(process.dumpTTrigToFile)
if TYPE=="VDriftDB" : process.p3 = cms.Path(process.dumpVdToFile)
if TYPE=="RecoUncertDB": process.p4 = cms.Path(process.dumpUncertToFile)


