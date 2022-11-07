#include "vector.hpp"
#include <cstring>

Vector::Vector(){
    x = 0;
    y = 0;
    z = 0;
}
Vector::Vector(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}
template <typename T>
Vector::Vector(T t){
    this->x = t[0];
    this->y = t[1];
    this->z = t[2];
}
double Vector::operator[](int i){
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
double Vector::operator[](char c){
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
bool Vector::operator<(Vector v){
    return z < v.z;
}
bool Vector::operator>(Vector v){
    return z > v.z;
}
bool Vector::operator<=(Vector v){
    return z <= v.z;
}
bool Vector::operator>=(Vector v){
    return z >= v.z;
}
Vector Vector::operator+(Vector v){
    Vector temp;
    temp.x = this->x + v.x;
    temp.y = this->y + v.y;
    temp.z = this->z + v.z;
    return temp;
}
Vector Vector::operator+(double i){
    Vector temp;
    temp.x = this->x + i;
    temp.y = this->y + i;
    temp.z = this->z + i;
    return temp;
}
Vector Vector::operator-(Vector v){
    Vector temp;
    temp.x = this->x - v.x;
    temp.y = this->y - v.y;
    temp.z = this->z - v.z;
    return temp;
}
Vector Vector::operator-(double i){
    Vector temp;
    temp.x = this->x - i;
    temp.y = this->y - i;
    temp.z = this->z - i;
    return temp;
}
Vector Vector::operator*(Vector v){
    Vector temp;
    temp.x = this->x * v.x;
    temp.y = this->y * v.y;
    temp.z = this->z * v.z;
    return temp;
}
Vector Vector::operator*(double i){
    Vector temp;
    temp.x = this->x * i;
    temp.y = this->y * i;
    temp.z = this->z * i;
    return temp;
}
Vector Vector::operator/(Vector v){
    Vector temp;
    temp.x = this->x / v.x;
    temp.y = this->y / v.y;
    temp.z = this->z / v.z;
    return temp;
}
Vector Vector::operator/(double i){
    Vector temp;
    temp.x = this->x / i;
    temp.y = this->y / i;
    temp.z = this->z / i;
    return temp;
}
bool Vector::operator==(Vector v){
    if (v.x == x && v.y == y && v.z == z)
        return true;
    else
        return false;
}
bool Vector::operator!=(Vector v){
    if (v.x == x && v.y == y && v.z == z)
        return false;
    else
        return true;
}
double Vector::dot(Vector v){
    return (x*v.x + y*v.y + z*v.z);
}
Vector Vector::ort(Vector v){
    Vector temp;
    temp.x = y*v.z - z*v.y;
    temp.y = z*v.x - x*v.z;
    temp.y = x*v.y - y*v.x;
    return temp;
}
