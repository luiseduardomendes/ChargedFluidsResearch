#pragma once

#include <vector>
#include <string>
#include "allegro.hpp"
#include "vector.hpp"
#include "box.hpp"

using namespace std;

class Particle{
public:
    string type;
    double radius;
    ALLEGRO_COLOR color;
    Vec pos;
    Vec spd;
    Vec acc;
    double charge;
    double mass;
    Particle();
    Particle(double x, double y, double z, string type);
    Particle(string type);

    void random_position(Box box);

    void switch_particle_type(string type);

    bool operator<(Particle);
    bool operator>(Particle);
    bool operator<=(Particle);
    bool operator>=(Particle);
};