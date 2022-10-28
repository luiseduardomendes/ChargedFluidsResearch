#include "particles.hpp"
#include <iostream>

Particle::Particle(){
    this->pos = Vector();
    this->type = "None";
}

Particle::Particle(double x, double y, double z, string type){
    this->pos = Vector(x, y, z);
    this->spd = Vector((rand()%3 - 1), (rand()%3 - 1), (rand()%3 - 1));
    this->spd = Vector();
    this->acc = Vector();
    this->type = type;

    if (type == "Na"){
        this->radius = 2.27;
        this->color = al_map_rgb(0x93,0x05,0x25);
    }
    else if (type == "Cl"){
        this->radius = 1.75;
        this->color = al_map_rgb(0x0e,0x52,0x66);
    }
    else{
        this->color = al_map_rgb(255,255,255);
    }
}