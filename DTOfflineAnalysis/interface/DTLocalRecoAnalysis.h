#ifndef DTOfflineAnalysis_DTLocalRecoAnalysis_H
#define DTOfflineAnalysis_DTLocalRecoAnalysis_H

/*
 * \file DTLocalRecoAnalysis.h
 *
 * $Date: 2010/05/12 15:27:01 $
 * $Revision: 1.3 $
 * \author M. Zanetti & G. Cerminara - INFN Padova & Torino
 *
*/

#include <FWCore/Framework/interface/EDAnalyzer.h>


#include <string>

// #include <fstream>
// #include <vector>


class DTSegmentAnalysis;
class DTResolutionAnalysis;
class DTTreeBuilder;
class TFile;

class DTLocalRecoAnalysis: public edm::EDAnalyzer{

public:

/// Constructor
DTLocalRecoAnalysis(const edm::ParameterSet& pset);

/// Destructor
virtual ~DTLocalRecoAnalysis();

protected:

/// Analyze
void analyze(const edm::Event& event, const edm::EventSetup& setup);

// BeginJob
void beginJob();

// EndJob
void endJob();

private:
  TFile *theFile;

  // Switch for verbosity
  bool debug;
  std::string theRootFileName;

  // Classes doing the analysis
  DTSegmentAnalysis *theSegmentAnalysis;
  DTResolutionAnalysis *theResolutionAnalysis;
  DTTreeBuilder *theTreeBuilder;

  bool doSegmentAnalysis;
  bool doResolutionAnalysis;
  bool doTreeBuilder;


};

#endif
