
/*
 *  See header file for a description of this class.
 *
 *  $Date: 2013/11/12 17:23:14 $
 *  $Revision: 1.25 $
 *  \author G. Cerminara - INFN Torino
 */

#include "DTTreeBuilder.h"
#include "DTSegmentObject.h"
#include "DTHitObject.h"
#include "DTMuObject.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/ESHandle.h"
// #include "Geometry/Vector/interface/Pi.h"

//Hack to be able to call DTRecSegment2D::update and DTRecSegment4D::phiSegment
#define protected public
#include "DataFormats/DTRecHit/interface/DTRecSegment2D.h"
#undef protected
#define private public
#include "DataFormats/DTRecHit/interface/DTRecSegment4D.h"
#undef private
#include "RecoLocalMuon/DTSegment/src/DTSegmentUpdator.h"

#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecHitCollection.h"

#include "RecoLocalMuon/DTRecHit/interface/DTRecHitAlgoFactory.h"

#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "TrackingTools/GeomPropagators/interface/StraightLinePlaneCrossing.h"

#include "CondFormats/DataRecord/interface/DTStatusFlagRcd.h"
#include "CondFormats/DTObjects/interface/DTStatusFlag.h"
#include <CondFormats/DTObjects/interface/DTTtrig.h>
#include <CondFormats/DataRecord/interface/DTTtrigRcd.h>
#include "CondFormats/DTObjects/interface/DTT0.h"
#include "CondFormats/DataRecord/interface/DTT0Rcd.h"
#include "CondFormats/DataRecord/interface/DTMtimeRcd.h"
#include "CondFormats/DTObjects/interface/DTMtime.h"

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/VertexReco/interface/Vertex.h"

#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"

#include <iterator>
#include <vector>

#include "TFile.h"
#include "TMath.h"
#include "TTree.h"
#include "TClonesArray.h"


using namespace edm;
using namespace std;
using namespace reco;

// Refit the segment used as a reference for computing residuals, possibly skipping hits
// NOTE: at the moment the refitted segment is used only as the reference to compute residuals.
//       All other quantities (angles, segment X, Y etc) used to plot dependencies come from the original segment.
bool refitReferenceSegment = false;


DTTreeBuilder::DTTreeBuilder(const ParameterSet& pset, TFile* file) : 
  theFile(file),
  BX(-999),
  runN(-1),
  eventN(-1),
  theUpdator(0)
{
  debug = pset.getUntrackedParameter<bool>("debug","false");
  // the name of the 4D rec hits collection
  theRecHits4DLabel = pset.getParameter<string>("recHits4DLabel");
  theRecHits2DLabel = pset.getParameter<string>("recHits2DLabel");
  theRecHitLabel = pset.getParameter<string>("recHitLabel");
  theMuonLabel = pset.getParameter<string>("muonLabel");

  checkNoisyChannels = pset.getUntrackedParameter<bool>("checkNoisyChannels","false");
  algoName = pset.getParameter<string>("recAlgo");
  theAlgo = DTRecHitAlgoFactory::get()->create(algoName,pset.getParameter<ParameterSet>("recAlgoConfig"));

  if (refitReferenceSegment) { 
  // updator to refit the segment used as a reference to define residuals
    theUpdator = new DTSegmentUpdator(pset.getParameter<ParameterSet>("segmentUpdatorConfig"));

    // Fill List of layers to be excluded from the segment refit (suspect alignment ouliers) 
    // when refitReferenceSegment == true
    
    //Clear Single-layer misalignments
    skipLayersFromReference.insert(DTLayerId(-1,1,6,3,4));
    skipLayersFromReference.insert(DTLayerId( 0,1,2,3,1));
    skipLayersFromReference.insert(DTLayerId( 2,4,1,3,1));

    //Clear 2-layer misalignments
    skipLayersFromReference.insert(DTLayerId( 2,4,3,3,2));
    skipLayersFromReference.insert(DTLayerId( 2,4,3,1,4));
    skipLayersFromReference.insert(DTLayerId( 2,4,2,3,2));
    skipLayersFromReference.insert(DTLayerId( 2,4,2,1,3));

    //Reasonable candidates as single-layer misaligment
    skipLayersFromReference.insert(DTLayerId(-1,3,9,1,1)); 
    skipLayersFromReference.insert(DTLayerId( 1,4,2,3,2)); //huge, residual distances ~125micron, but cannot be pattern

    //Problematic misalignments
    skipLayersFromReference.insert(DTLayerId(-1,4,3,3,1)); // could hide pattern, but is anyhow too large (321) to be only a pattern. Has pattern in other SL.
    skipLayersFromReference.insert(DTLayerId(2,4,5,3,1)); // SL1;L2-3 cannot be a pattern. Also SL3;L1 is off
    skipLayersFromReference.insert(DTLayerId(2,4,5,1,2)); //  

    //2 Misalignment in same SL:  Small, noth worth
    skipLayersFromReference.insert(DTLayerId(-2,4,3,1,4)); // probably also 2 is misaligned.
    skipLayersFromReference.insert(DTLayerId( 2,4,6,1,1)); // L2 is also misaligned.

    //Others with patterns, or multiple effects
    skipLayersFromReference.insert(DTLayerId( 1,4,5,3,4)); // small, maybe not worth?
    skipLayersFromReference.insert(DTLayerId( 2,2,1,1,4)); // visible pattern
    skipLayersFromReference.insert(DTLayerId(-2,3,8,3,4)); // visible pattern
    skipLayersFromReference.insert(DTLayerId(-2,3,8,1,4)); //  with above; too small
    //-2,4,2,3,1 has clear pattern
  }
  
}

