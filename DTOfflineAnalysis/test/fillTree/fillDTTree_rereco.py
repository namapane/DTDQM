import FWCore.ParameterSet.Config as cms

######################################################################

isMC = False             #True for MC

reReco = False           #re-reconstruct segments; if true, the following are used:
fromRAW = True           #re-reco from RAW (otherwise, re-reco segments from rechits)
doAngleCorr = False      #apply angle correction (experimental)
T0_CALIBRATION = ""      #ttrig .db to use
TTRIG_CALIBRATION = ""   #ttrig .db to use
VDRIFT_CALIBRATION = ""  #vdrift .db to use
ALIGNMENT = ""           #alignment .db to use
JSON = "Cert_Collisions2023_366442_368823_Muon.py"

######################################################################
import os
print('Working in:', os.environ['CMSSW_BASE'])

from Configuration.StandardSequences.Eras import eras
process = cms.Process("DTOffAna", eras.Run3)

# the source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    )                        
#    duplicateCheckMode = cms.untracked.string('noDuplicateCheck')
)

process.options = cms.untracked.PSet(
#    wantSummary = cms.untracked.bool(True)
    fileMode = cms.untracked.string('NOMERGE')
    )


#process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_condDBv2_cff') # up to CMSSW_10
#from Configuration.AlCa.GlobalTag_condDBv2 import GlobalTag
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
from Configuration.AlCa.GlobalTag import GlobalTag
                              
################### Set input samples
from past.builtins import execfile
#execfile("files_ZMu-22Jan2013-v1.py")                                    # Data
#execfile("files_710pre4_RelVal_zMu2012D.py")                        # Data 71X
#execfile("files_710pre5_RelVal_zMu2012D.py")                        # Data 71X
#execfile("files_ZMu-2012D-740p9.py")                                 # Data repro in 74X
#execfile("files_DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.py")    # Z MC
#execfile("files_RelValZMM5312.py")                                       # Z RelVal, 5X
#execfile("files_RelValZMM700p4.py")                                      # Z RelVal, 7X
#execfile("files_ZMu_2015D.py")                                  # 2015D-v3
#execfile("files_ZMu_2015Dv4.py")                                # 2015D-v4
#execfile("files_ZMu_2016Bv2.py")                                 # 2016B-v2
#execfile("files_ZMu_2018Bv1.py")
#execfile("files_ZMu_2022Ev1.py")
execfile("files_ZMu_2023Cv4.py")


# Override the GT set in flies above to use IDEAL MC
# process.GlobalTag.globaltag = "MC_53_V7A::All"  # IDEAL MC

###################

process.source.inputCommands = cms.untracked.vstring("keep *", "drop *_MEtoEDMConverter_*_*", "drop L1GlobalTriggerObjectMapRecord_hltL1GtObjectMap__HLT", "drop l1extra*_*_*_*")

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
    )


process.load("Configuration.StandardSequences.GeometryDB_cff")
process.load("Configuration.StandardSequences.MagneticField_cff")


if T0_CALIBRATION != "" :
    process.GlobalTag.toGet.extend(cms.VPSet(
        cms.PSet(record = cms.string("DTT0Rcd"),
                 tag = cms.string("t0"),
                 connect = cms.string("sqlite_file:"+T0_CALIBRATION))
        )
    )
if TTRIG_CALIBRATION != "" :
    process.GlobalTag.toGet.extend(cms.VPSet(
        cms.PSet(record = cms.string("DTTtrigRcd"),
                 tag = cms.string("ttrig"),
                 connect = cms.string("sqlite_file:"+TTRIG_CALIBRATION))
        )
    )
if VDRIFT_CALIBRATION != "" :
     process.GlobalTag.toGet.extend(cms.VPSet(
         cms.PSet(record = cms.string("DTMtimeRcd"),
                  tag = cms.string("vDrift"),
                  connect = cms.string("sqlite_file:"+VDRIFT_CALIBRATION))
         )
    )

### Non-standard DB alignment
#DTGeom16May_Design.db --> internal alignment nominale
#DTGeom16May_SL.db     --> superlayer corrections
#DTGeom16May_Layer.db  --> layer to layer corrections
if ALIGNMENT != "" :
    import CondCore.DBCommon.CondDBSetup_cfi
    process.muonAlignment = cms.ESSource("PoolDBESSource",
                                      connect = cms.string("sqlite_file:"+ALIGNMENT),

                                      DBParameters = CondCore.DBCommon.CondDBSetup_cfi.CondDBSetup.DBParameters,
                                      toGet = cms.VPSet(cms.PSet(record = cms.string("DTAlignmentRcd"),
                                                                 tag =  cms.string("DTAlignmentRcd")),
                                                        cms.PSet(record = cms.string("DTAlignmentErrorRcd"),
                                                                 tag =  cms.string("DTAlignmentErrorRcd"))
                                                        )
                                      )
    process.es_prefer_muonAlignment = cms.ESPrefer("PoolDBESSource","muonAlignment")


