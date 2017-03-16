//
// Created by Flyer on 17-3-15.
//
#include "Facility.h"
#include "gcdistance.h"
#include <cstdlib>

Facility::Facility(std::string s):latitude_(convert_latitude(s)),longitude_(convert_longitude(s)),site_number_(s.substr(0,10)),type_(s.substr(11,13)),code_(s.substr(24,4)),name_(s.substr(130,50)){

}


double Facility::convert_latitude(std::string s) const {
    char aux[12];  // auxiliary char array for using atof funcition to convert.
    for(int position = 535; position < 546; position++){
        aux[position - 535] = s[position];
    }
    if(s[546] == 'N')
        return atof(aux)/3600;
    else
        return -1*atof(aux)/3600;
}
double Facility::convert_longitude(std::string s) const {
    char aux[12];
    for(int position = 562; position < 573; position++){
        aux[position - 562] = s[position];
    }
    if(s[573] == 'W')
        return -1*atof(aux)/3600;
    else
        return atof(aux);
}

std::string Facility::site_number() const {
    return this->site_number_;
}

std::string Facility::type() const {
    return this->type_;
}
std::string Facility::code() const {
    return this->code_;
}
std::string Facility::name() const {
    return this->name_;
}
double Facility::latitude() const {
    return this->latitude_;
}
double Facility::longitude() const {
    return this->longitude_;
}
double Facility::distance(double lat, double lon) const {
    return gcdistance(lat,lon,this->latitude_,this->longitude_);
}