[CRAB]
jobtype                 = cmssw
scheduler               = caf


[CAF]
queue                   = cmscaf1nd

[CMSSW]
dbs_url                 = https://cmsdbsprod.cern.ch:8443/cms_dbs_caf_analysis_01_writer/servlet/DBSServlet
datasetpath             = /MinimumBias/cerminar-DtCalibrationGoodCollV9-100610-V10-45d5a4add3c13836d9608259324344ab/USER
#datasetpath             = /Commissioning/Run2010A-MuonDPG_skim-v2/RAW-RECO
#runselection            = 132440-132513
pset                    = dt_analysis_local.py


total_number_of_events  = -1
#events_per_job          = 500000
number_of_jobs         = 5
output_file             = DTLocalRecoAnalysisStd.root
get_edm_output          = 1


[USER]
#ui_working_dir          = r67647_t4_V00
return_data             = 0
 
copy_data = 1

storage_pool = None

# Configure the castor area to stageout the output
# storage_element=srm-cms.cern.ch
# storage_path=/castor/cern.ch
# user_remote_dir=/user/c/cerminar/DTAnalysis/311/r67647/t4

storage_element         = T2_CH_CAF
#user_remote_dir         = /user/c/cerminar/DT-DQM/FColl/Skims/r123732
#storage_path            = /castor/cern.ch

# per pubblicare in DBS
#dbs_url_for_publication=https://cmsdbsprod.cern.ch:8443/cms_dbs_caf_analysis_01_writer/servlet/DBSServlet
#publish_data = 1
#publish_data_name = DtCalibrationGoodCollV9-100610-V10


## for example:
#lfn=/user/a/afanfani/DQMCRAFT/DQMDTRunINSERTRUN
# Note that is important to have the outputs of each run in a different directory

user_remote_dir         = DtCalibV9-100610




