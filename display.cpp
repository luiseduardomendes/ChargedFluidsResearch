#include "display.hpp"
#include <cmath>
#include <iostream>

#define CTE_DIM 7.5

Display::Display(int w, int h, double fps, double init_z, vector<Particle*> part){
    this->on = true;

    if (!(this->display = al_create_display(w, h)))
        this->on = false;

    this->w = w;
    this->h = h;

    this->current_z = init_z;
    
    this->particles = part;
    
    this->timer = al_create_timer(1.0/fps);
    al_start_timer(this->timer);
    this->paused = false;

}

Display::Display(){
    current_z = 0;
}

bool Display::is_on(){
    return this->on;
}

void Display::draw_particles(){
    al_clear_to_color(al_map_rgb(0,0,0));
    for (auto p : (this->particles)){
        if (p->pos.z > this->current_z - p->radius && p->pos.z < this->current_z + p->radius)
            al_draw_filled_circle(
                p->pos.x*CTE_DIM + w/2, 
                p->pos.y*CTE_DIM + h/2,
                sqrt(abs(pow(p->radius, 2) - pow((p->pos.z-current_z), 2)))*CTE_DIM, 
                p->color
            );
    }
    al_flip_display();
}

void Display::pause_play(){
    if (this->paused){
        this->paused = false;
    }
    else{
        this->paused = true;
    }
}

bool Display::is_paused(){
    return this->paused;
}

void Display::inc_z(){
    current_z += 1;
}

void Display::dec_z(){
    current_z -= 1;
}

void Display::inc_z(double inc){
    current_z += inc;
}
