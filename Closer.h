//
// Created by Flyer on 17-3-15.
//

#ifndef CLOSER_H
#define CLOSER_H

#include "Facility.h"
class Closer
{
public:
    Closer(const double cur_lat,const double cur_lon);
    bool operator() (Facility* &a,Facility* &b);
private:
    const double cur_la;
    const double cur_lo;
};
#endif //CLOSER_H
