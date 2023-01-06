#pragma once

#include <vector>
#include <string>
#include "particles.hpp"
#include "vector.hpp"
#include "box.hpp"

using namespace std;

void read_csv(string file_name, vector<Particle*>&);
void split(string str, vector<float>& v, string& particle_type, char sep);
Vec _calc_eletric_field(Vec point, Particle p);
double _calc_distance(Vec p1, Vec p2);
Vec _calc_lennard_jones(Particle p1, Particle p2);
void _sort(vector<Particle *> &arr);
Vec gausran_vector();
double gausran(); // generate random gaussian numbers
double unirand(double min, double max); // generate random numbers between min and max
Vec random_pos_in_box(Box box);
bool check_colision(vector<Particle*> v, Particle* part);
bool colide(Particle p1, Particle p2);