#include "display.hpp"

Display::Display(int w, int h, double fps, double init_z, double range_z, vector<Particle*> part){
    this->on = true;

    if (!(this->display = al_create_display(w, h)))
        this->on = false;

    this->current_z = init_z;
    this->range_z = range_z;
    
    this->particles = part;
    
    this->timer = al_create_timer(1.0/fps);
}

Display::Display(){
    current_z = 0;
    range_z = 0;
}

bool Display::is_on(){
    return this->on;
}

void Display::draw_particles(){
    for (auto p : (this->particles)){
        if (p->pos.z > this->current_z - this->range_z && p->pos.z < this->current_z + this->range_z)
            al_draw_filled_circle(p->pos.x, p->pos.y, p->radius, p->color);
    }
}