process.load("Configuration/StandardSequences/RawToDigi_Data_cff")
process.load("Configuration/StandardSequences/Reconstruction_cff")

# message logger
process.load('FWCore.MessageService.MessageLogger_cfi')
process.MessageLogger.cerr.FwkReport.reportEvery = 1000
#suppress message: "Failed to get  TEV refits, fall back to sigma switch."
#process.MessageLogger.suppressWarning= cms.untracked.vstring('muons1stStep')

process.goodPrimaryVertices = cms.EDFilter("VertexSelector",
  src = cms.InputTag("offlinePrimaryVertices"),
  cut = cms.string("!isFake && ndof > 4 && abs(z) <= 24 && position.Rho <= 2"),
  filter = cms.bool(True),
)

if (doAngleCorr) :
    process.dt4DSegments.Reco4DAlgoConfig.recAlgoConfig.doAngleCorr = True;
    process.dt4DSegments.Reco4DAlgoConfig.Reco2DAlgoConfig.doAngleCorr = True; # FIXME: hit recomputation @step2 is not activated!


process.load("DQM.DTOfflineAnalysis.dtLocalRecoAnalysis_cfi")
process.dtLocalRecoAnal.rootFileName = 'DTLocalReco.root'
#process.dtLocalRecoAnal.debug = True
#process.dtLocalRecoAnal.treeBuilderConfig.debug = True

# FIXME!!! FIXME FIXME FIXME ----------------------------------------------------------------------
#Just for steps 1, 2?
#process.dtLocalRecoAnal.treeBuilderConfig.recAlgoConfig.stepTwoFromDigi = True
#process.dtLocalRecoAnal.treeBuilderConfig.segmentUpdatorConfig.stepTwoFromDigi = True
# FIXME!!! FIXME FIXME FIXME ----------------------------------------------------------------------

if reReco :
    if fromRAW: ### redigi + rereco, from RAW
#        process.jobPath = cms.Path(process.goodPrimaryVertices*process.muonDTDigis*process.dtlocalreco+process.dt2DSegments+process.muonreco+process.dtLocalRecoAnal)
        process.jobPath = cms.Path(process.goodPrimaryVertices+process.muonDTDigis+process.dtlocalreco_with_2DSegments+process.dtLocalRecoAnal) ### FIXME: without muon reco
    else: ### re-reconstruct segments from rechits
        process.dt4DSegments.Reco4DAlgoConfig.recAlgoConfig.stepTwoFromDigi = True
        process.dt4DSegments.Reco4DAlgoConfig.Reco2DAlgoConfig.recAlgoConfig.stepTwoFromDigi = True
#    process.jobPath = cms.Path(process.goodPrimaryVertices*process.dt4DSegments+process.muonreco+process.dtLocalRecoAnal)
        process.jobPath = cms.Path(process.goodPrimaryVertices*process.dt4DSegments+process.dtLocalRecoAnal) ### FIXME: without muon reco


else : # Take original segments
    process.jobPath = cms.Path(process.goodPrimaryVertices*process.dtLocalRecoAnal)





## Also run standard DQM code (MC only)
if (False) :
    process.load("DQMServices.Core.DQMStore_cfg")
    process.load("DQMServices.Components.DQMEnvironment_cfi")
    process.dqmSaver.convention = 'Offline'
    # FIXME: correct this
    process.dqmSaver.workflow = '/Cosmics/CMSSW_2_2_X-Testing/RECO'      
    process.load("Validation.DTRecHits.DTRecHitQualityAll_cfi")
    process.load("Validation.DTRecHits.DTRecHitClients_cfi")
##process.rechivalidation.doStep2 = False
# process.rechivalidation.recHitLabel = 'hltDt1DRecHits'
# process.rechivalidation.segment4DLabel = 'hltDt4DSegments'
# process.seg2dsuperphivalidation.segment4DLabel = 'hltDt4DSegments'
# process.seg4dvalidation.segment4DLabel = 'hltDt4DSegments'
    process.validation = cms.Sequence(process.dtLocalRecoValidation_no2D)
    process.clients = cms.Sequence(process.dtLocalRecoValidationClients)
    process.p = cms.Path(process.validation + process.dqmSaver)


# JSON
if (not isMC and JSON != "") :
    execfile(JSON)

