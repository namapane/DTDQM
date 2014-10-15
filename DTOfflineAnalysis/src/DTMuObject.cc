/*
 *  See header file for a description of this class.
 *
 *  $Date: 2010/07/30 10:32:47 $
 *  $Revision: 1.3 $
 */

#include "DTMuObject.h"

using namespace std;

DTMuObject::DTMuObject() : 
  eta(-999),
  phi(-999),
  qpt(-999),
  nMuHits(-1),
  nStaDTHits(-1),
  nGlbDTHits(-1),
  nStaDTValidHits(-1),
  nGlbDTValidHits(-1),
  nStripHits(-1),
  nPixHits(-1),
  normChi2tk(-1.),
  normChi2sta(-1.),
  normChi2glb(-1.),
  type(-1),
  sel(-1){
}


ClassImp(DTMuObject)
