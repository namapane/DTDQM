#ifndef MuonAnalysis_H
#define MuonAnalysis_H

/** \class MuonAnalysis
 *  Offline analysis
 *
 *  $Date: 2010/07/29 13:53:07 $
 *  $Revision: 1.2 $
 *  \author G. Cerminara - INFN Torino
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <FWCore/Framework/interface/one/EDAnalyzer.h>
#include "FWCore/Utilities/interface/InputTag.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"

#include <string>
#include <vector>
#include <map>

class TFile;

class MuonAnalysis: public edm::one::EDAnalyzer<>{
public:
  /// Constructor
  MuonAnalysis(const edm::ParameterSet& pset);

  /// Destructor
  virtual ~MuonAnalysis();

  /// book the histos
  void beginJob(const edm::EventSetup& c);

  /// Endjob
  void endJob();

  // Operations
  void analyze(const edm::Event& event, const edm::EventSetup& setup);

  double angleBtwPiAndPi(double angle) const;

protected:

private:
  // Switch for verbosity
  bool debug;

  // The label to retrieve the digis 
  edm::InputTag theDigiLabel;
  edm::InputTag theRecHitLabel;
  edm::InputTag theRecHits4DLabel;
  edm::InputTag theMuonLabel;

  std::string theFileName;
  TFile *theFile;

//   std::map<int, double> ebEnergyPerEvent;
//   std::map<int, double> numMB3DigisPerEvent;

  int nEvents;

  const edm::ESGetToken<TransientTrackBuilder, TransientTrackRecord> esTokenTTB;

};
#endif