DTTreeBuilder::~DTTreeBuilder(){}


void DTTreeBuilder::analyze(const Event& event, const EventSetup& setup) {
  if(debug)
    cout << "[DTTreeBuilder] Analyze #Run: " << event.id().run()
	 << " #Event: " << event.id().event() << endl;

  // get the BX, run, event...
  BX = event.bunchCrossing();
  runN = event.id().run();
  eventN = event.id().event();

  if (theUpdator) theUpdator->setES(setup);


  // Get the 4D segment collection from the event
  edm::Handle<DTRecSegment4DCollection> all4DSegments;
  event.getByLabel(theRecHits4DLabel, all4DSegments);

  // Get the 2D segment collection from the event
  edm::Handle<DTRecSegment2DCollection> all2DSegments;
  if (theRecHits2DLabel!="") {
    event.getByLabel(theRecHits2DLabel, all2DSegments);
  }
  
  // Get the DT rechit collection from the event
  Handle<DTRecHitCollection> dtRecHits;
  event.getByLabel(theRecHitLabel, dtRecHits);


  edm::Handle<reco::VertexCollection> vertex; 
  event.getByLabel("goodPrimaryVertices", vertex);

  // Get the DT Geometry
  ESHandle<DTGeometry> dtGeom;
  setup.get<MuonGeometryRecord>().get(dtGeom);
  
  // Get the map of noisy channels
  ESHandle<DTStatusFlag> statusMap;
  if(checkNoisyChannels) {
    setup.get<DTStatusFlagRcd>().get(statusMap);
  }

  setup.get<DTTtrigRcd>().get(tTrigMap);
  setup.get<DTT0Rcd>().get(t0Handle);


  // Get the map of ttrig from the Setup
  setup.get<DTMtimeRcd>().get(mTimeHandle);
  const DTMtime *mTimeMap = &*mTimeHandle;


  int segmCounter = 0;



  // Loop over all chambers containing a 4D segment
  for (DTRecSegment4DCollection::id_iterator chamberId = all4DSegments->id_begin(); chamberId != all4DSegments->id_end(); ++chamberId) {
    // Get the range for the corresponding ChamerId
    DTRecSegment4DCollection::range  range = all4DSegments->get(*chamberId);
    int nsegm = distance(range.first, range.second);
    if(debug)
      cout << "   Chamber: " << *chamberId << " has " << nsegm
	   << " 4D segments" << endl;
    // Get the chamber
    const DTChamber* chamber = dtGeom->chamber(*chamberId);

    // Loop over the rechits of this ChamerId
    for (DTRecSegment4DCollection::const_iterator segment4D = range.first;
	 segment4D!=range.second;
	 ++segment4D) {
      if(debug){
   	cout<<"Looping on 4D rechits: -------------------------"<<endl;
	cout << "   == RecSegment dimension: " << (*segment4D).dimension() << endl;
      }

      // NA: For the time being, keep ALL 4D segments
      // If Statio != 4 skip RecHits with dimension != 4
      // For the Station 4 consider 2D RecHits
//       if((*segment4D).dimension() != 4) {
// 	if(debug)
// 	  cout << "[DTTreeBuilder]***Warning: RecSegment dimension is not 4 but "
// 	       << (*segment4D).dimension() << ", skipping!" << endl;
// 	continue;
//       }
      

      // Get all 1D RecHits at step 3 within the 4D segment
      vector<DTRecHit1D> recHits1D_S3;

      // Create the segment object
      DTSegmentObject * segmObj = new((*segmentArray)[segmCounter++]) DTSegmentObject((*chamberId).wheel(), (*chamberId).station(), (*chamberId).sector());
      LocalPoint segment4DLocalPos = (*segment4D).localPosition();
      segmObj->setPositionInChamber(segment4DLocalPos.x(), segment4DLocalPos.y(), segment4DLocalPos.z());

      // Segment angles defined in the chamber RF
      float dxdz = std::atan((*segment4D).localDirection().x()/(*segment4D).localDirection().z());
      float dydz = std::atan((*segment4D).localDirection().y()/(*segment4D).localDirection().z());
      
      //      cout << "DTTreeBuilder: " << *chamberId << " dxdz: " << dxdz << " dydz: " << dydz << " " << endl;

      segmObj->phi = dxdz;
      segmObj->theta = dydz;
      segmObj->chi2 = (*segment4D).chi2()/(*segment4D).degreesOfFreedom();

      GlobalPoint segment4DGlobalPos = chamber->toGlobal(segment4DLocalPos);
      segmObj->setGlobalPosition(segment4DGlobalPos.x(), segment4DGlobalPos.y(), segment4DGlobalPos.z());


      int projection = -1;
      
      DTRecSegment4D refittedSegment4D((*segment4D));
      if((*segment4D).hasPhi()) {
	if(debug) cout << "  segment has phi projection" << endl;
	DTSuperLayerId supLayIdPhi1((*chamberId), 1);
	DTSuperLayerId supLayIdPhi2((*chamberId), 3);
	float hitResolution = 0;//FIXME: should use this!	
	// get the vdrift of the 2 phi SLs and take the average
	float vDrift1 = 0.;
	// vdrift is cm/ns , resolution is cm
	mTimeMap->get(supLayIdPhi1,
		      vDrift1,
		      hitResolution,
		      DTVelocityUnits::cm_per_ns);

	float vDrift2 = 0.;
	// vdrift is cm/ns , resolution is cm
	mTimeMap->get(supLayIdPhi2,
		      vDrift2,
		      hitResolution,
		      DTVelocityUnits::cm_per_ns);

	float vdrift = (vDrift1 + vDrift2) / 2.;
	
	// FIXME: Apply the corrections that are harcoded in RecoLocalMuon/DTRecHit/plugins/DTLinearDriftFromDBAlgo.cc
	  // (variation of vdrift along Y due to B field)
	if (abs((*chamberId).wheel()) == 2 && 
	    (*chamberId).station() == 1) {
	  // Note that here we pick the segment local Y, while in reco the correction is applied using the hit local Y!
	  const float k_param = 1.2e-04;
	  vdrift = vdrift*(1. - k_param*segment4DLocalPos.y());
	}

	const DTChamberRecSegment2D* phiSeg = (*segment4D).phiSegment();
	vector<DTRecHit1D> phiRecHits = phiSeg->specificRecHits();
	copy(phiRecHits.begin(), phiRecHits.end(), back_inserter(recHits1D_S3));
	projection = 1;
	if ((*segment4D).phiSegment()->ist0Valid()) {
	  segmObj->t0SegPhi = (*segment4D).phiSegment()->t0();
	  float dVdrift = (*segment4D).phiSegment()->vDrift();
	  segmObj->dVDriftPhi = dVdrift;  // O is returned in case of failure, e.g. if nhits < 5, or vdrift corr > 10%
	  segmObj->vDriftCorrPhi =  vdrift*(1. - dVdrift);
	} else {
	  segmObj->t0SegPhi = -1.;
	  segmObj->dVDriftPhi    = 0.; // this is already used for falure anyhow
	  segmObj->vDriftCorrPhi =  vdrift;
	}

	// Refit segment to be used as reference for the computation of residuals, possibly skipping selected layers
	if (refitReferenceSegment) {
	  bool mustRefit=false;
	  vector<DTRecHit1D> updatedRecHits;		
	  for (vector<DTRecHit1D>::const_iterator hit=phiRecHits.begin();
	       hit!=phiRecHits.end(); ++hit) {

	    if (skipLayersFromReference.find((*hit).wireId().layerId())==skipLayersFromReference.end()) {
	      updatedRecHits.push_back(*hit);
	    } else {
	      mustRefit = true;
	    } 
	  }
	
	  if (mustRefit) {
	    refittedSegment4D.phiSegment()->update(updatedRecHits);	
	    theUpdator->fit(&refittedSegment4D);
	  }

// 	  float ddir = (refittedSegment4D.localDirection()-(*segment4D).localDirection()).mag();
// 	  float dpos = (refittedSegment4D.localPosition()-(*segment4D).localPosition()).mag();	  
// 	  if (mustRefit || ddir > 0.00001 || dpos > 0.0001)  cout << "refit: " << mustRefit << " D: " << ddir << " P: " << dpos << endl;

	}
      }



      if((*segment4D).hasZed()) {
	DTSuperLayerId supLayIdTheta((*chamberId), 2);
	float hitResolution = 0;//FIXME: should use this!	
	// get the vdrift of the 2 phi SLs and take the average
	float vdrift = 0.;
	// vdrift is cm/ns , resolution is cm
	mTimeMap->get(supLayIdTheta,
		      vdrift,
		      hitResolution,
		      DTVelocityUnits::cm_per_ns);


	const DTSLRecSegment2D* zSeg = (*segment4D).zSegment();
	vector<DTRecHit1D> zRecHits = zSeg->specificRecHits();
	copy(zRecHits.begin(), zRecHits.end(), back_inserter(recHits1D_S3));
	if(projection == -1) projection = 2;
	else projection = 3;
	// 	segmObj->t0SegTheta = (*segment4D).zSegment()->t0();
	float dVdrift = (*segment4D).zSegment()->vDrift();
	if ((*segment4D).zSegment()->ist0Valid()) {
	  segmObj->vDriftCorrTheta =  vdrift*(1. - dVdrift);
	  segmObj->t0SegTheta = (*segment4D).zSegment()->t0();
	} else {
	  segmObj->vDriftCorrTheta =  -1.;
	  segmObj->t0SegTheta = -1.;
	}
	// 	segmObj->vDriftCorrTheta = (*segment4D).zSegment()->vDrift();
      }

      segmObj->proj = projection;

      for(int sl = 1; sl != 4; ++sl) {
	DTSuperLayerId supLayId((*chamberId), sl);
	//	float ttrig = 0.;
	float mean = 0.;
	float sigma = 0.;
	float kFact = 0.0;
	// FIXME: port to 31X interface
	tTrigMap->get(supLayId, mean, sigma, kFact, DTTimeUnits::ns); 
	//ttrig = mean + kFact*sigma;
	segmObj->setTTrig(sl, mean, sigma, kFact);
      }

      // Set up segment extrapolator using the refitted segment as a reference
      StraightLinePlaneCrossing segmentPlaneCrossing((chamber->toGlobal(refittedSegment4D.localPosition())).basicVector(),
						     (chamber->toGlobal(refittedSegment4D.localDirection())).basicVector(),
						     anyDirection);

      // Loop over 1D RecHit inside 4D segment
      for(vector<DTRecHit1D>::const_iterator recHit1D = recHits1D_S3.begin();
	  recHit1D != recHits1D_S3.end();
	  recHit1D++) {
	const DTWireId wireId = (*recHit1D).wireId();
	if(debug) {
	  cout<<"Looping on 1D rechits: -------------------------"<<endl;
	  cout << wireId << endl;
	}
	//	cout << wireId << " " << sqrt((*recHit1D).localPositionError().xx()) << endl;

	
	DTHitObject *hitObj = segmObj->add1DHit(wireId.wheel(), wireId.station(), wireId.sector(),
					       wireId.superLayer(), wireId.layer(), wireId.wire());
	
	
	hitObj->digiTime = (*recHit1D).digiTime() ;

	float t0 = 0;
	float t0rms = 0;
	// Read the t0 from pulses for this wire (ns)
	t0Handle->get(wireId,
		      t0,
		      t0rms,
		      DTTimeUnits::ns);

	hitObj->t0pulses = t0;

	// Check for noisy channels and skip them
	if(checkNoisyChannels) {
	  bool isNoisy = false;
	  bool isFEMasked = false;
	  bool isTDCMasked = false;bool isTrigMask = false;
	  bool isDead = false;
	  bool isNohv = false;
	  statusMap->cellStatus(wireId, isNoisy, isFEMasked, isTDCMasked, isTrigMask, isDead, isNohv);
	  hitObj->isNoisyCell = isNoisy;
	}

	// Get the layer and the wire position
	const DTLayer* layer = (chamber->superLayer(wireId.superlayerId()))->layer(wireId.layerId());
	float wireX = layer->specificTopology().wirePosition(wireId.wire());

	// Extrapolate segment to layer surface
	pair<bool,Basic3DVector<float> > ppt = segmentPlaneCrossing.position(layer->surface());
	if (ppt.first==false) {
	  cout << "ERROR: invalid segment extrapolation" <<  refittedSegment4D.localPosition() << " " << refittedSegment4D.localDirection() << endl;
	  continue;	  
	}
	GlobalPoint segExrapolationToLayer(ppt.second);
	LocalPoint  segExrapolationToLayer_lrf = layer->toLocal(segExrapolationToLayer);

	// Distance between 1D rechit and segment extrapolation
	float deltaX = (*recHit1D).localPosition().x() - segExrapolationToLayer_lrf.x();
	// Distance of the 1D rechit from the wire
	double distRecHitToWire = std::abs(wireX - (*recHit1D).localPosition().x());
	// Distance of the segment extrapolation from the wire
	double distSegmToWire = std::abs(wireX-segExrapolationToLayer_lrf.x());
	
	// Segment angle in the layer RF. (this is the original segment, not the refitted one!)
	LocalVector segDirInLayer = layer->toLocal(chamber->toGlobal((*segment4D).localDirection()));
	float angle = std::atan(segDirInLayer.x()/segDirInLayer.z());

	if(fabs(distSegmToWire) > 10)
	  cout << "  Warning: dist segment-wire: " << distSegmToWire << endl;

	// create the DTHitObject
	hitObj->setLocalPosition((*recHit1D).localPosition().x(),
				(*recHit1D).localPosition().y(),
				(*recHit1D).localPosition().z());
	
	hitObj->resDist = distRecHitToWire - distSegmToWire;
	hitObj->resPos = deltaX;
	hitObj->distFromWire = distSegmToWire;
	hitObj->sigmaPos = sqrt((*recHit1D).localPositionError().xx());
	hitObj->angle = angle;


	// Re-reconstruct hits at different steps
	
	// 1.step
	DTDigi digi(wireId.wire(), double((*recHit1D).digiTime()));
	LocalPoint leftPoint;
	LocalPoint rightPoint;
	LocalError error;
	theAlgo->setES(setup);
	float dS1 =-1.;
	if (theAlgo->compute(layer, digi, leftPoint, rightPoint, error)){
	  dS1 = (leftPoint-rightPoint).mag()/2.;
	  hitObj->resDistS1=dS1 - distSegmToWire;
	}

	// 2. step
	float dS2 =-1.;
	// Beware, lin algo just copies input RH to output RH, does not to the actual job!
	// FIXME simple hack for the time being. Should rather rebuild the S1 hit from dS1!
	if (algoName=="DTLinearDriftFromDBAlgo") {
	  dS2 = dS1;
	} else {
	  DTRecHit1D rhS2 = (*recHit1D);
	  if (theAlgo->compute(layer, (*recHit1D), angle, rhS2)) {
	    dS2 = fabs(wireX - rhS2.localPosition().x());
	  }
	}

	if (dS2>=0.) {
	  hitObj->resDistS2=dS2 - distSegmToWire;
	}

	// 3. step: re-reco (crossckeck)
	//	float dS3 =-1.;
	DTRecHit1D rhS3 = (*recHit1D);
	//	GlobalPoint pos = chamber->toGlobal(segPosAtZWire);
// 	if (theAlgo->compute(layer, (*recHit1D), angle, pos, rhS3)) {
// 	  dS3 = fabs(wireX - rhS3.localPosition().x());
// 	}

// 	if (fabs(dS3 - distRecHitToWire) > 0.0005) {  
// 	  // FIXME must check why!!!
// 	  cout << endl << "WARNING: " << distRecHitToWire << " S1=" << dS1 << " S2=" << dS2 << " S3=" << dS3 
// 	       << " diff recomputed S3:" <<  dS3 - distRecHitToWire<< endl << endl;

// 	}
	
      }// End of loop over 1D RecHit inside 4D segment
      
      // Add the DTSegmentObject to the TClonesArray
      if(debug) cout << "Add new segment with # hits: " << segmObj->hits->GetEntriesFast() << endl;
      if(debug) cout << "    new # of segments is: " << segmCounter << endl;

      

      // Add available 1D hits for this chamber
      
      for (int sl = 1; sl <=3; ++sl) {
	if ((*chamberId).station()==4 && sl==3) continue;
	for (int layer = 1; layer <=4; ++layer) {
	  DTLayerId lId((*chamberId),sl,layer);
	  DTRecHitCollection::range range = dtRecHits->get(lId);
	  for (DTRecHitCollection::const_iterator recHit1D = range.first; recHit1D!=range.second; ++recHit1D) {
	    DTWireId wireId = (*recHit1D).wireId();
	    DTHitObject *hitObj = segmObj->addAvailable1DHit(wireId.wheel(), wireId.station(), wireId.sector(),wireId.superLayer(), wireId.layer(), wireId.wire());
	    
	    hitObj->digiTime = (*recHit1D).digiTime() ;
	    hitObj->setLocalPosition((*recHit1D).localPosition().x(),
				     (*recHit1D).localPosition().y(),
				     (*recHit1D).localPosition().z());
	    hitObj->distFromWire = ((*recHit1D).localPosition(DTEnums::Right)-(*recHit1D).localPosition(DTEnums::Left)).mag()/2.;
	    
	    hitObj->sigmaPos = sqrt((*recHit1D).localPositionError().xx());

	  }
	}
      }
      

    }// End of loop over the segm4D of this ChamerId
  }


  // 2D segments
  //----------------------------------------------------------------------
  if (theRecHits2DLabel!="") {
    int segm2DCounter = 0;  
    for (DTRecSegment2DCollection::id_iterator slId = all2DSegments->id_begin(); slId != all2DSegments->id_end(); ++slId) { // loop over SLs with segments
      DTRecSegment2DCollection::range  range = all2DSegments->get(*slId);
      int nsegm = distance(range.first, range.second);
      if(debug)
	cout << "   SL: " << *slId << " has " << nsegm
	     << " 2D segments" << endl;
      // Get the SL
      const DTSuperLayer* sl = dtGeom->superLayer(*slId);


      for (DTRecSegment2DCollection::const_iterator segment2D = range.first;
	   segment2D!=range.second; ++segment2D) { // Loop over the segments in this SL
	if(debug){
	  cout<<"Looping on 2D segments: -------------------------"<<endl;
	}


	// Get all 1D RecHits at step 2 within the 2D segment
	vector<DTRecHit1D> recHits1D_S2;

	// Create the segment object
	DTSegmentObject * segmObj = new((*segment2DArray)[segm2DCounter++]) DTSegmentObject((*slId).wheel(), (*slId).station(), (*slId).sector());
	LocalPoint segment2DLocalPos = (*segment2D).localPosition();
	segmObj->setPositionInChamber(segment2DLocalPos.x(), segment2DLocalPos.y(), segment2DLocalPos.z());

      // Segment angle defined in the chamber RF
	float dxdz = std::atan((*segment2D).localDirection().x()/(*segment2D).localDirection().z());

	segmObj->phi = dxdz;
	segmObj->theta = 0;
	segmObj->chi2 = (*segment2D).chi2()/(*segment2D).degreesOfFreedom();
      
	int projection = -1;

	if((*slId).superLayer()==2) {
	  projection = 2;
	} else {
	  projection = 1;
	}
      
	recHits1D_S2 = segment2D->specificRecHits();
	segmObj->proj = projection;


	// Loop over 1D RecHit inside 2D segment
	for(vector<DTRecHit1D>::const_iterator recHit1D = recHits1D_S2.begin();
	    recHit1D != recHits1D_S2.end();
	    recHit1D++) {
	  const DTWireId wireId = (*recHit1D).wireId();
	  if(debug) {
	    cout<<"Looping on 1D rechits: -------------------------"<<endl;
	    cout << wireId << endl;
	  }

	
	  DTHitObject *hitObj = segmObj->add1DHit(wireId.wheel(), wireId.station(), wireId.sector(),
						  wireId.superLayer(), wireId.layer(), wireId.wire());
	
	
	  hitObj->digiTime = (*recHit1D).digiTime() ;

	  float t0 = 0;
	  float t0rms = 0;
	  // Read the t0 from pulses for this wire (ns)
	  t0Handle->get(wireId,
			t0,
			t0rms,
			DTTimeUnits::ns);

	  hitObj->t0pulses = t0;

	  // Check for noisy channels and skip them
	  if(checkNoisyChannels) {
	    bool isNoisy = false;
	    bool isFEMasked = false;
	    bool isTDCMasked = false;
	    bool isTrigMask = false;
	    bool isDead = false;
	    bool isNohv = false;
	    statusMap->cellStatus(wireId, isNoisy, isFEMasked, isTDCMasked, isTrigMask, isDead, isNohv);
	    hitObj->isNoisyCell = isNoisy;
	  }

	  // Get the layer and the wire position
	  const DTLayer* layer = sl->layer(wireId.layerId());
	  float wireX = layer->specificTopology().wirePosition(wireId.wire());


	
	  // Distance of the 1D rechit from the wire
	  //float distRecHitToWire = fabs(wireX - (*recHit1D).localPosition().x());
	  float distRecHitToWire = fabs(wireX - (*recHit1D).localPosition().x());
	
	  // Extrapolate the segment to the z of the wire
	
	  // Get wire position in SL RF
	  LocalPoint wirePosInLay(wireX,0,0);
	  LocalPoint wirePosInSl = sl->toLocal(layer->toGlobal(wirePosInLay));
	  // 	cout << "Wire: " << wireId << " z: " << wirePosInChamber.z() << endl;

	  // Segment position at Wire z in SL local frame
	  // FIXME: this neglects misalignment, should use the proper implementation as for 4D (cf above)
	  LocalPoint segPosAtZWire = (*segment2D).localPosition()
	    + (*segment2D).localDirection()*wirePosInSl.z()/cos((*segment2D).localDirection().theta());
  

	  float deltaX = (*recHit1D).localPosition().x() - (layer->toLocal(sl->toGlobal(segPosAtZWire))).x();
	  float angle = dxdz;
	  double distSegmToWire = fabs(wirePosInSl.x() - segPosAtZWire.x());

	  // 	cout << wireId << " wiX=" << wireX << " drhw=" << distRecHitToWire 
	  // 	     << " wposL=" << wirePosInLay 
	  // 	     << " wposSl=" << wirePosInSl << endl
	  // 	     << " segPosAtZWire=" << segPosAtZWire
	  // 	     << " deltaX " << deltaX 
	  // 	     << " distSegmToWire " << distSegmToWire <<endl
	  // 	     << " theta=" <<(*segment2D).localDirection().theta()
	  // 	     << " angle=" <<angle <<endl <<endl;


	  if(fabs(distSegmToWire) > 10)
	    cout << "  Warning: dist segment-wire: " << distSegmToWire << endl;
	
	
	  // plots for different angles
	  theFile->cd();

	  // FIXME
	  // create the DTHitObject
	  hitObj->setLocalPosition((*recHit1D).localPosition().x(),
				   (*recHit1D).localPosition().y(),
				   (*recHit1D).localPosition().z());
	
	  hitObj->resDist = distRecHitToWire - distSegmToWire;
	  hitObj->resPos = deltaX;
	  hitObj->distFromWire = distSegmToWire;
	  hitObj->sigmaPos = sqrt((*recHit1D).localPositionError().xx());
	  hitObj->angle = angle;	

	}// End of loop over 1D RecHit inside 2D segment
      
	if(debug) cout << "Add new segment with # hits: " << segmObj->hits->GetEntriesFast() << endl;
	if(debug) cout << "    new # of segments is: " << segm2DCounter << endl;

      }// End of loop over the segm2D of this ChamerId
    }
  }
  


  // Look at muons -----------------------------------------------------------------------------

  Handle<MuonCollection> muons;
  event.getByLabel(theMuonLabel, muons);

  int muCounter = 0;

  if(muons.isValid()) {
    for (MuonCollection::const_iterator muon = muons->begin();
	 muon!=muons->end(); ++muon) { // loop over all muons

      DTMuObject * muObj = new((*muArray)[muCounter++]) DTMuObject();

      muObj->eta = (*muon).eta();
      muObj->phi = (*muon).phi();
      muObj->qpt = (*muon).pt()*(*muon).charge();

      if(debug)
	cout << "muon eta, phi:" << muObj->eta << " " << muObj->phi << endl;
      
      if (muon->isGlobalMuon()) {
	
	// Info from the GLB fit
	const HitPattern& hitP = (*muon).globalTrack()->hitPattern();

	muObj->nStripHits =hitP.numberOfValidStripHits();
	muObj->nPixHits   =hitP.numberOfValidPixelHits();
	muObj->nMuHits    =hitP.numberOfValidMuonHits();
	muObj->nGlbDTValidHits = hitP.numberOfValidMuonDTHits();

	muObj->nGlbDTHits = hitP.numberOfValidMuonDTHits()+hitP.numberOfBadMuonDTHits();


	// Info from the STA fit
	const HitPattern& hitPSTA = (*muon).outerTrack()->hitPattern();
	muObj->nStaDTValidHits = hitPSTA.numberOfValidMuonDTHits();
	muObj->nStaDTHits = hitPSTA.numberOfValidMuonDTHits() + hitPSTA.numberOfBadMuonDTHits();

      } else {
	if (muon->isStandAloneMuon()) { // STA Only
	  const HitPattern& hitP = (*muon).outerTrack()->hitPattern();

	  muObj->nMuHits    = hitP.numberOfValidMuonHits();	
	  muObj->nStaDTValidHits = hitP.numberOfValidMuonDTHits();
	  muObj->nStaDTHits = hitP.numberOfValidMuonDTHits() + hitP.numberOfBadMuonDTHits();

	}
	if (muon->isTrackerMuon()) { // TK Only
	  muObj->nStripHits =( *muon).innerTrack()->hitPattern().numberOfValidStripHits();
	  muObj->nPixHits   = (*muon).innerTrack()->hitPattern().numberOfValidPixelHits();
	}
      }
      
      
      float normChi2tk  = -1;
      float normChi2sta = -1;
      float normChi2glb = -1;
      int type = 0;      
      if(muon->isStandAloneMuon()) {
	normChi2sta = (*muon).outerTrack()->normalizedChi2();
	if(muon->isGlobalMuon()) {
	  normChi2tk = (*muon).innerTrack()->normalizedChi2();
	  normChi2glb = (*muon).globalTrack()->normalizedChi2();
	  if(muon->isTrackerMuon()) { 
	   type = 1; // STA + GLB + TM
	  } else type = 2; // STA + GLB
	} else {
	  if(muon->isTrackerMuon()) {
	    normChi2tk = (*muon).innerTrack()->normalizedChi2();
	    type = 3;  // STA + TM
	  } else type= 5; // STA
	} 
      } else {
	if(muon->isTrackerMuon()) type = 4; // TM
	normChi2tk = (*muon).innerTrack()->normalizedChi2();
      }
          

      muObj->normChi2tk=normChi2tk;
      muObj->normChi2sta=normChi2sta;
      muObj->normChi2glb=normChi2glb;
      muObj->type=type;

      // Segment matches
//       if(muon->isMatchesValid()){
// 	const std::vector<MuonChamberMatch>& matches = muon->matches();
// 	cout << "matches: " << matches.size() << endl;
//       }

      int sel = 0;
      //      if(muon::isGoodMuon(*muon,muon::GlobalMuonPromptTight)) sel=1;
      if(muon::isTightMuon(*muon,vertex->front())) sel=1;

      muObj->sel = sel;
    }
  }


  theTree->Fill();
//   cout << " clear the array" << endl;
  segmentArray->Delete();
  segment2DArray->Delete();
  muArray->Delete();
  

}


  


void DTTreeBuilder::endJob() {
  // Write all histos to file
  cout << "# of entries in the tree: " << theTree->GetEntries() << endl;
  theFile->cd();
  theTree->Write();
}








// BeginJob
void DTTreeBuilder::beginJob() {
  // create the tree
  theFile->cd();
  
  segmentArray = new TClonesArray("DTSegmentObject");
  segment2DArray = new TClonesArray("DTSegmentObject");
  muArray = new TClonesArray("DTMuObject");


  theTree = new TTree("DTSegmentTree","DTSegmentTree");
  theTree->SetAutoSave(10000000);

  theTree->Branch("segments", "TClonesArray", &segmentArray); 
  if (theRecHits2DLabel!="") {
    theTree->Branch("segments2D", "TClonesArray", &segment2DArray); 
  }
  theTree->Branch("muonCands", "TClonesArray", &muArray);
  theTree->Branch("BX", &BX, "BX/I");
  //  theTree->Branch("Pix", &pix, "Pix/I");
  theTree->Branch("Run", &runN, "Run/I");
  theTree->Branch("Event", &eventN, "Event/I");
}

