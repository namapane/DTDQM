  //  ----------------------------------------------------------------------

  if(false){// Debug 2D profiles
} 



  // t0
  if (false) {
    c1->cd(3);
    plotAndProfileX(hSegChamberSel->ht0PhiVsPhi,rbx,rby,1,-5, 5, -0.5, 0.5);


  }




  //------- t0seg phi, vdrift - old format
  if (false) {    
    TCanvas* c1= new TCanvas;
    c1->SetName(canvbasename+" t0 - vdrift");
    c1->SetTitle(canvbasename+" t0 - vdrift");
    c1->Divide(2,2);
    c1->cd(1);
    //    hSegChamberSel->ht0Phi->Rebin(2);
    TF1* ft0phi=drawGFit(hSegChamberSel->ht0Phi, 1, -40, 40);

    if (hSegChamberSel->ht0Theta) {  
      c1->cd(2);
      //      hSegChamberSel->ht0Theta->Rebin(2);
      TF1* ft0phi=drawGFit(hSegChamberSel->ht0Theta, 1.5, -40, 40);
    }
    
    if (hSegChamberSel->hVDrift->GetEntries() != 0){
    
      c1->cd(3);
    //    c1->SetTitle(canvbasename+"_DeltaVd");
      hSegChamberSel->hVDrift->Rebin(2);
      TF1* fDvd=drawGFit(hSegChamberSel->hVDrift, 1.5, -0.1, 0.1);

      c1->cd(4);
      plotAndProfileX(hSegChamberSel->hVDriftVsPhi,rbx,rby,1,-.1, .1, -.5, .5);
    }
  }

  // t0seg (old format)
  if (false) {
    
    TCanvas* c1= new TCanvas;
    c1->SetTitle(canvbasename+"_t0");
    c1->Divide(2,2);

    c1->cd(1);
    TF1* ft0phi=drawGFit(hSegChamberSel->ht0Phi, 1., -40, 40);

    c1->cd(2);
    plotAndProfileX(hSegChamberSel->ht0PhiVsPhi,rbx,rby,1,-10, 10, -0.5, 0.5);

    c1->cd(3);
    TF1* ft0theta=drawGFit(hSegChamberSel->ht0Theta, 1.5, -40, 40);

    t0phi = ft0phi->GetParameter("Mean");
    t0theta = ft0theta->GetParameter("Mean");

//     c1->cd(4);
//     hSegChamberSel->ht0thetaVsPhi->Draw();
  }


  //--- Angular dependencies for sigma
  if (false) {
    TCanvas* c1= new TCanvas;
    c1->SetName(canvbasename+" SigmaVsAngles");
    c1->SetTitle(canvbasename+" SigmaVsAngles");

    c1->Divide(2,2);
    c1->cd(1);
    hSegChamberSel->hPhiLoc->GetXaxis()->SetRangeUser(-1.,1.);
    hSegChamberSel->hPhiLoc->Draw();

//     c1->cd(2);
//     plotAndProfileX(hResPhi->hResDistVsAngle,rbx,rby,1,-.1, .1, -0.5, 0.5);

    double minYSigma = 0.017;
    double maxYSigma = 0.026;

    double minXSigma = -0.3;
    double maxXSigma = 0.3;

    if(detId2.wheel == 0) {
      minXSigma = -0.3;
      maxXSigma = 0.3;
    } else if(abs(detId2.wheel) == 1) {
      minXSigma = -0.75;
      maxXSigma = -0.3;
    } else if(abs(detId2.wheel) == 2) {
      minXSigma = -1.05;
      maxXSigma = -0.75;
    }

    c1->cd(2);
    // SIGMA Phi vs phi
    //    plotAndProfileX(hSegChamberSel->ht0PhiVsPhi,rbx,rby,1,-10, 10, -0.5, 0.5);
    TH1F *ht = plotAndProfileSigmaX(hResPhi->hResDistVsAngle,rbx,rby,1,0.02, 0.032, -0.5, 0.5);
    ht->GetXaxis()->SetTitle("Angle in #phi view (rad)");
    ht->GetYaxis()->SetTitle("#sigma_{x} (cm)");


    c1->cd(3);
    if (hSegChamberSel->hThetaLoc){
      //    hSegChamberSel->hThetaLoc->GetXaxis()->SetRangeUser(-1.,1.);
      hSegChamberSel->hThetaLoc->Draw();
    }
    
    c1->cd(4);
    if (hResTheta->hResDistVsAngle){
      // mean phi vs theta
      TH1F *htTheta = plotAndProfileSigmaX(hResPhi->hResDistVsTheta,rbx,rby,1,minYSigma, maxYSigma, minXSigma, maxXSigma);
      htTheta->GetXaxis()->SetTitle("Angle in #theta view (rad)");
      htTheta->GetYaxis()->SetTitle("#sigma_{x} (cm)");
    }
    

    c1->cd(6);
    // sigma phi vs theta
    //    gPad->Update();
  }




  // To test computation of ttrig
  if (false) {
    TCanvas* c1= new TCanvas;
    c1->SetTitle(canvbasename+"_PhiTheta");
    c1->Divide(2,2);
    
    c1->cd(1);
    hResPhi->hResDist->Rebin(1);
    TF1* fphi=drawGFit(hResPhi->hResDist, nsigma, -0.4, 0.4);

    c1->cd(2);
    plotAndProfileX(hResPhi->hResDistVsDist,rbx,rby,rbp,-.1, .1, 0, 2.1);

    c1->cd(3);  
    hResTheta->hResDist->Rebin(1);
    TF1* ftheta=drawGFit(hResTheta->hResDist, nsigma, -0.4, 0.4);

    c1->cd(4);  
    plotAndProfileX(hResTheta->hResDistVsDist,rbx,rby,rbp,-.1, .1, 0, 2.1);

    cout << filename
	 << " Phi: M= " << int(fphi->GetParameter("Mean")*cmToMicron)
	 << " S= "  << int(fphi->GetParameter("Sigma")*cmToMicron)
	 << "; Theta: M= " << int(ftheta->GetParameter("Mean")*cmToMicron) 
	 << " S= "  << int(ftheta->GetParameter("Sigma")*cmToMicron) <<endl;
    
    cout << " phi off "  <<  int(fphi->GetParameter("Mean")*cmToMicron)/vdrift
	 << " theta off "  <<  int(ftheta->GetParameter("Mean")*cmToMicron)/vdrift
	 << endl;
  }
  

  //--- Phi residuals binned by angle
  if (false) {
    TCanvas* c2= new TCanvas;
    c2->SetTitle(canvbasename+"_PhiByAngle");
    c2->Divide(2,3);

    c2->cd(1);
    TF1* fphi0_15=draw2GFit(hResPhi0_15->hResDist, nsigma, -0.4, 0.4);

    c2->cd(2);
    plotAndProfileX(hResPhi0_15->hResDistVsDist,  rbx,rby,rbp,-.1, .1, 0, 2.1);

    c2->cd(3);  
    TF1* fphi15_30=draw2GFit(hResPhi15_30->hResDist, nsigma, -0.4, 0.4);

    c2->cd(4);  
    plotAndProfileX(hResPhi15_30->hResDistVsDist,  rbx,rby,rbp,-.1, .1, 0, 2.1);

    c2->cd(5);  
    TF1* fphi30=draw2GFit(hResPhi30->hResDist, nsigma, -0.4, 0.4);

    c2->cd(6);  
    plotAndProfileX(hResPhi30->hResDistVsDist,  rbx,rby,rbp,-.1, .1, 0, 2.1);


  }

  


  
  // Residuals  for 2D segment
  if (false) {
    TCanvas* c1= new TCanvas;
    c1->SetTitle(canvbasename+"_PhiTheta2D");
    c1->Divide(2,2);

    c1->cd(1);
    TF1* fphi=draw2GFit(hRes2DPhi->hResDist, nsigma, -0.4, 0.4);

    c1->cd(2);
    plotAndProfileX(hRes2DPhi->hResDistVsDist, rbx,rby,rbp, -.1, .1, 0, 2.1);

     c1->cd(3);  
     TF1* ftheta=draw2GFit(hRes2DTheta->hResDist, nsigma, -0.4, 0.4);

     c1->cd(4);  
     plotAndProfileX(hRes2DTheta->hResDistVsDist, rbx,rby,rbp,-.1, .1, 0, 2.1);
  }


  // Residuals  for 2D segment, phi divided by SL
  if (false) {
    TCanvas* c2= new TCanvas;
    c2->SetTitle(canvbasename+"_Phi1Ph2_2D");
    c2->Divide(2,2);

    c2->cd(1);
    TF1* fphi1=draw2GFit(hRes2DPhi1->hResDist, nsigma, -0.4, 0.4);

    c2->cd(2);  
    plotAndProfileX(hRes2DPhi1->hResDistVsDist,  rbx,rby,rbp,-.1, .1, 0, 2.1);

    c2->cd(3);  
    TF1* fphi2=draw2GFit(hRes2DPhi2->hResDist, nsigma, -0.4, 0.4);

    c2->cd(4);  
    plotAndProfileX(hRes2DPhi2->hResDistVsDist,  rbx,rby,rbp,-.1, .1, 0, 2.1);

    cout << canvbasename
	 << " 2D Phi1: M= " << int(fphi1->GetParameter("Mean")*cmToMicron) 
	 << " Phi2: M= " << int(fphi2->GetParameter("Mean")*cmToMicron) 
	 << " delta=" << int((fphi2->GetParameter("Mean") - fphi1->GetParameter("Mean"))*cmToMicron) << endl;

  }

  // Phi, Step 1 and Step 2
  if (doPhiBySLS1AndS3) {
    TCanvas* c2= new TCanvas;
    c2->SetTitle(canvbasename+"_PhiS1S2");
    c2->Divide(2,2);

    c2->cd(1);
    TF1* fphiS1=draw2GFit(hResPhiS1->hResDist, nsigma, -0.4, 0.4);

    c2->cd(2);  
    plotAndProfileX(hResPhiS1->hResDistVsDist,  rbx,rby,rbp,-.1, .1, 0, 2.1);

    c2->cd(3);  
    TF1* fphiS2=draw2GFit(hResPhiS2->hResDist, nsigma, -0.4, 0.4);

    c2->cd(4);  
    plotAndProfileX(hResPhiS2->hResDistVsDist,  rbx,rby,rbp,-.1, .1, 0, 2.1);

    m_phiS1 = fphiS1->GetParameter("Mean")*cmToMicron;
    m_phiS2 = fphiS2->GetParameter("Mean")*cmToMicron;
    s_phiS1 = fphiS1->GetParameter("Sigma")*cmToMicron;
    s_phiS2 = fphiS2->GetParameter("Sigma")*cmToMicron;

  }
  
  // Theta, S1 and S2
  if (false) {
    TCanvas* c2= new TCanvas;
    c2->SetTitle(canvbasename+"_ThetaS1S2");
    c2->Divide(2,2);

    c2->cd(1);
    TF1* fthetaS1=draw2GFit(hResThetaS1->hResDist, nsigma, -0.4, 0.4);

    c2->cd(2);  
    plotAndProfileX(hResThetaS1->hResDistVsDist,  rbx,rby,rbp,-.1, .1, 0, 2.1);

    c2->cd(3);  
    TF1* fthetaS2=draw2GFit(hResThetaS2->hResDist, nsigma, -0.4, 0.4);

    c2->cd(4);  
    plotAndProfileX(hResThetaS2->hResDistVsDist,  rbx,rby,rbp,-.1, .1, 0, 2.1);

    m_thetaS1 = fthetaS1->GetParameter("Mean")*cmToMicron;
    m_thetaS2 = fthetaS2->GetParameter("Mean")*cmToMicron;
    s_thetaS1 = fthetaS1->GetParameter("Sigma")*cmToMicron;
    s_thetaS2 = fthetaS2->GetParameter("Sigma")*cmToMicron;

  }



  //  return;
  
  //  ----------------------------------------------------------------------

  

  // Phi/theta vs X and Y, S1
  if (false) {
    TCanvas* c2= new TCanvas;
    c2->SetTitle(canvbasename+"_PhiThetaS1vsXY");
    c2->Divide(2,2);

    c2->cd(1);
    plotAndProfileX(hResPhiS1->hResDistVsX,  rbx,rby,2,-.1, .1, -130,130);

    c2->cd(2);  
    plotAndProfileX(hResPhiS1->hResDistVsY,  rbx,rby,2,-.1, .1, -130,130);

    c2->cd(3);  
    plotAndProfileX(hResThetaS1->hResDistVsX,  rbx,rby,2,-.1, .1, -130,130);

    c2->cd(4);  
    plotAndProfileX(hResThetaS1->hResDistVsY,  rbx,rby,2,-.1, .1, -130,130);

  }  

  if(false) {
    TCanvas* c2= new TCanvas(canvbasename+"_PhiThetaS1vsXY",canvbasename+"_PhiThetaS1vsXY");
    c2->SetName(canvbasename+"_PhiThetaS1vsXY (TALK)");

    c2->SetTitle(canvbasename+"_PhiThetaS1vsXY (TALK)");
    c2->Divide(1,2);

    c2->cd(1);
    plotAndProfileX(hResPhiS1->hResDistVsY,  rbx,rby,2,-.1, .1, -130,130);

    c2->cd(2);
    plotAndProfileX(hResThetaS1->hResDistVsY,  rbx,rby,2,-.1, .1, -130,130);

  }





  
  //Theta vs Y
  if (false) {
    TCanvas* c2= new TCanvas;
    c2->SetTitle(canvbasename+"_ThetavsXY");

    plotAndProfileX(hResTheta->hResDistVsY,  rbx,rby,2,-.2, .2, -130,130);

  }


  // Phi/theta vs Y, S2 vs s3 (duplicate, rearrangement of the above)
  if (false) {
    TCanvas* c2= new TCanvas;
    c2->SetTitle(canvbasename+"_PhiThetaS2vsXY");
    c2->Divide(2,2);

    c2->cd(1);
    plotAndProfileX(hResPhiS2->hResDistVsY,  rbx,rby,2,-.1, .1);

    c2->cd(2);  
    plotAndProfileX(hResPhi->hResDistVsY,  rbx,rby,2,-.1, .1);

    c2->cd(3);  
    plotAndProfileX(hResThetaS2->hResDistVsY,  rbx,rby,2,-.1, .1);

    c2->cd(4);  
    plotAndProfileX(hResTheta->hResDistVsY,  rbx,rby,2,-.1, .1);
  }


  // Difference between S2 and S3
  if (false) {
    TCanvas* c2= new TCanvas;
    c2->SetTitle(canvbasename);
    c2->Divide(2,2);

    c2->cd(1);
    TF1* fphi1=draw2GFit(hResPhidS3S2->hResDist, nsigma, -0.4, 0.4);

    c2->cd(2);  
    plotAndProfileX(hResPhidS3S2->hResDistVsDist,  1,1,1,-.1, .1, 0, 2.1);

    c2->cd(3);  
    TF1* fphi2=draw2GFit(hResThetadS3S2->hResDist, nsigma, -0.4, 0.4);

    c2->cd(4);  
    plotAndProfileX(hResThetadS3S2->hResDistVsDist,  1,1,1,-.1, .1, 0, 2.1);
    
  }
  

  //  Difference between S2 and S3, vs X and Y
  if (false) {
    TCanvas* c2= new TCanvas;
    c2->SetTitle(canvbasename);
    c2->Divide(2,2);

    c2->cd(1);
    plotAndProfileX(hResPhidS3S2->hResDistVsX,  1,1,1,-.1, .1);

    c2->cd(2);  
    plotAndProfileX(hResPhidS3S2->hResDistVsY,  1,1,1,-.1, .1);

    c2->cd(3);  
    plotAndProfileX(hResThetadS3S2->hResDistVsX,  1,1,1,-.1, .1);

    c2->cd(4);  
    plotAndProfileX(hResThetadS3S2->hResDistVsY,  1,1,1,-.1, .1);
  }

  //  Difference between S2 and S3 for phi1 and phi2, vs X and Y
  if (false) {
    TCanvas* c2= new TCanvas;
    c2->SetTitle(canvbasename);
    c2->Divide(2,2);

    c2->cd(1);
    plotAndProfileX(hResPhi1dS3S2->hResDistVsX,  1,1,1,-.1, .1);

    c2->cd(2);  
    plotAndProfileX(hResPhi1dS3S2->hResDistVsY,  1,1,1,-.1, .1);

    c2->cd(3);  
    plotAndProfileX(hResPhi2dS3S2->hResDistVsX,  1,1,1,-.1, .1);

    c2->cd(4);  
    plotAndProfileX(hResPhi2dS3S2->hResDistVsY,  1,1,1,-.1, .1);
  }

