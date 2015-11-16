/*
 * compile:  
 * g++ sumTables.cc -o sumTables
 * usage: sumTables <originalTTrig> <originalVdrift> <correctionTable> 
 * originalTTrig = "zero" -> write correction only
 */

#include <cassert>
#include <cstring>
#include <map>
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {

  if (argc!=4) {
    cout << "args: <originalTTrig> <originalVdrift> <correctionTable>" << endl;
    return 0;
  }

  // [wheel][station][sector][sl]
  map<int,map<int,map<int,map<int,pair <float,float> > > > > ttrigTable;  // Original table of ttrig and kappa (assuming sigma==1)
  map<int,map<int,map<int,map<int,float> > > > vdriftTable; // Original vdrift table
  //  map<int,map<int,map<int,map<int,float> > > > corrTable;   // table with offsets *in cm* 


  // Read original ttrig, skip if originalTTrig=="zero"

  ifstream* file1=0;
  string line;
  if (strcmp(argv[1],"zero")!=0){
    file1 = new ifstream(argv[1]);
    if (!*file1) { // Oops                                    
      cerr << argv[1] << " Not found" <<endl;
      return 0;
    }

    while (getline(*file1,line)) {
      if( line == "" || line[0] == '#' ) continue;
      stringstream linestr;
      linestr << line;

      int wheel, sector, station, sl, l, w;
      float ttrig, sigma, kappa;
      linestr >> wheel >> station >> sector >> sl >> l >> w >> ttrig >> sigma >> kappa;
      assert (sigma==1);

      ttrigTable[wheel][station][sector][sl] = make_pair(ttrig, kappa);
    }
  }

  ifstream file2(argv[2]);
  if (!file2) { // Oops                                    
    cerr << argv[2] << " Not found" <<endl;
    return 0;
  }


  // Read original vdrift
  while (getline(file2,line)) {
    if( line == "" || line[0] == '#' ) continue;
    stringstream linestr;
    linestr << line;

    int wheel, sector, station, sl, l, w, d1, d2, d3;
    double value;
    linestr >> wheel >> station >> sector >> sl >> l >> w >> d1 >> d2 >> d3 >> value;
    assert(d1==-1&&d2==-1&&d3==-1);

    vdriftTable[wheel][station][sector][sl] = value;  
  }


  // Read corrTable
  ifstream file3(argv[3]);
  if (!file3) { // Oops                                    
    cerr << argv[3] << " Not found" <<endl;
    return 0;
  }

  while (getline(file3,line)) {
    if( line == "" || line[0] == '#' ) continue;
    stringstream linestr;
    linestr << line;

    int wheel, sector, station, sl, l, w;
    double value;
    linestr >> wheel >> station >> sector >> sl >> l >> w >> value;
    
    //ttrigTable[wheel][station][sector][sl].second += value/vdriftTable[wheel][station][sector][sl];  
    ttrigTable[wheel][station][sector][sl].second += value/vdriftTable[wheel][station][sector][1];  //FIXME FIXME FIXME!!!! using vd for sl=1?
  }

  
  // Write

  for (int wheel = -2; wheel<3; ++wheel) {
    for (int station = 1; station<5; ++station) {
      for (int sector = 1; sector<15; ++sector) {
	if (station!=4 && sector >=13) continue;
	for (int sl = 1; sl <=3; ++sl) {
	  if (station==4 && sl==2) continue;

	  //-->

	  float ttrig =  ttrigTable[wheel][station][sector][sl].first;
	  float kappa =  ttrigTable[wheel][station][sector][sl].second;

	  cout << wheel << " " << station << " " << sector << " " << sl << " 0 0 " << ttrig << " 1 " << kappa << " -1 -1 " << endl;

	  //<--

	}
      }
    }
  }
  return 0;
}
