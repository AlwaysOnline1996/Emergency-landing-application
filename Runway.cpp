//
// Created by Flyer on 17-3-15.
//

#include "Runway.h"
#include <cstdlib>
Runway::Runway(std::string s):site_number_(s.substr(0,10)),name_(s.substr(13,7)),length_(convert_length(s)) {
}

int Runway::convert_length(std::string s) const {
    char aux[5];
    for(int position = 20; position < 25;position++){
        aux[position - 20] = s[position];
    }
    return atoi(aux);
}

std::string Runway::site_number() const {
    return site_number_;
}

std::string Runway::name() const {
    return name_;
}
int Runway::length() const {

    return length_;
}