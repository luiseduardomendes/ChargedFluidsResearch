#include "box.hpp"

Box::Box(pdd x, pdd y, pdd z){
    this->inf.x = x.first;
    this->inf.y = y.first;
    this->inf.z = z.first;
    
    this->sup.x = x.second;
    this->sup.y = y.second;
    this->sup.z = z.second;
}
Box::Box(
    double ix, double iy, double iz,
    double fx, double fy, double fz
){
    this->inf.x = ix;
    this->inf.y = iy;
    this->inf.z = iz;
    
    this->sup.x = fx;
    this->sup.y = fy;
    this->sup.z = fz;
}
Box::Box(double x, double y, double z){
    this->inf.x = -x;
    this->inf.y = -y;
    this->inf.z = -z;
    
    this->sup.x = x;
    this->sup.y = y;
    this->sup.z = z;
}

Box::Box(double k){
    this->inf.x = -k;
    this->inf.y = -k;
    this->inf.z = -k;
    
    this->sup.x = k;
    this->sup.y = k;
    this->sup.z = k;
}

Box::Box(){
    this->inf.x = -100;
    this->inf.y = -100;
    this->inf.z = -100;
    
    this->sup.x = 100;
    this->sup.y = 100;
    this->sup.z = 100;
}