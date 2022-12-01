#pragma once

#include "vector.hpp"
#include <vector>
#include "particles.hpp"
#include "common.hpp"
#include "box.hpp"

class PhysicEvents{
    private:
        
        std::vector<Particle*>* particles;
        Box box;
        double detalT;

        void calculate_particle_position(Particle *i);
        void calculate_particle_speed(Particle *i);
        void check_particle_outside_box(Particle *i);

        void calculate_forces();
        void resultant_vector(Particle *p);
        Vector eletric_field_in_position(Vector pos);
        Vector eletric_field(Particle p);
        Vector lennard_jones(Particle p);
    public:
        PhysicEvents();
        PhysicEvents(std::vector<Particle*>* particles, Box box, double deltaT);
        void calculate_new_system_status();
};


