//
// mayday.cpp
//
// use: mayday latitude longitude min_length
//
// Provide a list of facilities and runways closest to the location specified
// by the coordinates (latitude,longitude).
// Only facilities having runways longer than min_length are printed.
// Only runways longer than min_length are printed.
//
// Input:
//   latitude, longitude in degrees decimal
//   min_length in ft
// Output:
//   list of nearest facilities and runways including distance in nautical miles

#include "Facility.h"
#include "Runway.h"
#include "Closer.h"
#include "SiteNumber.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cassert>
#include <cmath>
using namespace std;

int main(int argc, char **argv)
{
  // use: mayday current_latitude current_longitude min_runway_length
  // latitude and longitudes in degrees decimal
  // min runway length of runway in ft

  assert(argc==4);
  const double current_latitude = atof(argv[1]);
  const double current_longitude = atof(argv[2]);
  const int min_runway_length = atoi(argv[3]);

  vector<Facility*> facilities;
  // load facilities data
  // Insert your code here

    ifstream file("./Facilities.txt");
    string line;
    assert(file.is_open()); // check if file is open
    while(getline(file,line)){
        Facility* aux = new Facility(line);  // Auxiliary object to help store information to vectors
        facilities.push_back(aux);
    }
  // sort facilities in order of proximity to the current position
  sort(facilities.begin(), facilities.end(),
       Closer(current_latitude,current_longitude));

  vector<Runway*> runways;
  // load runways data
  // Insert your code here
  ifstream fileR("./Runways.txt");
  string line_Runway;
  assert(fileR.is_open());
  while(getline(fileR,line_Runway)){
    Runway* aux = new Runway(line_Runway);
    runways.push_back(aux);
  }


  // list up to 10 nearest facilities that have a long enough runway
  // list each runway that is long enough
  int count = 0;
  for ( unsigned int i = 0; i < facilities.size() && count < 10; i++ )
  {
    Facility *a = facilities[i];

    // Find all runways of this facility that are long enough
    vector<Runway*> good_runways;
    // Insert your code here

      for(vector<Runway*>::iterator it =runways.begin(); it != runways.end() && *it != NULL;it++){

          it = find_if(it,runways.end(),SiteNumber(a,min_runway_length));
          if(*it == NULL)
            break;
        else
          good_runways.push_back(*it);

      }

    // print this facility if it has long enough runways
    if ( !good_runways.empty() )
    {
      // increment count of good facilities
      count++;

      cout << a->type() << " " << a->code() << " "
           << a->name() << " ";
      cout.setf(ios_base::fixed,ios_base::floatfield);
      cout.setf(ios_base::right, ios_base::adjustfield);
      cout.width(5);
      cout.precision(1);
      cout << a->distance(current_latitude,current_longitude)
           << " NM" << endl;
      // print all runways that are long enough
      for ( unsigned int i = 0; i < good_runways.size(); i++ )
      {
        Runway *r = good_runways[i];
        cout << "  Runway: " << r->name() << "  length: " << r->length()
             << " ft" << endl;
      }
    }
  }
}
