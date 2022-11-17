#pragma once

#include "vector.h"
#include <string.h>
#include "allegro.h"

typedef struct Particle{
    char type[3];
    double radius;
    ALLEGRO_COLOR color;
    Vector pos;
    Vector spd;
    Vector acc;
    double charge;
    double mass;
} Particle;

Particle *ParticleCreateByType(char type[]);
Particle *ParticleCreateByTypeAndInitState(char type[], Vector pos, Vector spd, Vector acc);
Particle *ParticleCreateGeneric(char type[], double radius, ALLEGRO_COLOR color, Vector pos, Vector spd, Vector acc,
    double charge, double mass
);