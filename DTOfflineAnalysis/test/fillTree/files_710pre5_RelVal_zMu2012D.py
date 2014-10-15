# 
# from https://cmsweb.cern.ch/das/makepy?dataset=/SingleMu/CMSSW_7_1_0_pre5-GR_R_71_V1_RelVal_zMu2012D-v1/RECO&instance=prod/global

isMC = False

process.GlobalTag.globaltag = "GR_R_71_V1::All"

readFiles = cms.untracked.vstring()

process.source.fileNames = readFiles

readFiles.extend( [
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/002DF325-14B6-E311-93B9-003048678AC0.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/004898B4-0BB6-E311-88F0-0025905A611C.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/006BCA94-12B6-E311-95B8-002618943882.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/0896F656-0AB6-E311-B121-002618943842.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/0CE9FF23-0AB6-E311-B49A-0025905A6092.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/0E2B8B45-14B6-E311-BDDC-0025905938D4.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/1CC415CF-0DB6-E311-8DA0-003048FFD732.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/26D55B78-0DB6-E311-8051-0025905A608A.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/320DBC0B-12B6-E311-A79C-00261894394D.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/387B8091-08B6-E311-8432-003048678FA6.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/3A959814-15B6-E311-A32B-002618943905.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/3AA55A35-04B6-E311-936C-0026189438CC.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/3CEE2BB7-0BB6-E311-A9B2-0025905A60CA.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/405A0D93-0BB6-E311-B68A-00261894383F.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/42065CC6-0DB6-E311-83FE-003048678BF4.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/4235C971-25B6-E311-8E07-0025905A48E4.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/448152F8-07B7-E311-BC10-0025905A6088.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/4CC0F443-10B6-E311-B8DF-003048678BAA.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/5665B489-10B6-E311-BDB1-002354EF3BDE.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/5804186C-A0B7-E311-878E-0025905A6094.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/5AE1C50E-AEB6-E311-AE9B-0026189438BF.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/5C5981F0-14B6-E311-8210-0025905AA9F0.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/6279AD7E-98B6-E311-B27A-0025905A6094.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/62B4E2E0-07B6-E311-BEBC-0026189438FF.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/6AEF9470-0FB6-E311-8BF0-0025905A608E.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/70E66FEC-10B6-E311-9A81-0025905A48D8.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/72C12FAF-06B6-E311-8CA6-002618943849.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/7887ED41-94B6-E311-910D-002618943821.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/7A3AAC0F-12B6-E311-8F72-0018F3D095F6.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/8017AB2C-09B6-E311-9096-00261894383B.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/80EF9A74-12B6-E311-81AD-0025905A6070.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/860DC546-10B6-E311-B439-00304867902E.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/8622D1F1-0CB6-E311-8AC2-0025905A48F0.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/88966445-0FB6-E311-B3D6-0026189438C2.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/8A256391-0BB6-E311-A59A-002618943904.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/8C146505-0EB6-E311-B4C6-0026189438D7.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/906BA710-06B6-E311-80F6-002618943976.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/94CEB24D-10B6-E311-ABF0-003048FFD728.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/98E25EB3-0EB6-E311-9862-0025905964BC.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/9AB33B16-10B6-E311-B7A7-0025905A48F2.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/A0E67937-0EB6-E311-8A27-0025905964C2.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/AC78A761-0EB6-E311-AC9F-0025905A60DE.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/AE73B600-13B6-E311-91EF-0025905A6104.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/B0C9936B-13B6-E311-920D-002590593902.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/BAD303F4-0BB6-E311-9A47-0025905A6104.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/C2A2761C-0DB6-E311-A293-00261894392B.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/C4EAE6F9-06B6-E311-9607-003048678B5E.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/C8103536-11B6-E311-9B6A-003048679266.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/CE5FA54D-07B6-E311-8669-002618943932.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/D0B90816-07B6-E311-83A4-0025905A613C.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/D2D1AB74-18B6-E311-AA30-0025905A48C0.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/D61B170B-0FB6-E311-BA62-0025905A6104.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/E202AA07-0AB6-E311-8731-0026189438B8.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/E60D4B48-0FB6-E311-92C6-0025905A60CA.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/E657126F-09B6-E311-B8CC-003048678C9A.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/FC5F9C5D-0EB6-E311-8990-0026189438EB.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/FC853A76-0EB6-E311-9934-0025905A60CE.root',
       '/store/relval/CMSSW_7_1_0_pre5/SingleMu/RECO/GR_R_71_V1_RelVal_zMu2012D-v1/00000/FE532E84-05B6-E311-BBCF-003048FFD744.root' ] );

