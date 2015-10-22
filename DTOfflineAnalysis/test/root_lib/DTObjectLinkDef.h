#include <DQM/DTOfflineAnalysis/src/DTSegmentObject.h>
#include <DQM/DTOfflineAnalysis/src/DTHitObject.h>
#include <DQM/DTOfflineAnalysis/src/DTMuObject.h>
#include "TTreeReader.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/DTDetId.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/Histograms.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/DTHistoPlotter.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/Utils.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/DTCut.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/FEDNtupleReader.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/FEDNumbering.h"


#ifdef __CINT__
#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;


#pragma link C++ class DTHitObject;
#pragma link C++ class DTMuObject;
#pragma link C++ class DTSegmentObject;
#pragma link C++ class TTreeReader;
#pragma link C++ class DTDetId;
#pragma link C++ class HRes1DHits;
#pragma link C++ class HSegment;
#pragma link C++ class DTHistoPlotter;
#pragma link C++ class Utils;
#pragma link C++ class DTCut;
#pragma link C++ class SimTreeReader;
#pragma link C++ class FEDNtupleReader;
#pragma link C++ class FEDNumbering;


#endif



