/*
 *  See header file for a description of this class.
 *
 *  $Date: 2008/12/03 10:41:13 $
 *  $Revision: 1.1 $
 *  \author G. Cerminara - INFN Torino
 */
#include "DQM/DTOfflineAnalysis/src/DTTimeBoxAnalysis.h"
#include "CalibMuon/DTCalibration/interface/DTTimeBoxFitter.h"
#include "CalibMuon/DTDigiSync/interface/DTTTrigSyncFactory.h"
#include "CalibMuon/DTDigiSync/interface/DTTTrigBaseSync.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "DataFormats/DTDigi/interface/DTDigiCollection.h"
#include "DataFormats/MuonDetId/interface/DTWireId.h"

#include "CondFormats/DTObjects/interface/DTTtrig.h"

#include "DataFormats/GeometryVector/interface/GlobalPoint.h"

#include "TFile.h"
#include "TH1F.h"

class DTLayer;

using namespace std;
using namespace edm;
// using namespace cond;



// Constructor
DTTimeBoxAnalysis::DTTimeBoxAnalysis(const edm::ParameterSet& pset, TFile* file, ConsumesCollector && cc) : theFile(file), esTokenDTGeom(cc.esConsumes()),esTokenDTStatusMap(cc.esConsumes())
{
  // Get the debug parameter for verbose output
  debug = pset.getUntrackedParameter<bool>("debug");

  // Get the label to retrieve digis from the event
  digiLabel = pset.getUntrackedParameter<string>("dtDigiLabel");

  theFile->cd();
  theFitter = new DTTimeBoxFitter();
  if(debug)
    theFitter->setVerbosity(1);

  doSubtractT0 = pset.getUntrackedParameter<bool>("doSubtractT0","false");
  // Get the synchronizer
  if(doSubtractT0) {
    theSync = DTTTrigSyncFactory::get()->create(pset.getParameter<string>("tTrigMode"),
						pset.getParameter<ParameterSet>("tTrigModeConfig"), cc);
  } else {
    theSync = nullptr;
  }

  checkNoisyChannels = pset.getUntrackedParameter<bool>("checkNoisyChannels","false");

  if(debug) 
    cout << "[DTTimeBoxAnalysis]Constructor called!" << endl;
}



// DEstructor
DTTimeBoxAnalysis::~DTTimeBoxAnalysis(){
  if(debug) 
    cout << "[DTTimeBoxAnalysis]Destructor called!" << endl;

//   // Delete all histos
//   for(map<DTSuperLayerId, TH1F*>::const_iterator slHisto = theHistoMap.begin();
//       slHisto != theHistoMap.end();
//       slHisto++) {
//     delete (*slHisto).second;
//   }

  theFile->Close();
  delete theFitter;
}



