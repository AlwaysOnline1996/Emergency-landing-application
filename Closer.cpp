//
// Created by Flyer on 17-3-15.
//
#include <vector>
#include "Closer.h"
Closer::Closer(const double cur_lat,const double cur_lon):cur_la(cur_lat),cur_lo(cur_lon){
}
bool Closer::operator() (Facility* &a,Facility* &b){
    return a->distance(cur_la,cur_lo) < b->distance(cur_la,cur_lo);
}
