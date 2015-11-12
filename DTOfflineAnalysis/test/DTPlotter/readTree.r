//----------------------------------------------------------------------
//
// Read trees and produce file with histogram for the specified granularity.
// 
// Run:
// .x readTree.r(<input>,<outputRootFile>,GRANULARITY)
//
// Supported GRANULARITY:
// "statByView";
// "absWStatByView";
// "statByLayer";
// "statBySL";
// "SL";
// "chamberByView";
// "chamberByLayer";
// "chamberByLayerLR";
//
//----------------------------------------------------------------------


#include "TFile.h"
#include "TTree.h"
#include "TClonesArray.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/DTSegmentObject.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/DTHitObject.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/TTreeReader.h"

#include "TSystem.h"
#include "TMath.h"
#include "TLorentzVector.h"
#include <iostream>

// R__LOAD_LIBRARY(libDTOfflineAnalysisEvent) Will work in root 6.04


using namespace std;

int NEVENTS = -1;
int debug = 0;

void readTree() {
  cout << "run with:"
       << ".x readTree.r(<input>,<outputRootFile>,GRANULARITY)" << endl;
}


void readTree(TString infile, string outputFile, string GRANULARITY="statByView") {

  //cout <<  TString(gSystem->GetLibraries()) << endl;
  
  //  if (! TString(gSystem->GetLibraries()).Contains("libEvent.so")) {
  //  cout << "LOADING " << endl;
  //  gSystem->Load("$CMSSW_BASE/src/DQM/DTOfflineAnalysis/test/root_lib/libEvent.so"); 
  //} 

  TChain c("DTSegmentTree");

  if (infile.EndsWith(".root")) { // single root file
    c.Add(infile);
  } else { // input file is chain maker script
    gROOT->ProcessLine(".x "+infile);
  }
  
//----------------------------------------------------------------------  
  outputFile = outputFile+"_"+GRANULARITY+".root";

  cout << c.GetEntries() << endl;

  dt::TTreeReader *reader = new dt::TTreeReader(&c, outputFile);
  if (GRANULARITY=="statByView") {
    reader->doStep1 = true; // also ake plots for step 1
  }
  int detail = 4; // >=2: Make 2D histograms of res vs other qty. 
                  // >=3: add plots for specific studies (eg vdrift)
                  // >=4: debug plots (eg res vs cell)
  reader->setDebug(debug);
  reader->setFilterEvents(1); //apply selection: at least 1 good, hi-pT mu + run range filter in data
  reader->setMinPt(15.);
  //  reader->setFilterSL(true); // Skip predefined list of bad SLs
  reader->setRunRange(144045, -1);
  //  reader->setRunRange(258443, 258445);


  // all segments
//   DTCut stdCut;
//   reader->setCuts("all",stdCut);

  // only segments with 12 hits
  DTCut hqCut;
  hqCut.setSegmNHitsPhi(7,10);
  hqCut.setSegmNHitsTheta(4,6);
  hqCut.setSegmPhiAngle(-25*TMath::DegToRad(),25*TMath::DegToRad());

  DTCut lqCut = hqCut; // no cuts on nhits
  lqCut.setSegmNHitsPhi(0,20);
  lqCut.setSegmNHitsTheta(0,20);

  //"Plus" phi
  // hqCut.setSegmPhiAngle(0,25*TMath::DegToRad());

  //"Minus" phi
  // hqCut.setSegmPhiAngle(-25*TMath::DegToRad(),0);


  DTCut hqCutL = hqCut;
  hqCutL.selectLR = -1;
  DTCut hqCutR = hqCut;
  hqCutR.selectLR = 1;

  if (GRANULARITY=="statByView") {
    detail =3;
  } else if (GRANULARITY=="chamberByLayerLR") {
    reader->setCuts("Cut1L",hqCutL);
    reader->setCuts("Cut1R",hqCutR);
    reader->setGranularity("chamberByLayer");
    detail=1;
  }
  //  reader->setCuts("Cut0",lqCut);
  reader->setCuts("Cut1",hqCut);

  
  reader->detail = detail; // >1: Make 2D histograms of res vs other qty.
  reader->setGranularity(GRANULARITY);

  reader->analyse(NEVENTS);

  cout << "files: " << endl;
  c.ls();
  cout << "wrote " << outputFile <<endl;
  delete reader;
}
