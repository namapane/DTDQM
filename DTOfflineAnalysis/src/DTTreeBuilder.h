#ifndef DTTreeBuilder_H
#define DTTreeBuilder_H

/** \class DTTreeBuilder
 *  DQM Analysis of rechit residuals: it compares the rechit distance from wire
 *  with the segment extrapolation.
 *  Only segments with 8 hits in phi view and 4 hits in the theta view (if available)
 *  are selected.<br>
 *  The plot produced are:<br>
 *      - residuals
 *      - meantimer (with the standard formula) for different position along the wire
 *      - time boxes for different position along the wire
 *  All histos are produce per SuperLayer.
 *
 *
 *  $Date: 2013/11/05 18:19:54 $
 *  $Revision: 1.12 $
 *  \author G. Cerminara - INFN Torino
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "DataFormats/MuonDetId/interface/DTLayerId.h"
#include <FWCore/Framework/interface/ESHandle.h>
#include "FWCore/Framework/interface/ConsumesCollector.h"

//Hack to be able to call DTRecSegment2D::update and DTRecSegment4D::phiSegment
#define protected public
#include "DataFormats/DTRecHit/interface/DTRecSegment2D.h"
#undef protected
#define private public
#include "DataFormats/DTRecHit/interface/DTRecSegment4D.h"
#undef private

#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecHitCollection.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"

#include <CondFormats/DataRecord/interface/DTTtrigRcd.h>
#include "CondFormats/DataRecord/interface/DTT0Rcd.h"
#include "CondFormats/DataRecord/interface/DTMtimeRcd.h"
#include "CondFormats/DataRecord/interface/DTStatusFlagRcd.h"
#include <CondFormats/DTObjects/interface/DTTtrig.h>
#include "CondFormats/DTObjects/interface/DTT0.h"
#include "CondFormats/DTObjects/interface/DTMtime.h"
#include "CondFormats/DTObjects/interface/DTStatusFlag.h"

#include <string>
#include <vector>
#include <map>
#include <set>

class TFile;
class TH1F;
class TTree;
class TClonesArray;
class DTTtrig;
class DTT0;
class DTRecHitBaseAlgo;
class DTMtime;
class DTSegmentUpdator;

class DTTreeBuilder {
public:
  /// Constructor
  DTTreeBuilder(const edm::ParameterSet& pset, edm::ConsumesCollector && iC, TFile* file);

  /// Destructor
  virtual ~DTTreeBuilder();

  // Operations
  void analyze(const edm::Event& event, const edm::EventSetup& setup);
  void beginJob();
  void endJob();

protected:

private:

  TFile* theFile;

  bool debug;
  // Label of 4D segments in the event
  std::string theRecHits4DLabel;
  // Label of 2D segments in the event
  std::string theRecHits2DLabel;
  // Label of 1D rechits in the event
  std::string theRecHitLabel;
  // Label of muon collection in the event
  std::string theMuonLabel;

  edm::EDGetTokenT<DTRecSegment4DCollection> recHit4DToken;
  edm::EDGetTokenT<DTRecSegment2DCollection> recHit2DToken;
  edm::EDGetTokenT<DTRecHitCollection> recHitToken;
  edm::EDGetTokenT<reco::MuonCollection> muonToken;
  edm::EDGetTokenT<reco::VertexCollection> vertexToken;
  
  edm::ESGetToken<DTGeometry, MuonGeometryRecord> dtGeomToken_;
  edm::ESGetToken<DTTtrig, DTTtrigRcd> dtTTrigToken_;
  edm::ESGetToken<DTT0, DTT0Rcd> dtT0Token_;
  edm::ESGetToken<DTMtime, DTMtimeRcd> dtMtimeToken_;
  edm::ESGetToken<DTStatusFlag,DTStatusFlagRcd> dtStatusToken_;

  // Switch for checking of noisy channels
  bool checkNoisyChannels;


  TTree *theTree;
  TClonesArray *segmentArray;
  TClonesArray *segment2DArray;
  TClonesArray *muArray;
  int BX;
  //  int pix;
  int runN;
  int eventN;
  

  // Algo to re-reco the hits
  std::unique_ptr<DTRecHitBaseAlgo> theAlgo;
  std::string algoName;
  
  // Helper to refit segments
  DTSegmentUpdator* theUpdator;
  std::set<DTLayerId> skipLayersFromReference;
};
#endif

