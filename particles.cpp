#include "particles.hpp"

Particle::Particle(){
    this->pos.x = 0;
    this->pos.y = 0;
    this->pos.z = 0;
    this->type = "None";
}

Particle::Particle(double x, double y, double z, string type){
    this->pos.x = x;
    this->pos.y = y;
    this->pos.z = z;
    this->type = type;

    this->radius = 5;
    this->color = al_map_rgb(128, 206, 225);

    if (type == "Na"){
        this->color = al_map_rgb(255, 105, 97);
    }
    else if (type == "Cl"){
        this->color = al_map_rgb(128, 206, 225);
    }
}