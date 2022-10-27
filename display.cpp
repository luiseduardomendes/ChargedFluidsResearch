#include "display.hpp"
#include <cmath>
#include <iostream>

#define CTE_CONV 5

Display::Display(int w, int h, double fps, double init_z, vector<Particle*> part){
    this->on = true;

    if (!(this->display = al_create_display(w, h)))
        this->on = false;

    this->w = w;
    this->h = h;

    this->current_z = init_z;
    
    this->particles = part;

    this->font = al_load_ttf_font("fonte.ttf", 36, 0);
    
    this->timer = al_create_timer(1.0/fps);
    al_start_timer(this->timer);
    this->paused = false;

    this->zoom = 1;

}

bool Display::is_on(){
    return this->on;
}

void Display::show(){
    al_clear_to_color(al_map_rgb(0x00, 0x11, 0x20));
    this->draw_grid();
    this->draw_particles();
    this->draw_HUD();
    al_flip_display();
}

void Display::draw_HUD(){
    // al_draw_textf(this->font, al_map_rgb(0xff,0xff,0xff), 2*w/3, h - 48, 0, "grid_lines = %.2lf", zoom*CTE_CONV*10);
}

void Display::draw_grid(){
    double i;
    i = this->w / 2.0;
    while (i < this->w){
        al_draw_line(i, 0, i, this->h, al_map_rgb(0x8f,0x8f,0x8f),2);
        i += zoom*CTE_CONV*10;
    }
    i = this->w / 2.0;
    while (i > 0){
        al_draw_line(i, 0, i, this->h, al_map_rgb(0x8f,0x8f,0x8f),2);
        i -= zoom*CTE_CONV*10;
    }

    i = this->h / 2;
    while (i < this->h){
        al_draw_line(0, i, this->w, i, al_map_rgb(0x8f,0x8f,0x8f),2);
        i += zoom*CTE_CONV*10;
    }
    i = this->h / 2;
    while (i > 0){
        al_draw_line(0, i, this->w, i, al_map_rgb(0x8f,0x8f,0x8f),2);
        i -= zoom*CTE_CONV*10;
    }
}

void Display::draw_particles(){
    for (auto p : (this->particles)){
        if (p->pos.z > this->current_z - p->radius && p->pos.z < this->current_z + p->radius){
            al_draw_filled_circle(
                p->pos.x*zoom*CTE_CONV + w/2, 
                p->pos.y*zoom*CTE_CONV + h/2,
                sqrt(abs(pow(p->radius, 2) - pow((p->pos.z-current_z), 2)))*zoom*CTE_CONV, 
                p->color
            );
            al_draw_circle(
                p->pos.x*zoom*CTE_CONV + w/2, 
                p->pos.y*zoom*CTE_CONV + h/2,
                sqrt(abs(pow(p->radius, 2) - pow((p->pos.z-current_z), 2)))*zoom*CTE_CONV, 
                al_map_rgb(0,0,0), 0.2*zoom*CTE_CONV
            );
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
