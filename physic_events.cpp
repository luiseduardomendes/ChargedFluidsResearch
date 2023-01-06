#include "physic_events.hpp"

PhysicEvents::PhysicEvents(){
    this->particles = NULL;
    this->box = Box();
    this->detalT = 1/60.0;
}

PhysicEvents::PhysicEvents(std::vector<Particle*>* particles, Box box, double deltaT){
    this->particles = particles;
    this->box = box;
    this->detalT = deltaT;
}

void PhysicEvents::calculate_new_system_status(){
    calculate_forces();
    for (auto i : *(this->particles)){
        calculate_particle_position(i);
        calculate_particle_speed(i);

        check_particle_outside_box(i);
    }
}

void PhysicEvents::calculate_particle_position(Particle *i){
    i->pos = i->pos + (i->spd * (this->detalT));
}

void PhysicEvents::calculate_particle_speed(Particle *i){
    i->spd = i->spd + (i->acc * (this->detalT));
}

void PhysicEvents::check_particle_outside_box(Particle *i){
    if (i->pos.x > box.sup.x)
        i->pos.x = box.inf.x;
    if (i->pos.x < box.inf.x)
        i->pos.x = box.sup.x;
    if (i->pos.y > box.sup.y)
        i->pos.y = box.inf.y;
    if (i->pos.y < box.inf.y)
        i->pos.y = box.sup.y;
    if (i->pos.z > box.sup.z)
        i->pos.z = box.inf.z;
    if (i->pos.z < box.inf.z)
        i->pos.z = box.sup.z;
}

Vec PhysicEvents::eletric_field_in_position(Vec pos){
    Vec E(0,0,0);

    for (auto p : *(this->particles)){
        if (_calc_distance(p->pos, pos) > p->radius){
            E = E + _calc_eletric_field(pos, *p);
        }
    }    

    return E;
}

Vec PhysicEvents::eletric_field(Particle p){
    return (eletric_field_in_position(p.pos) * p.charge) / p.mass;
}

Vec PhysicEvents::lennard_jones(Particle p){
    Vec L(0,0,0);
    for (auto q : *(this->particles)){
        if (_calc_distance(p.pos, q->pos) > p.radius+q->radius){
            L = L + _calc_lennard_jones(p, *q);
        }
    }
    return L;

}

void PhysicEvents::resultant_vector(Particle *p){
    Vec acc(0,0,0);
    //acc = acc + eletric_field(*p);
    acc = acc + lennard_jones(*p);

    p->acc = acc;
}


void PhysicEvents::calculate_forces(){
    for (auto p : *(this->particles))
        this->resultant_vector(p);
}