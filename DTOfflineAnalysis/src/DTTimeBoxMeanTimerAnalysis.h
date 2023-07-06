#ifndef DTTimeBoxMeanTimerAnalysis_H
#define DTTimeBoxMeanTimerAnalysis_H

/** \class DTTimeBoxMeanTimerAnalysis
 *  DQM Analysis of time boxes and meantimer as a function of position along the wire
 *  (computed with the segment extrapolation).
 *  Only segments with 8 hits in phi view and 4 hits in the theta view (if available)
 *  are selected.<br>
 *  The plot produced are:<br>
 *      - meantimer (with the standard formula) for different position along the wire
 *      - time boxes for different position along the wire
 *  All histos are produce per SuperLayer.
 *
 *
 *  $Date: 2008/12/03 10:41:13 $
 *  $Revision: 1.1 $
 *  \author S. Bolognesi - INFN Torino
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "DataFormats/MuonDetId/interface/DTSuperLayerId.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"

#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "CondFormats/DataRecord/interface/DTStatusFlagRcd.h"
#include "CondFormats/DTObjects/interface/DTStatusFlag.h"


#include <string>
#include <vector>
#include <map>

class DTTTrigBaseSync;
class HMeanTimer;
class HTimeBoxes;
class TFile;
class TH1F;

class DTTimeBoxMeanTimerAnalysis {
public:
  /// Constructor
  DTTimeBoxMeanTimerAnalysis(const edm::ParameterSet& pset, TFile* file, edm::ConsumesCollector && cc);

  /// Destructor
  virtual ~DTTimeBoxMeanTimerAnalysis();

  // Operations
  void analyze(const edm::Event& event, const edm::EventSetup& setup);
  void endJob();

protected:

private:
  TFile* theFile;

  bool debug;
  // Lable of 4D segments in the event
  std::string theRecHits4DLabel;
  // Lable of 1D rechits in the event
  std::string theRecHitLabel;
  

  // Book meantimer histogram for a give sl
  void bookHistoMT(DTSuperLayerId slId);
  // Book time boxe histogram for a give sl
  void bookHistoTB(DTSuperLayerId slId);
  // Fill meantimer histogram for a give sl 
  void fillHistoMT(DTSuperLayerId slId,
		 float meantimer,
		 float ySegm,
		 float cellLenght);
  // Fill time boxe histogram for a give sl 
  void fillHistoTB(DTSuperLayerId slId,
		 float time,
		 float ySegm,
		 float cellLenght);

  std::map<DTSuperLayerId, HMeanTimer* > histoMTPerSL;
  std::map<DTSuperLayerId, HTimeBoxes* > histoTBPerSL;
 
  // Switch for t0 subtraction
  bool doSubtractT0;
  // Switch for checking of noisy channels
  bool checkNoisyChannels;
 // The module for t0 subtraction
  std::unique_ptr<DTTTrigBaseSync> theSync;

const edm::ESGetToken<DTGeometry, MuonGeometryRecord> esTokenDTGeom;
  const edm::ESGetToken<DTStatusFlag, DTStatusFlagRcd> esTokenDTStatusMap;

};
#endif

