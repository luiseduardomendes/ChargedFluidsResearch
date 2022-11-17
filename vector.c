#include "vector.h"
#include <math.h>

Vector VectorCreateZero(){
    Vector v;
    v.x = 0;
    v.y = 0;
    v.z = 0;
    return v;
}

Vector VectorCreateInitState(double x, double y, double z){
    Vector v;
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

Vector VectorAdd(Vector v1, Vector v2){
    Vector v;
    v.x = v1.x + v2.x;
    v.y = v1.y + v2.y;
    v.z = v1.z + v2.z;
    return v;
}

Vector VectorSub(Vector v1, Vector v2){
    Vector v;
    v.x = v1.x - v2.x;
    v.y = v1.y - v2.y;
    v.z = v1.z - v2.z;
    return v;
}

Vector VectorMult(Vector v1, Vector v2){
    Vector v;
    v.x = v1.x * v2.x;
    v.y = v1.y * v2.y;
    v.z = v1.z * v2.z;
    return v;
}

Vector VectorDiv(Vector v1, Vector v2){
    Vector v;
    v.x = v1.x / v2.x;
    v.y = v1.y / v2.y;
    v.z = v1.z / v2.z;
    return v;
}


Vector VectorCteAdd(Vector v1, double k){
    Vector v;
    v.x = v1.x + k;
    v.y = v1.y + k;
    v.z = v1.z + k;
    return v;
}

Vector VectorCteSub(Vector v1, double k){
    Vector v;
    v.x = v1.x - k;
    v.y = v1.y - k;
    v.z = v1.z - k;
    return v;
}

Vector VectorCteMult(Vector v1, double k){
    Vector v;
    v.x = v1.x * k;
    v.y = v1.y * k;
    v.z = v1.z * k;
    return v;
}

Vector VectorCteDiv(Vector v1, double k){
    Vector v;
    v.x = v1.x / k;
    v.y = v1.y / k;
    v.z = v1.z / k;
    return v;
}

double VectorDot(Vector v1, Vector v2){
    return (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
}

double VectorMag(Vector v){
    return sqrt(VectorDot(v, v));
}

int VectorCmp(Vector v1, Vector v2){
    if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z){
        return 0;
    }
    else{
        if (VectorMag(v1) > VectorMag(v2)){
            return 1;
        }
        else{
            return -1;
        }
    }
}

Vector VectorOrt(Vector v1, Vector v2){
    Vector temp;
    temp.x = v1.y*v2.z - v1.z*v2.y;
    temp.y = v1.z*v2.x - v1.x*v2.z;
    temp.z = v1.x*v2.y - v1.y*v2.x;
    return temp;
}
