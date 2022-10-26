#pragma once

#include <vector>
#include <string>
#include "particles.hpp"

using namespace std;

void read_csv(string file_name, vector<Particle*>&);
void split(string str, vector<float>& v, string& particle_type, char sep);