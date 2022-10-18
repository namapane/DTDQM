#ifndef DQM_DTTimeBoxAnalysis_H
#define DQM_DTTimeBoxAnalysis_H

/** \class DTTimeBoxAnalysis
 *  Analyzer class which fills time box plots with SL granularity
 *  for t_trig computation, fits the rising edge and write results to DB.
 *  The time boxes are written to file.
 *
 *  $Date: 2008/12/03 10:41:13 $
 *  $Revision: 1.1 $
 *  \author G. Cerminara - INFN Torino
 */

#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "DataFormats/MuonDetId/interface/DTSuperLayerId.h"
#include "DataFormats/MuonDetId/interface/DTLayerId.h"
#include "FWCore/Framework/interface/ConsumesCollector.h"


#include <string>
#include <map>
#include <vector>

namespace edm {
  class ParameterSet;
  class Event;
  class EventSetup;
}

class TFile;
class TH1F;
class DTTimeBoxFitter;
class DTTTrigBaseSync;
class DTTtrig;

class DTTimeBoxAnalysis{
public:
  /// Constructor
  DTTimeBoxAnalysis(const edm::ParameterSet& pset, TFile* file, edm::ConsumesCollector && cc);

  /// Destructor
  virtual ~DTTimeBoxAnalysis();

  // Operations

  /// Fill the time boxes
  void analyze(const edm::Event & event, const edm::EventSetup& eventSetup);

  /// Fit the time box rising edge and write the resulting ttrig to the DB
  void endJob();


protected:

private:
  // Generate the time box name
  std::string getTBoxName(const DTSuperLayerId& slId) const;
  // Generate the time box name
  std::string getOccupancyName(const DTLayerId& slId) const;

  // Debug flag
  bool debug;

  // The label used to retrieve digis from the event
  std::string digiLabel;

  // The file which will contain the time boxes
  TFile *theFile;
  
  // Map of the histograms by SL
  std::map<DTSuperLayerId, std::vector<TH1F*> > theHistoMap;
  std::map<DTLayerId, TH1F*> theOccupancyMap;

  // Switch for t0 subtraction
  bool doSubtractT0;
  // Switch for checking of noisy channels
  bool checkNoisyChannels;
  // The fitter
  DTTimeBoxFitter *theFitter;
  // The module for t0 subtraction
  std::unique_ptr<DTTTrigBaseSync> theSync;

};
#endif

