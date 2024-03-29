
/*
 * Plot residuals for all 12 sectors of a given W,St,Sl,l
 */

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



void plot12s(TString filename, int wheel, int station, int sl, int layer=0) {
 
  //  TStyle * style = getStyle("myStyle");
  TStyle * style = getStyle("tdr");
  style->cd();  
  gStyle->SetPalette(5);
  gStyle->SetStatFormat("4.3g");
  gStyle->SetFitFormat("4.3g");
    opt2Dplot = "col";
    //opt2Dplot = "";

  TFile *file = new TFile(filename);

  gStyle->SetStatFormat("2.1g");

  HRes1DHits* hResTheta[13];
  for (int sector = 1; sector<=12; ++sector) {
    DTDetId detId2(wheel, station, sector, sl, layer, 0);
    hResTheta[sector] = new HRes1DHits(Utils::getHistoNameFromDetIdAndSet(detId2, "Cut1"),file);
  }
  

  float nsigma = 2;

  
  TString name = filename+"_W"+wheel+"_St"+station+"_SL"+sl;
  TCanvas* c1= new TCanvas(name,name,1100,800);
  c1->Divide(4,3);
  

  for (int sector = 1; sector<=12; ++sector) {  
    c1->cd(sector);
    hResTheta[sector]->hResDist->Rebin(2);
    //    hResTheta[sector]->hResDist->SetTitle("");
    TF1* fphi=drawGFit(hResTheta[sector]->hResDist, nsigma, -0.3, 0.3);
    cout << "sector " << sector 
	 << " mean=" << fphi->GetParameter("Mean")*1e4
	 << " sigma=" << fphi->GetParameter("Sigma")*1e4 << endl;
 
  }
}
