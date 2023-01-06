#include "particles.hpp"
#include "common.hpp"
#include <iostream>

Particle::Particle(){
    this->pos = Vec();
    this->type = "None";
}

Particle::Particle(double x, double y, double z, string type){
    this->pos = Vec(x,y,z);
    this->spd = Vec(0,0,0);
    this->acc = Vec(0,0,0);
    this->type = type;

    this->switch_particle_type(type);
}

Particle::Particle(string type){
    random_position(Box());
    this->spd = Vec(0,0,0);
    this->acc = Vec(0,0,0);
    this->type = type;

    this->switch_particle_type(type);
}

bool Particle::operator<(Particle p){
    return this->pos < p.pos;
}

bool Particle::operator>(Particle p){
    return this->pos > p.pos;
}

bool Particle::operator<=(Particle p){
    return this->pos <= p.pos;
}

bool Particle::operator>=(Particle p){
    return this->pos >= p.pos;
}

void Particle::switch_particle_type(string type){
    if (type == "Na"){
        this->charge = 2;
        this->mass = 22.989769;
        this->radius = 2.27;
        this->color = al_map_rgb(0x93,0x05,0x25);
    }
    else if (type == "Cl"){
        this->charge = -2;
        this->mass = 35.453;
        this->radius = 1.75;
        this->color = al_map_rgb(0x0e,0x52,0x66);
    }
    else{
        this->charge = 1;
        this->mass = 1;
        this->radius = 1;
        this->color = al_map_rgb(255,255,255);
    }
}

void Particle::random_position(Box box){
    this->pos = random_pos_in_box(box);
}