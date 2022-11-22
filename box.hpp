#pragma once
#include "vector.hpp"
#include <vector>

typedef pair<double, double> pdd;

struct Box{
    Vector inf, sup;
    Box(pdd,pdd,pdd);
    Box(double,double,double,double,double,double);
    Box(double,double,double);
    Box(double);
    Box();
};