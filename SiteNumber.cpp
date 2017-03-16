//
// Created by Flyer on 17-3-15.
//

#include "SiteNumber.h"
SiteNumber::SiteNumber(Facility* &fa, const int le):min_runway_length(le),f(fa){
}
bool SiteNumber::operator() (Runway* &r){
    return (r->site_number() == f->site_number() ) && (r->length() >= this->min_runway_length);
}