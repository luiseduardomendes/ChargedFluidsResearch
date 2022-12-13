#include "display.hpp"
#include "common.hpp"
#include <algorithm>
#include <cmath>
#include <iostream>

#define CTE_CONV 5

Display::Display(int w, int h, double fps, double init_z, vector<Particle*> part, Box *box){
    this->on = true;

    if (!(this->display = al_create_display(w, h)))
        this->on = false;

    this->w = w;
    this->h = h;

    this->current_z = init_z;
    
    this->particles = part;

    al_init_ttf_addon();
    this->font = al_load_ttf_font("fonte.ttf", 36, 0);

    draw = Drawer(w, h, zoom*CTE_CONV);
    
    this->timer = al_create_timer(1.0/fps);
    al_start_timer(this->timer);
    this->paused = false;

    this->zoom = 2.5;
    this->fov = 1;
    this->box = box;

}

bool Display::is_on(){
    return this->on;
}

void Display::show(){
    draw.update_conv(zoom*CTE_CONV);

    al_clear_to_color(al_map_rgb(0x00, 0x11, 0x20));
    draw.grid();
    this->draw_particles();
    
    draw.box(*(this->box), al_map_rgb(0xc0,0xc0,0xc0), 2);
    draw.HUD();

    al_flip_display();
}


void Display::show_3d(){
    al_clear_to_color(al_map_rgb(0x00, 0x11, 0x20));
    //this->draw_box_3d();
    //this->draw_particles_3d();
    al_flip_display();
}

void Display::draw_particles(){
    for (auto p : (this->particles)){
        if (p->pos.z > this->current_z - p->radius && p->pos.z < this->current_z + p->radius){
            
            Vector v(p->pos.x*zoom*CTE_CONV + w/2, p->pos.y*zoom*CTE_CONV + h/2, 0);
            draw.vector(v, v+p->acc, 10, 0, 5);
        }
    }
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

void Display::zoom_out(){
    this->zoom *= 0.9;
}

void Display::zoom_in(){
    this->zoom *= 1.1;
}

void Display::zoom_rst(){
    this->zoom = 1;
}

void Display::fov_out(){
    this->fov *= 1.1;
}

void Display::fov_in(){
    this->fov *= 0.9;
}