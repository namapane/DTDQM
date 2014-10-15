#include <map>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>
#include <TRandom3.h>


// g++ -I /afs/cern.ch/cms/sw/slc5_ia32_gcc434/lcg/root/5.22.00d-cms18/include  /afs/cern.ch/cms/sw/slc5_ia32_gcc434/lcg/root/5.22.00d-cms18/lib/libMathCore.so tuneMCScenario.cc -o tuneMCScenario

using namespace std;

int main(int argc, char *argv[]) {

  if (argc>4||argc<3) {
    cout << "args: sigma_data.txt sigma_mc_ideal.txt [t0_template.txt]" << endl
	 << "  t0_template.txt is just used to get the list of channels; if not specified, smearings are reported instead of table" <<endl;
    return 0;
  }

  bool onlySmearings = true;
  if (argc==4) onlySmearings = false;

  ifstream file1(argv[1]);
  if (!file1) { // Oops                                    
    cerr << argv[1] << " Not found" <<endl;
    return 0;
  }

  ifstream file2(argv[2]);
  if (!file2) { // Oops                                    
    cerr << argv[2] << " Not found" <<endl;
    return 0;
  }


  // [wheel][station][sector][sl]
  map<int,map<int,map<int,map<int,float> > > > table_data;
  map<int,map<int,map<int,map<int,float> > > > table_mc;
  map<int,map<int,map<int,map<int,float> > > > table_smear;

  // Read file1
  string line;
  while (getline(file1,line)) {
    if( line == "" || line[0] == '#' ) continue;
    stringstream linestr;
    linestr << line;

    int wheel, sector, station, sl, l, w, d1, d2, d3;
    float vd, value;
    linestr >> wheel >> station >> sector >> sl >> l >> w 
	    >> d1 >> d2 >> d3 >> vd >> value;
    table_data[wheel][station][sector][sl] = value;  
  }

  // Read file2
  while (getline(file2,line)) {
    if( line == "" || line[0] == '#' ) continue;
    stringstream linestr;
    linestr << line;

    int wheel, sector, station, sl, l, w, d1, d2, d3;
    float vd, value;
    linestr >> wheel >> station >> sector >> sl >> l >> w
	    >> d1 >> d2 >> d3 >> vd >> value;
    table_mc[wheel][station][sector][sl] = value;  
  }

  // Compute smearings

  for (int wheel = -2; wheel<3; ++wheel) {
    for (int station = 1; station<5; ++station) {
      for (int sector = 1; sector<15; ++sector) {
	if (station!=4 && sector >=13) continue;
	for (int sl = 1; sl <=3; ++sl) {
	  if (station==4 && sl==2) continue;

	  //-->

	  float s_data = table_data[wheel][station][sector][sl];
	  float s_mc   = table_mc[wheel][station][sector][sl];
	  float smear = sqrt(max(0.f,(s_data*s_data-s_mc*s_mc))); //in micron

	  table_smear[wheel][station][sector][sl] =smear;

	  if (onlySmearings) {  
	    cout << wheel << " " << station << " " << sector << " " << sl << " : " << s_data*10000./54.3 << " " << s_mc*10000./54.3 << " " << smear*10000./54.3 << endl;
	  }
	  //<--

	}
      }
    }
  }

  

  if (onlySmearings) return 0;

  // Loop on t0 file
  ifstream file3(argv[3]);
  if (!file3) { // Oops                                    
    cerr << file3 << " Not found" <<endl;
    return 0;
  }

  TRandom3* random = new TRandom3();

  while (getline(file3,line)) {
    if( line == "" || line[0] == '#' ) continue;
    stringstream linestr;
    linestr << line;

    int wheel, station, sector, sl, l, w, d1, d2, d3, d4, d5;
    double t0, t0sigma, ttrig;
    linestr >> wheel >> station >> sector >> sl >> l >> w >> 
      d1 >> d2 >> d3 >> d4 >> d5 >> t0 >> t0sigma;


    // in TDC counts:
    float smear = table_smear[wheel][station][sector][sl]*10000.*32./(54.3*25.);
      
    cout << wheel << " " << station << " " << sector << " " << sl << " " << l << " " << w << " " << d1 << " " << d2 << " " << d3 << " " << d4 << " " << d5 << " " << random->Gaus(0,smear) << " " << 0 << " " << endl; 
  }

  return 0;
}
