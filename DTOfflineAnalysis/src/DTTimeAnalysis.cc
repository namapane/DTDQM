/*
 * \file DTTimeAnalysis.cc
 * 
 * $Date: 2008/12/03 10:41:13 $
 * $Revision: 1.1 $
 * \author S. Bolognesi - INFN Torino
 *
*/

#include "DQM/DTOfflineAnalysis/interface/DTTimeAnalysis.h"
#include "DQM/DTOfflineAnalysis/src/DTTimeBoxAnalysis.h"
#include "DQM/DTOfflineAnalysis/src/DTTimeBoxMeanTimerAnalysis.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"


#include "TFile.h"
// #include <DataFormats/DTDigi/interface/DTDigi.h>
// #include <DataFormats/DTDigi/interface/DTDigiCollection.h>
// #include <DataFormats/MuonDetId/interface/DTLayerId.h>

#include <iostream>

using namespace std;
using namespace edm;


DTTimeAnalysis::DTTimeAnalysis(const ParameterSet& pset) : theTimeBoxAnalysis(0),
							   theTimeBoxMeanTimerAnalysis(0) {
  debug = pset.getUntrackedParameter<bool>("debug", "false");

  if(debug)
    cout << "[DTTimeAnalysis] Constructor called!" << endl;

  theRootFileName = pset.getUntrackedParameter<string>("rootFileName", "DTTimeAnalysis.root");
  theFile = new TFile(theRootFileName.c_str(), "RECREATE");

  doTimeBoxAnalysis = pset.getUntrackedParameter<bool>("doTimeBoxAnalysis", "false");
  doTimeBoxMeanTimerAnalysis = pset.getUntrackedParameter<bool>("doTimeBoxMeanTimerAnalysis", "false");

  // Create the classes which really make the analysis
  if(doTimeBoxAnalysis)
    theTimeBoxAnalysis =
      new DTTimeBoxAnalysis(pset.getParameter<ParameterSet>("timeBoxAnalysisConfig"), theFile, consumesCollector());
  if(doTimeBoxMeanTimerAnalysis)
    theTimeBoxMeanTimerAnalysis =
      new DTTimeBoxMeanTimerAnalysis(pset.getParameter<ParameterSet>("timeBoxMeanTimerAnalysisConfig"), theFile, consumesCollector());
}

DTTimeAnalysis::~DTTimeAnalysis(){
  if(debug)
    cout << "[DTTimeAnalysis] Destructor called!" << endl;
  //   logFile.close();
}

void DTTimeAnalysis::beginJob(const EventSetup& setup){
}

void DTTimeAnalysis::endJob() {
  if(doTimeBoxAnalysis)
    theTimeBoxAnalysis->endJob();
  if(doTimeBoxMeanTimerAnalysis)
    theTimeBoxMeanTimerAnalysis->endJob();
 theFile->Close();
}

void DTTimeAnalysis::analyze(const Event& event, const EventSetup& setup){
  cout << "--- [DTTimeAnalysis] Analyze Run: " << event.id().run()
       << " #Event: " << event.id().event() << endl;

  if(doTimeBoxAnalysis)
    theTimeBoxAnalysis->analyze(event, setup);

  if(doTimeBoxMeanTimerAnalysis)
    theTimeBoxMeanTimerAnalysis->analyze(event, setup);

}