/// Perform the real analysis
void DTTimeBoxAnalysis::analyze(const edm::Event & event, const edm::EventSetup& eventSetup) {
  if(debug)
    cout << "[DTTimeBoxAnalysis] Analyze #Run: " << event.id().run()
	 << " #Event: " << event.id().event() << endl;

  // Get the digis from the event
  Handle<DTDigiCollection> digis; 
  event.getByLabel(digiLabel, digis);
  
  // Get the map of noisy channels
  const DTStatusFlag* statusMap = nullptr;
  if(checkNoisyChannels) {
    statusMap = &eventSetup.getData(esTokenDTStatusMap);
  }
  // Get the DT Geometry
  const DTGeometry* dtGeom = &eventSetup.getData(esTokenDTGeom);

  if(doSubtractT0)
    theSync->setES(eventSetup);

  // Iterate through all digi collections ordered by LayerId   
  DTDigiCollection::DigiRangeIterator dtLayerIt;
  for (dtLayerIt = digis->begin();
       dtLayerIt != digis->end();
       ++dtLayerIt){
    // The layerId
    const DTLayerId layerId = (*dtLayerIt).first;
    const DTSuperLayerId slId = layerId.superlayerId();

    // Get the histo from the map
    vector<TH1F *> timeBoxVector;
    if(theHistoMap.find(slId) == theHistoMap.end()) {
      // Book the time boxes

      timeBoxVector.push_back(new TH1F(getTBoxName(slId).c_str(), "Time box (ns)", 12800, -1000, 9000));
      timeBoxVector.push_back(new TH1F(string(getTBoxName(slId)+"_1of3X").c_str(),
				       "Time box 1/3 X (ns)", 12800, -1000, 9000));
      timeBoxVector.push_back(new TH1F(string(getTBoxName(slId)+"_2of3X").c_str(),
				       "Time box 2/3 X (ns)", 12800, -1000, 9000));
      timeBoxVector.push_back(new TH1F(string(getTBoxName(slId)+"_3of3X").c_str(),
				       "Time box 3/3 X (ns)", 12800, -1000, 9000));
      theHistoMap[slId] = timeBoxVector;
    } else {
      timeBoxVector = theHistoMap[slId];
    }
    TH1F *hO = theOccupancyMap[layerId];
    if(hO == 0) {
      // Book the histogram
      theFile->cd();
      hO = new TH1F(getOccupancyName(layerId).c_str(), "Occupancy", 100, 0, 100);
      if(debug)
	cout << "  New Time Box: " << hO->GetName() << endl;
      theOccupancyMap[layerId] = hO;
    }



    // Get the iterators over the digis associated with this LayerId
    const DTDigiCollection::Range& digiRange = (*dtLayerIt).second;

    // Loop over all digis in the given range
    for (DTDigiCollection::const_iterator digi = digiRange.first;
	 digi != digiRange.second;
	 digi++) {
      const DTWireId wireId(layerId, (*digi).wire());

      // Check for noisy channels and skip them
       if(checkNoisyChannels) {
	bool isNoisy = false;
	bool isFEMasked = false;
	bool isTDCMasked = false;
	bool isTrigMask = false;
	bool isDead = false;
	bool isNohv = false;
	statusMap->cellStatus(wireId, isNoisy, isFEMasked, isTDCMasked, isTrigMask, isDead, isNohv);
	if(isNoisy) {
	  if(debug)
	    cout << "Wire: " << wireId << " is noisy, skipping!" << endl;
	  continue;
	}      
	}
      theFile->cd();
      double offset = 0;
      if(doSubtractT0) {
	const DTLayer* layer = 0;//fake
	const GlobalPoint glPt;//fake
	offset = theSync->offset(layer, wireId, glPt);
      }
      const DTLayer* layer = dtGeom->layer(layerId);
      DTTopology dtTopo = layer->specificTopology();
      //cout << "First: " << dtTopo.firstChannel() << " last: " << dtTopo.lastChannel()
      //     << " wire: " << (*digi).wire() << endl;
      if(((*digi).wire() - dtTopo.firstChannel()) < ((dtTopo.lastChannel() - dtTopo.firstChannel())/3)) {
	//cout << "1/3 X" << endl;
	 timeBoxVector[1]->Fill((*digi).time()-offset);
      } else if(((*digi).wire() - dtTopo.firstChannel()) < ((dtTopo.lastChannel() - dtTopo.firstChannel())*2/3)) {
	//cout << "2/3 X" << endl;
	timeBoxVector[2]->Fill((*digi).time()-offset);
      } else if(((*digi).wire() - dtTopo.firstChannel()) < ((dtTopo.lastChannel() - dtTopo.firstChannel()))) {
	//cout << "3/3 X" << endl;
	timeBoxVector[3]->Fill((*digi).time()-offset);
      }
      timeBoxVector[0]->Fill((*digi).time()-offset);

      if(debug) {
	cout << "   Filling Time Box:   " << timeBoxVector[0]->GetName() << endl;
	cout << "           offset (ns): " << offset << endl;
	cout << "           time(ns):   " << (*digi).time()-offset<< endl;
      }
      hO->Fill((*digi).wire());
    }
  }
}


void DTTimeBoxAnalysis::endJob() {
  if(debug) 
    cout << "[DTTimeBoxAnalysis]Writing histos to file!" << endl;
  
  // Write all time boxes to file
  theFile->cd();
  for(map<DTSuperLayerId, vector<TH1F*> >::const_iterator slHisto = theHistoMap.begin();
      slHisto != theHistoMap.end();
      slHisto++) {
    int count = 0;
    for(vector<TH1F*>::const_iterator histo = (*slHisto).second.begin();
	histo != (*slHisto).second.end();
	histo++) {
      theFile->cd();
      (*histo)->Write();
      //if little statistics then the fitter goes in an infinite loop (rebinning the histo)
      //pair<double, double> meanAndSigma = theFitter->fitTimeBox((*histo));
      //cout << count  << "/3 X " << endl;
      //cout << (*slHisto).first << endl
      //	   << "Mean(ns): " << meanAndSigma.first << " sigma(ns): " <<  meanAndSigma.second << endl;
      count++;
    }
  }
  for(map<DTLayerId, TH1F*>::const_iterator slHisto = theOccupancyMap.begin();
      slHisto != theOccupancyMap.end();
      slHisto++) {
      theFile->cd();
    (*slHisto).second->Write();
  }
  
}




string DTTimeBoxAnalysis::getTBoxName(const DTSuperLayerId& slId) const {
  string histoName;
  stringstream theStream;
  theStream << "Ch_" << slId.wheel() << "_" << slId.station() << "_" << slId.sector()
	    << "_SL" << slId.superlayer() << "_hTimeBox";
  theStream >> histoName;
  return histoName;
}

string DTTimeBoxAnalysis::getOccupancyName(const DTLayerId& slId) const {
  string histoName;
  stringstream theStream;
  theStream << "Ch_" << slId.wheel() << "_" << slId.station() << "_" << slId.sector()
	    << "_SL" << slId.superlayer() << "_L"<< slId.layer() <<"_Occupancy";
  theStream >> histoName;
  return histoName;
}


