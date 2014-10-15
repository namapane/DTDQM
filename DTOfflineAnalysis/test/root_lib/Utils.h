#ifndef Utils_H
#define Utils_H

/** \class Utils
 *  No description available.
 *
 *  $Date: 2013/10/14 23:09:49 $
 *  $Revision: 1.4 $
 *  \author G. Cerminara - INFN Torino
 */

#include "TString.h"

class DTDetId;
class TCanvas;

namespace Utils {

  // Operations
  TString getHistoNameFromDetId(const DTDetId& detId);
  
  TString getHistoNameFromDetIdAndSet(const DTDetId& detId, const TString& set);

  TString getDTValidationHistoNameFromDetId(const DTDetId& detId, TString step="S3");
  
  TCanvas * newCanvas(TString name,
		      TString title="",
		      int xdiv=0,
		      int ydiv=0,
		      int form = 1,
		      int w=-1);

  TCanvas * newCanvas(TString name, int xdiv, int ydiv, int form, int w);
  TCanvas * newCanvas(int xdiv, int ydiv, int form = 1);
  TCanvas * newCanvas(int form = 1);
  TCanvas * newCanvas(TString name, int form, int w=-1);

  void newName(TNamed* obj);


};
#endif


  
