#pragma once

#include "particles.h"
#include "vector.h"

Particle **read_csv(char file_name[], int *);

Vector _calc_eletric_field(Vector point, Particle p);
double _calc_distance(Vector p1, Vector p2);
Vector _calc_lennard_jones(Particle p1, Particle p2);