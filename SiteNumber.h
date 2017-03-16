//
// Created by Flyer on 17-3-15.
//

#ifndef SITENUMBER_H
#define SITENUMBER_H

#include "Facility.h"
#include "Runway.h"
class SiteNumber
{
public:
    SiteNumber(Facility* &f, const int le);
    bool operator() (Runway* &r);

private:
    const int min_runway_length;
    const Facility* f;
};
#endif //SITENUMBER_H
