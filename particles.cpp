#include "particles.hpp"
#include <iostream>

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


    if (type == "Na"){
        this->radius = 2.27;
        this->color = al_map_rgb(255,95,107);
    }
    else if (type == "Cl"){
        this->radius = 1.75;
        this->color = al_map_rgb(128,206,225);
    }
    else{
        this->color = al_map_rgb(255,255,255);
    }
}