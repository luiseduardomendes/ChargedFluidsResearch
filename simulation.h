#pragma once

#include "particles.h"
#include "box.h"
#include "common.h"
#include "vector.h"

typedef struct Simulation{
    int nParticles;
    Particle **particles;

    double fps;
    Box box;
} Simulation;

Simulation* SimulationCreate(char filename[], double, Box);

void SimulationCalculateForces(Simulation *);
void SimulationResultantVector(Simulation *, Particle *p);
Vector SimulationEletricFieldIn(Simulation *, Vector pos);
Vector SimulationLennardJones(Simulation *, Particle p);
void SimulationUpdateParticlePosition(Simulation *);