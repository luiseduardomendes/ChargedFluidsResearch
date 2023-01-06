#pragma once
#include "vector.hpp"
#include <vector>

struct Box{
    Vec inf, sup;
    Box(double,double,double,double,double,double);
    Box(double,double,double);
    Box(double);
    Box();
};