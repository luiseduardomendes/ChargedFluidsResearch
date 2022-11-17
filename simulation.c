#include "simulation.h"

Simulation* SimulationCreate(char filename[], double fps, Box box){
    Simulation* sim = (Simulation*) malloc(sizeof(Simulation));
    sim->particles = read_csv(filename, &(sim->nParticles));

    sim->fps = fps;
    sim->box = box;

    return sim;
}

void SimulationUpdateParticlePosition(Simulation *sim){
    SimulationCalculateForces(sim);
    for (int i = 0; i < sim->nParticles; i ++){
        Particle *p = sim->particles[i];
        p->spd = VectorAdd(p->spd, VectorCteMult(p->acc, (1.0/sim->fps)));
        p->pos = VectorAdd(p->pos, VectorCteMult(p->spd, (1.0/sim->fps)));

        if (p->pos.x > sim->box.sup.x)
            p->pos.x = sim->box.inf.x;
        if (p->pos.x < sim->box.inf.x)
            p->pos.x = sim->box.sup.x;
        if (p->pos.y > sim->box.sup.y)
            p->pos.y = sim->box.inf.y;
        if (p->pos.y < sim->box.inf.y)
            p->pos.y = sim->box.sup.y;
        if (p->pos.z > sim->box.sup.z)
            p->pos.z = sim->box.inf.z;
        if (p->pos.z < sim->box.inf.z)
            p->pos.z = sim->box.sup.z;
    }
}