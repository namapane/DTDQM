#ifndef DTDetId_H
#define DTDetId_H

/** \class DTDetId
 *  No description available.
 *
 *  $Date: 2011/02/07 21:56:20 $
 *  $Revision: 1.3 $
 *  \author G. Cerminara - INFN Torino
 */
#include <iosfwd>


class DTDetId {
public:
  /// Constructor
  // NOTE: use 0 for all
  DTDetId(int aWheel, int aStation, int aSector, int aSl, int aLayer, int aWire);

  DTDetId();



  /// Destructor
  virtual ~DTDetId();
  
  // strict ordering 
  bool operator<(const DTDetId& aDetId) const;

  // Equality
  bool operator==(const DTDetId& aDetId) const;

  
//   bool matchesGranularity(const int granularity, const DTDetId& detid) const;

  // Operations
  int wheel;
  int station;
  int sector;
  int sl;
  int layer;
  int wire;
protected:

private:

  

};

std::ostream& operator<<( std::ostream& os, const DTDetId& id );

#endif


