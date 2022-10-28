#pragma once
#include <vector>

class Vector{
public:
    double x, y, z;
    Vector();
    Vector(double,double,double);
    template <typename T>
    Vector(T t);
    Vector operator+(Vector);
    Vector operator+(double);
    Vector operator-(Vector);
    Vector operator-(double);
    Vector operator*(Vector);
    Vector operator*(double);
    Vector operator/(double);
    Vector operator/(Vector);
    double operator[](int);
    double operator[](char);
    double dot(Vector);
    Vector ort(Vector);


};