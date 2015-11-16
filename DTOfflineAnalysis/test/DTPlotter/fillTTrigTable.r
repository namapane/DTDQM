//------------------------------
//
// Write table of ttrigs
//
// run:  
// root -q -b 'fillTTrigTable.r("ZMu_2015Dv4_ttrig_256675_vDrift_259626_SL.root")'
//
// or
// root -q -b 'fillTTrigTable.r("ZMu_2015Dv4_ttrig_256675_vDrift_259626_statByView.root", "stat")'
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

float filter(float offset);


// set granularity="SL" for "SL" or "ChamberBy*";  granularity="stat" for statBy*"
void fillTTrigTable(TString filename, TString granularity = "SL") {

  // Configurable parameters --------------------
  float vdrift = 54.3/10000.; // in cm/ns

  float conversion = 1.; // output offsets in cm
  //  float conversion = vdrift; // output offsets in ns (approxymately; deprecated)

  float sigmafit = 2;

  TString table = "ttrig_"+filename;
  table.ReplaceAll(".root",".txt");

  TString tablet0seg = "";

  //--------------------

  ofstream f(table,ios_base::out);
  ofstream* ft0seg =0;
  if (tablet0seg!="") ft0seg = new ofstream(tablet0seg,ios_base::out);

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
	float ttrig2Mean=0;

 	TF1* fphi1=drawGFit(hResPhi1->hResDist, sigmafit, -1, 1);
	ttrig1=fphi1->GetParameter("Mean")/conversion;

	if (hResPhi2->hResDist->GetEntries()) {
	  TF1* fphi2=drawGFit(hResPhi2->hResDist, sigmafit, -1, 1);
	  ttrig3=fphi2->GetParameter("Mean")/conversion;
	} else {
	  ttrig3=ttrig1;
	}
	
	if (station !=4) {
	  //	  hResTheta->hResDist->Rebin(2);
	  TF1* ftheta=drawGFit(hResTheta->hResDist, sigmafit, -1, 1);
	  ttrig2=ftheta->GetParameter("Mean")/conversion;
	  ttrig2Mean = hResTheta->hResDist->GetMean()/conversion;
	  float diff = std::abs(ttrig2-ttrig2Mean);
	  if (diff>0.05/conversion && std::abs(diff/ttrig2)>0.1) { // >50 micron, or 10%
 	    cout << "FIT FAILURE? " << ttrig2 << " " << ttrig2Mean << endl;
 	  }
	}
	

// 	cout.precision(1);
// 	cout << fixed;

//	if (std::abs(filter(ttrig1)) > 0 ) {	  
	cout << filename
	     << " " << wheel << " " << station << " " << sector 
	     << " " <<  ttrig1;
	if (station !=4) cout << " " <<  ttrig2;
	cout << " " <<  ttrig3;
	cout << endl;
//	}
	int secmin=1;
	int secmax=14;

	if (sector != 0){ // for granularity = station
	  secmin=sector;
	  secmax=sector;
	}

	for (int sec = secmin; sec<=secmax; sec++) {
	  if (station!=4 && sec>12) continue;
	  writeTTrigTable(f,wheel,station,sec,1, filter(ttrig1));
	  if (ft0seg) writeTTrigTable(*ft0seg,wheel,station,sec,1, mt0Phi);	    
	  if (station!=4) {
	    writeTTrigTable(f,wheel,station,sec,2, filter(ttrig2));
	    //	    writeTTrigTable(f,wheel,station,sec,2, filter(ttrig1)); //FIXME impose phi offset to theta 
	    if (ft0seg) writeTTrigTable(*ft0seg,wheel,station,sec,2, mt0Theta);
	  }
	  writeTTrigTable(f,wheel,station,sec,3, filter(ttrig3));
	  if (ft0seg) writeTTrigTable(*ft0seg,wheel,station,sec,3, mt0Phi);
	}
      }
    }
  }
  delete ft0seg;

  cout << endl << "Wrote " << table << endl << endl;
}


// Used to filter offsers (ie set zero those below threshold)
float filter(float offset) {
//   const float filter = 40/10000.; // 50 micron, assuming offset in cm
//   if (std::abs(offset)<filter) return 0.;
  return offset;
}
