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
  DTTreeBuilder(const edm::ParameterSet& pset, TFile* file);

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
  edm::ESHandle<DTTtrig> tTrigMap;
  edm::ESHandle<DTT0> t0Handle;
  edm::ESHandle<DTMtime> mTimeHandle;
  

  // Algo to re-reco the hits
  DTRecHitBaseAlgo *theAlgo;
  std::string algoName;
  
  // Helper to refit segments
  DTSegmentUpdator* theUpdator;
  std::set<DTLayerId> skipLayersFromReference;
};
#endif

