//------------------------------
//
// Write table of ttrigs
//
// run: 
// .x writeTTrigTable.r
//
//
//------------------------------

#include <TH1F.h>
#include <TH2F.h>
#include <TF1.h>
#include <TLine.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <TFile.h>
#include <TColor.h>
#include <iostream>
#include <fstream>

using namespace std;

#include "DQM/DTOfflineAnalysis/test/root_lib/Utils.h"
#include "macros2.C"
#include "DQM/DTOfflineAnalysis/test/root_lib/Histograms.h"
#include "DQM/DTOfflineAnalysis/test/root_lib/DTDetId.h"

#include <iomanip>

void plotAll() {
  // Configurable parameters --------------------


  float cmToMicron = 10000.;
  float vdrift = 54.3;
  float sigmafit = 2;
  TString granularity = "stat";    // collapse sectors; for statBy*
  //  TString granularity = "SL";  // sectors independently

//   TString filename = "ZMu_2012DpromptTest_statByView.root";
//   TString table = "ttrig_test_statByView.txt";

 
//   TString filename = "ZMu_2012D_22jan13_statByView.root";
//   TString table = "ttrig_ZMu_2012D_22jan13_statByView.txt";


//    TString filename = "ZMu_2012D_22jan13_statByView.root";
//    TString table = "ttrig_ZMu_2012D_22jan13_statByView.txt";

//     TString filename = "ZMu_2012D_22jan13_SL.root";
//     TString table = "ttrig_ZMu_2012D_22jan13_SL.txt";

//  TString filename = "ZMu_2012D_22jan13_statByLayer.root";
  //  TString table = "ttrig_ZMu_2012D_22jan13_statByLayer.txt";

  TString filename =    "ZMu_2015D_ttrig_residuals_256675_15GeV_statByView.root";
  TString table = "ttrig_ZMu_2015D_ttrig_residuals_256675_15GeV_statByView.txt";

//   TString filename = "ZMu_2012D_22jan13_noDRR_statByView.root";
//   TString table = "ttrig_ZMu_2012D_22jan13_noDRR_statByView.txt";

//    TString filename = "ZMu_2012D_22jan13_noDRR_SL.root";
//    TString table = "ttrig_ZMu_2012D_22jan13_noDRR_SL.txt";

//   TString filename = "DYJetsToLL_M-50_53X_STD_statByView.root";
//   TString table = "ttrig_DYJetsToLL_M-50_53X_STD_statByView.txt";

//   TString filename = "DYJetsToLL_M-50_53X_STD_SL.root";
//   TString table = "ttrig_DYJetsToLL_M-50_53X_STD_SL.txt";

//   TString filename = "DYJetsToLL_M-50_53X_IDEAL_noDRR_statByView.root";
//   TString table = "ttrig_DYJetsToLL_M-50_53X_IDEAL_noDRR_statByView.txt";

//   TString filename = "DYJetsToLL_M-50_53X_IDEAL_noDRR_SL.root";
//   TString table = "ttrig_DYJetsToLL_M-50_53X_IDEAL_noDRR_SL.txt";


  TString tablet0seg = "";

  //--------------------

  ofstream f(table,ios_base::out);
  ofstream* ft0seg =0;
  if (tablet0seg!="") ft0seg = new ofstream(tablet0seg,ios_base::out);


//   f.precision(1);
//   f << fixed;

  TFile *file = new TFile(filename);

  int smin = 0;
  int smax = 0;
  if (granularity=="SL") {
    smin = 1;
    smax = 14;  
  } else if (granularity=="stat"){
    smin = 0;
    smax = 0;
  }

  for (int wheel = -2; wheel<3; ++wheel) {
    for (int station =1; station<=4; ++station) {	  
      for (int sector = smin; sector<=smax; ++sector) {

	if (station!=4 && sector>12) continue;

	DTDetId detId1(wheel, station, sector, 1, 0, 0);
	DTDetId detId2(wheel, station, sector, 2, 0, 0);
	DTDetId detId3(wheel, station, sector, 3, 0, 0);


	HRes1DHits *hResPhi1 = new HRes1DHits(Utils::getHistoNameFromDetIdAndSet(detId1, "Cut1"),file);

	HRes1DHits *hResTheta = new HRes1DHits(Utils::getHistoNameFromDetIdAndSet(detId2, "Cut1"),file);

	HRes1DHits *hResPhi2 = new HRes1DHits(Utils::getHistoNameFromDetIdAndSet(detId3, "Cut1"),file);


	DTDetId chDetId(wheel, station, sector, 0, 0, 0);
	HSegment*   hSegChamberSel = new HSegment(Utils::getHistoNameFromDetIdAndSet(chDetId, "Cut1"),file);



	TCanvas c;


	float ttrig1 =0.;
	float ttrig2 =0.;
	float ttrig3 =0.;
	float mt0Phi =0;
	float mt0Theta =0;

 	TF1* fphi1=drawGFit(hResPhi1->hResDist, sigmafit, -0.4, 0.4);
	ttrig1=fphi1->GetParameter("Mean")*cmToMicron/vdrift;

	if (hResPhi2->hResDist->GetEntries()) {
	  TF1* fphi2=drawGFit(hResPhi2->hResDist, sigmafit, -0.4, 0.4);
	  ttrig3=fphi2->GetParameter("Mean")*cmToMicron/vdrift;
	} else {
	  ttrig3=ttrig1;
	}


	//	hSegChamberSel->ht0Phi->Rebin(rebin);
// 	TF1* ft0Phi=drawGFit(hSegChamberSel->ht0Phi, 1.5, -40, 40);
// 	mt0Phi = ft0Phi->GetParameter("Mean");

	
	if (station !=4) {
	  //	  hResTheta->hResDist->Rebin(2);
	  TF1* ftheta=drawGFit(hResTheta->hResDist, sigmafit, -0.4, 0.4);
	  ttrig2=ftheta->GetParameter("Mean")*cmToMicron/vdrift;


// 	  TF1* ft0Theta=drawGFit(hSegChamberSel->ht0Theta, 1.5, -40, 40);
// 	  mt0Theta = ft0Theta->GetParameter("Mean");
	}
	

	cout.precision(1);
	cout << fixed;
	cout << filename
	     << " " << wheel << " " << station << " " << sector 
	     << " " <<  ttrig1;
	if (station !=4) cout << " " <<  ttrig2;
	cout << " " <<  ttrig3;
	cout << endl;

	int secmin=1;
	int secmax=14;

	if (sector != 0){ // for granularity = station
	  secmin=sector;
	  secmax=sector;
	}

	for (int sec = secmin; sec<=secmax; sec++) {
	  if (station!=4 && sec>12) continue;
	  writeTTrigTable(f,wheel,station,sec,1, ttrig1);
	  if (ft0seg) writeTTrigTable(*ft0seg,wheel,station,sec,1, mt0Phi);	    
	  if (station!=4) {
	    writeTTrigTable(f,wheel,station,sec,2, ttrig2);
	    if (ft0seg) writeTTrigTable(*ft0seg,wheel,station,sec,2, mt0Theta);
	  }
	  writeTTrigTable(f,wheel,station,sec,3, ttrig3);
	  if (ft0seg) writeTTrigTable(*ft0seg,wheel,station,sec,3, mt0Phi);	    
	}
      }
    }
  }
  delete ft0seg;
}

