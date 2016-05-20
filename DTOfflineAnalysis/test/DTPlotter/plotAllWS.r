/*
 * Plot 5x4 (WxSt) tables of various quantities
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
#include "ranges.C"
#include "summaryPlot.C"

//Works since root 6.04; the lib must be loaded by hand or with rootlogon.C in previous versions
R__LOAD_LIBRARY(libDTOfflineAnalysisEvent) 


void plotAllWS(TString filename, int sector, int sl) {

  bool doRes = true;
  bool doResVsDist = true;
  bool doResVsAngle = true;
  bool doResVsX = true;
  bool doResVsY = true;
  bool doAngleDist = false;
  bool doVD = true;
   
  float nsigma = 2;
   
  TStyle * style = getStyle("tdr");
  style->cd();  

  gStyle->SetCanvasDefW(1375); // Set larger canvas
  gStyle->SetCanvasDefH(800);  
  gStyle->SetTitleSize(0.05,"XYZ"); // Set larger axis titles
  gStyle->SetTitleOffset(1.5,"Y");
  gStyle->SetOptTitle(0); // remove histogram titles

  setPalette();
  opt2Dplot = "col";

  TFile *file = new TFile(filename);
   
   
  TString canvbasename = filename;
  canvbasename = canvbasename.Replace(canvbasename.Length()-5,5,"") + TString("_Se") + (long) sector + "_SL" + (long) sl;
   
   
  HRes1DHits* hRes[5][4]; // W, S;  
  HSegment*   hSeg[5][4];
  //HSegment*   hSeg;
   
  for (int wheel = -2; wheel<=2; ++wheel) {
    for (int station = 1; station<=4; ++station) {
      int iW = wheel+2;
      int iSt= station-1;
      DTDetId detId2(wheel, station, sector, sl, 0, 0); 
      DTDetId chDetId(wheel, station, sector, 0, 0, 0);
      hRes[iW][iSt] = new HRes1DHits(Utils::getHistoNameFromDetIdAndSet(detId2, "Cut1"),file);
      hSeg[iW][iSt] = new HSegment(Utils::getHistoNameFromDetIdAndSet(chDetId, "Cut1"),file);
       
    }
  }
   
  if(doRes){
    TCanvas* c0= new TCanvas(canvbasename+"_AllWSRes", canvbasename+"_AllWSRes");    
    
    c0->Divide(5,4,0.0005,0.0005);

   
    for (int wheel = -2; wheel<=2; ++wheel) {
      for (int station = 1; station<=4; ++station) {
	int iW = wheel+2;
	int iSt= station-1;
	// DTDetId detId(wheel, station, sector, sl, 0, 0);

	if(sl==2 && station ==4) continue;

	int ipad=iW+1 + (3-iSt)*5;
	c0->cd(ipad); ++ipad;

	float min;
	float max;

	DTDetId chDetId(wheel, station, sector, sl, 0, 0);
	rangeAngle(chDetId, min, max);
	//  cout << "min" << min << endl;
	//        cout << "max" << max << endl;

	TH1F* h = hRes[iW][iSt]->hResDist;
       
	//    if(sl==2){
	// 	 TH1F* hAlpha = hSeg[iW][iSt]->hThetaLoc;
	//        }

	TF1* fres=drawGFit(h, nsigma, -0.4, 0.4);
       
	//h->GetXaxis()->SetRangeUser(-0.4,0.4);
	// h->Draw();

      }
    }
  }
  

  if (doResVsDist) {
    TCanvas* c1= new TCanvas(canvbasename+"_AllWSResVsDist", canvbasename+"_AllWSResVsDists");    
    c1->Divide(5,4,0.0005,0.0005);


    for (int wheel = -2; wheel<=2; ++wheel) {
      for (int station = 1; station<=4; ++station) {
	int iW = wheel+2;
	int iSt= station-1;
	if(sl==2 && station ==4) continue;
	int ipad=iW+1 + (3-iSt)*5;
	c1->cd(ipad); ++ipad;
	plotAndProfileX(hRes[iW][iSt]->hResDistVsDist,1,1,1,-.1, .1, 0, 2.1);
      }
    }
  }
  

  if (doResVsAngle) {
    SummaryPlot hs_p0("p0");
    SummaryPlot hs_p1("p1");

    TCanvas* c2= new TCanvas(canvbasename+"_AllWSResVsAngle", canvbasename+"_AllWSResVsAngle");
    
    c2->Divide(5,4,0.0005,0.0005);

    
    for (int wheel = -2; wheel<=2; ++wheel) {
      for (int station = 1; station<=4; ++station) {
	int iW = wheel+2;
	int iSt= station-1;
	if(sl==2 && station ==4) continue;
	int ipad=iW+1 + (3-iSt)*5;
	c2->cd(ipad); ++ipad;

	float min, max;
	DTDetId chDetId(wheel, station, sector, sl, 0, 0);
	rangeAngle(chDetId, min, max);
	TH1F* hprof = plotAndProfileX(hRes[iW][iSt]->hResDistVsAngle,1,1,1,-0.04,0.04,min-0.03,max+0.03);
	
	//	if (wheel==0&&station==1) {
	//	  cout << hprof->GetName() << endl;
       	TF1 *angleDep= new TF1("angleDep","[0]*cos(x+[2])+[1]", min, max);

	//TF1 *angleDep= new TF1("angleDep","[0]*x*x+[2]*x+[1]", min, max);
	//	angleDep->SetParLimits(2,-0.1,+0.1);

	angleDep->SetParameters(0.01,0.001,0.1);
 	
	if(sl == 2 || (sl == 1 && (iSt!=0 ||(iSt==0 && iW==2))))  angleDep->FixParameter(2,0.);

	if(sl == 1 && (iW == 3 ||iW == 0) && iSt == 0)  angleDep->SetParameter(2,-0.12);
	
	hprof->Fit(angleDep,"RQNB"); 
     
 	if(sl == 2 && (iW == 0 || iW == 4) && (iSt == 0 || iSt == 1)) continue;



	angleDep->Draw("same");
	float p0 = angleDep->GetParameter(0);
	float p1 = angleDep->GetParameter(1);	
	float p2 = angleDep->GetParameter(2);
	
	// 	  cout << "p0 = " << p0 << endl;
	// 	  cout << "p1 = " << p1 << endl;
	
	hs_p0.Fill(wheel, station, sector, p0);
	hs_p1.Fill(wheel, station, sector, p1);
	
	cout << chDetId << " " << p0 << " " << p1 << " " << p2 << endl;
	
	//}
      }
    }

    // Summary plot (still being developed)
    if (false) {
      TCanvas* c6= new TCanvas(canvbasename+"_AllWSAngleCorr_p0", canvbasename+"_AllWSAngleCorr_p0");    
      hs_p0.hsumm->GetYaxis()->SetRangeUser(0.,0.5);
      hs_p0.hsumm->Draw("p");

      float p0_m[3][3];
      float p1_m[3][3];
    
      for (int wheel = 0; wheel<=2; ++wheel) {
	for (int station = 1; station<=3; ++station) {

	  float p0_n = hs_p0.hsumm->GetBinContent(hs_p0.bin(-wheel,station,0));
	  float p0_p = hs_p0.hsumm->GetBinContent(hs_p0.bin(wheel,station,0));
	  float p1_n = hs_p1.hsumm->GetBinContent(hs_p1.bin(-wheel,station,0));
	  float p1_p = hs_p1.hsumm->GetBinContent(hs_p1.bin(wheel,station,0));
	  p0_m[wheel][station] = (p0_n + p0_p)/2;
	  p1_m[wheel][station] = (p1_n + p1_p)/2;
	  cout << wheel << "   "   << station << "   " <<  p0_m[wheel][station] <<  "   "<<p1_m[wheel][station] <<endl;
	}
      }
    }
  }
    
  if (doResVsX) {
    TCanvas* c3=new TCanvas(canvbasename+"_AllWSResVsX", canvbasename+"_AllWSResVsX");    
    
    c3->Divide(5,4,0.0005,0.0005);

    for (int wheel = -2; wheel<=2; ++wheel) {
      for (int station = 1; station<=4; ++station) {
	int iW = wheel+2;
	int iSt= station-1;
	if(sl==2 && station ==4) continue;
	int ipad=iW+1 + (3-iSt)*5;
	c3->cd(ipad); ++ipad;
	plotAndProfileX(hRes[iW][iSt]->hResDistVsX,1,1,1,-0.04, 0.04, -150, 150); // FIXME
      }
    }
  }

  if (doResVsY) {

    TCanvas* c4=new TCanvas(canvbasename+"_AllWSResVsY", canvbasename+"_AllWSResVsY");    
     
    c4->Divide(5,4,0.0005,0.0005);

    for (int wheel = -2; wheel<=2; ++wheel) {
      for (int station = 1; station<=3; ++station) {//no Y for St4
	int iW = wheel+2;
	int iSt= station-1;
	if(sl==2 && station ==4) continue;
	int ipad=iW+1 + (3-iSt)*5;
	c4->cd(ipad); ++ipad;
	plotAndProfileX(hRes[iW][iSt]->hResDistVsY,1,1,1,-0.04, 0.04, -150, 150); // FIXME
      }
    }
  }

  if(doAngleDist){
    TCanvas* c5= new TCanvas(canvbasename+"_AllWSAngleDist", canvbasename+"_AllWSAngleDist");
   
    c5->Divide(5,4,0.0005,0.0005);
   
    for (int wheel = -2; wheel<=2; ++wheel) {
      for (int station = 1; station<=4; ++station) {
	int iW = wheel+2;
	int iSt= station-1;
	if(sl==2 && station ==4) continue;
	// DTDetId detId(wheel, station, sector, sl, 0, 0);
	int ipad=iW+1 + (3-iSt)*5;
	c5->cd(ipad); ++ipad;

	float min;
	float max;

	DTDetId chDetId(wheel, station, sector, sl, 0, 0);
	rangeAngle(chDetId, min, max);
	//  cout << "min" << min << endl;
	//        cout << "max" << max << endl;

	TH1F* hAlpha = hSeg[iW][iSt]->hPhiLoc;
       
	if(sl==2){
	  TH1F* hAlpha = hSeg[iW][iSt]->hThetaLoc;
	}

   
       
	hAlpha->GetXaxis()->SetRangeUser(-1.2,1.2);
	hAlpha->Draw();

      }
    }
  }


  if(doVD && sl!=2){
    TCanvas* c0= new TCanvas(canvbasename+"_AllWSVd", canvbasename+"_AllWSVd");    
    
    c0->Divide(5,4,0.0005,0.0005);

    for (int wheel = -2; wheel<=2; ++wheel) {
      for (int station = 1; station<=4; ++station) {
	int iW = wheel+2;
	int iSt= station-1;

	if(sl==2 && station ==4) continue;

	int ipad=iW+1 + (3-iSt)*5;
	c0->cd(ipad); ++ipad;

	plotAndProfileX(hSeg[iW][iSt]->hdVDriftVsY,2,1,1,-0.03,0.03, -130., 130.);

      }
    }
  }

}
