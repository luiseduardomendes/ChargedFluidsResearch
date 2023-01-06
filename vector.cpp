#include "vector.hpp"
#include <cstring>
#include <cmath>

Vec::Vec(){
    x = 0;
    y = 0;
    z = 0;
}
Vec::Vec(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}
template <typename T>
Vec::Vec(T t){
    this->x = t[0];
    this->y = t[1];
    this->z = t[2];
}
double Vec::operator[](int i){
    switch (i){
    case 0:
        return x;
        break;
    case 1:
        return y;
        break;
    case 2:
        return z;
        break;
    default:
        return 0;
        break;
    }
}
double Vec::operator[](char c){
    switch (c){
    case 'x': case 'X':
        return x;
        break;
    case 'y': case 'Y':
        return y;
        break;
    case 'z': case 'Z':
        return z;
        break;
    default:
        return 0;
        break;
    }
}
bool Vec::operator<(Vec v){
    return z < v.z;
}
bool Vec::operator>(Vec v){
    return z > v.z;
}
bool Vec::operator<=(Vec v){
    return z <= v.z;
}
bool Vec::operator>=(Vec v){
    return z >= v.z;
}
Vec Vec::operator+(Vec v){
    Vec temp;
    temp.x = this->x + v.x;
    temp.y = this->y + v.y;
    temp.z = this->z + v.z;
    return temp;
}
Vec Vec::operator+(double i){
    Vec temp;
    temp.x = this->x + i;
    temp.y = this->y + i;
    temp.z = this->z + i;
    return temp;
}
Vec Vec::operator-(Vec v){
    Vec temp;
    temp.x = this->x - v.x;
    temp.y = this->y - v.y;
    temp.z = this->z - v.z;
    return temp;
}
Vec Vec::operator-(double i){
    Vec temp;
    temp.x = this->x - i;
    temp.y = this->y - i;
    temp.z = this->z - i;
    return temp;
}
Vec Vec::operator*(Vec v){
    Vec temp;
    temp.x = this->x * v.x;
    temp.y = this->y * v.y;
    temp.z = this->z * v.z;
    return temp;
}
Vec Vec::operator*(double i){
    Vec temp;
    temp.x = this->x * i;
    temp.y = this->y * i;
    temp.z = this->z * i;
    return temp;
}
Vec Vec::operator/(Vec v){
    Vec temp;
    temp.x = this->x / v.x;
    temp.y = this->y / v.y;
    temp.z = this->z / v.z;
    return temp;
}
Vec Vec::operator/(double i){
    Vec temp;
    temp.x = this->x / i;
    temp.y = this->y / i;
    temp.z = this->z / i;
    return temp;
}
bool Vec::operator==(Vec v){
    if (v.x == x && v.y == y && v.z == z)
        return true;
    else
        return false;
}
bool Vec::operator!=(Vec v){
    if (v.x == x && v.y == y && v.z == z)
        return false;
    else
        return true;
}
double Vec::dot(Vec v){
    return (x*v.x + y*v.y + z*v.z);
}
Vec Vec::ort(Vec v){
    Vec temp;
    temp.x = y*v.z - z*v.y;
    temp.y = z*v.x - x*v.z;
    temp.z = x*v.y - y*v.x;
    return temp;
}

double Vec::mag(){
    return (sqrt(x*x + y*y + z*z));
}

Vec Vec::unit(){
    double mag = this->mag();
    Vec temp(x/mag, y/mag, z/mag);
    return temp;
}

Vec Vec::proj(Vec v){
    Vec temp(x, y, z);
    return temp * v / (v.mag() * temp.mag());
    
}

