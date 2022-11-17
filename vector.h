#pragma once

typedef struct vector{
    double x, y, z;
} Vector;


Vector VectorCreateZero();
Vector VectorCreateInitState(double x, double y, double z);
Vector VectorAdd(Vector v1, Vector v2);
Vector VectorSub(Vector v1, Vector v2);
Vector VectorMult(Vector v1, Vector v2);
Vector VectorDiv(Vector v1, Vector v2);
Vector VectorCteAdd(Vector v1, double k);
Vector VectorCteSub(Vector v1, double k);
Vector VectorCteMult(Vector v1, double k);
Vector VectorCteDiv(Vector v1, double k);
double VectorDot(Vector v1, Vector v2);
double VectorMag(Vector v);
int    VectorCmp(Vector v1, Vector v2);
Vector VectorOrt(Vector v1, Vector v2);

