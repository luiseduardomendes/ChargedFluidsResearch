#pragma once

#include <vector>
#include <string>

using namespace std;

class Vec{
public:
    double x, y, z;
    Vec();
    Vec(double,double,double);
    template <typename T>
    Vec(T t);
    Vec operator+(Vec);
    Vec operator+(double);
    Vec operator-(Vec);
    Vec operator-(double);
    Vec operator*(Vec);
    Vec operator*(double);
    Vec operator/(double);
    Vec operator/(Vec);
    bool operator==(Vec);
    bool operator!=(Vec);
    double operator[](int);
    double operator[](char);
    bool operator<(Vec);
    bool operator>(Vec);
    bool operator<=(Vec);
    bool operator>=(Vec);
    double dot(Vec);
    Vec ort(Vec);
    Vec proj(Vec);
    double mag();
    Vec unit();
};