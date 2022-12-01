#pragma once
#include <vector>
#include <string>
#include "box.hpp"
#include "common.hpp"

using namespace std;

class Vector{
public:
    double x, y, z;
    Vector();
    Vector(double,double,double);
    Vector(Box);
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
    bool operator==(Vector);
    bool operator!=(Vector);
    double operator[](int);
    double operator[](char);
    bool operator<(Vector);
    bool operator>(Vector);
    bool operator<=(Vector);
    bool operator>=(Vector);
    double dot(Vector);
    Vector ort(Vector);
    Vector proj(Vector);
    double mag();
    Vector unit();


};