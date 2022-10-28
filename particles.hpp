#pragma once

#include <vector>
#include <string>
#include "allegro.hpp"
#include "vector.hpp"

using namespace std;


class Particle{
public:
    string type;
    double radius;
    ALLEGRO_COLOR color;
    Vector pos;
    Vector spd;
    Vector acc;
    Particle();
    Particle(double x, double y, double z, string type);
};