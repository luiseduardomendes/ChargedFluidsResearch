#include "particles.h"

Particle* ParticleCreateByType(char type[]) {
    Particle *particle = (Particle*) malloc(sizeof(Particle));
    if (strcmp(type, "Na") == 0){
        particle->charge = 1;
        particle->mass = 22.989769;
        particle->radius = 2.27;
        particle->color = al_map_rgb(0x93,0x05,0x25);
    }
    else if (strcmp(type, "Cl") == 0){
        particle->charge = -1;
        particle->mass = 35.453;
        particle->radius = 1.75;
        particle->color = al_map_rgb(0x0e,0x52,0x66);
    }
    else{
        particle->charge = 1;
        particle->mass = 1;
        particle->radius = 1;
        particle->color = al_map_rgb(0x80,0x80,0x80);
    }
    particle->pos = VectorCreateZero();
    particle->spd = VectorCreateZero();
    particle->acc = VectorCreateZero();

    return particle;
}
    
Particle *ParticleCreateByTypeAndInitState(char type[], Vector pos, Vector spd, Vector acc) {
    Particle *particle = ParticleCreateByType(type);
    particle->pos = pos;
    particle->spd = spd;
    particle->acc = acc;

    return particle;
}


Particle *ParticleCreateGeneric(char type[], double radius, ALLEGRO_COLOR color, Vector pos, Vector spd, Vector acc,
    double charge, double mass
){
    Particle *particle = ParticleCreateByTypeAndInitState(type, pos, spd, acc);
    particle->charge = charge;
    particle->mass = mass;
    particle->radius = radius;
    particle->color = color;
    
    return particle;
}