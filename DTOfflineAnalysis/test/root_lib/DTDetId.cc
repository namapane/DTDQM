
/*
 *  See header file for a description of this class.
 *
 *  $Date: 2011/02/07 21:56:13 $
 *  $Revision: 1.3 $
 *  \author G. Cerminara - INFN Torino
 */

#include "DTDetId.h"
#include <iostream>

using namespace std;

DTDetId::DTDetId(int aWheel,
		 int aStation,
		 int aSector,
		 int aSl,
		 int aLayer,
		 int aWire) : wheel(aWheel),
			      station(aStation),
			      sector(aSector),
			      sl(aSl),
			      layer(aLayer),
			      wire(aWire) {}


DTDetId::DTDetId() : wheel(-1),
		     station(-1),
		     sector(-1),
		     sl(-1),
		     layer(-1),
		     wire(-1) {}



DTDetId::~DTDetId(){}



bool DTDetId::operator<(const DTDetId& aDetId) const {
//   cout << "   compare Wh: " << wheel << " wt " << aDetId.wheel
//        << " st: " << station << " wt " << aDetId.station
//        << " sect: " << sector << " wt " << aDetId.sector
//        << " sl: " << sl << " wt " << aDetId.sl
//        << " l: " << layer << " wt " << aDetId.layer
//        << " w: " << wire << " wt " << aDetId.wire << endl;
  if(wheel != aDetId.wheel) {
//     cout << "      res 1" << endl;
    return wheel < aDetId.wheel;
  } else if(station != aDetId.station) {
//     cout << "      res 2" << endl;
    return station < aDetId.station;
  } else if(sector != aDetId.sector) {
//     cout << "      res 3" << endl;
    return sector < aDetId.sector;
  } else if(sl != aDetId.sl) {
//     cout << "      res 4" << endl;
    return sl < aDetId.sl;
  } else if(layer != aDetId.layer) {
//     cout << "      res 5" << endl;
    return layer < aDetId.layer;
  } else if(wire != aDetId.wire) {
//     cout << "      res 6" << endl;
    return wire < aDetId.wire;
  }
//   cout << "   res default" << endl;
  return false;
}


bool DTDetId::operator==(const DTDetId& aDetId) const {
  if (wheel == aDetId.wheel &&
      station == aDetId.station &&
      (sector ==0 || aDetId.sector == 0 || sector == aDetId.sector) &&
      sl == aDetId.sl &&
      (layer == 0 || aDetId.layer == 0 || layer == aDetId.layer) &&
      (wire == 0 || aDetId.wire==0 || wire == aDetId.wire)) return true;
  return false;
}


// bool matchesGranularity(const int granularity, const DTDetId& aDetId) const {
//   if(granularity ==  1) { // by SL
//     if(wheel == aDetId.wheel &&
//        station == aDetId.station &&
//        sector == aDetId.sector &&
//        sl == aDetId.sl) return true;
//   }

//   return false;
// }

// Ostream operator
ostream& operator<<(ostream& os, const DTDetId& id ){

  os << " Wh:"<< id.wheel
     << " St:"<< id.station 
     << " Se:"<< id.sector
     << " Sl:"<< id.sl
     << " La:"<< id.layer
     << " Wi:"<< id.wire
     <<" ";

  return os;
}

