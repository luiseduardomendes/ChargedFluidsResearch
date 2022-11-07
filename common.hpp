#pragma once

#include <vector>
#include <string>
#include "particles.hpp"
#include "vector.hpp"

using namespace std;

void read_csv(string file_name, vector<Particle*>&);
void split(string str, vector<float>& v, string& particle_type, char sep);
Vector _calc_eletric_field(Vector point, Particle p);
double _calc_distance(Vector p1, Vector p2);
Vector _calc_lennard_jones(Particle p1, Particle p2);
void _sort(vector<Particle *> &arr);