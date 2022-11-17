#pragma once

#include "allegro.h"
#include "particles.h"
#include "box.h"
#include <math.h>

typedef struct Display{
    bool on;
    double zoom;
    double current_z;
    int h, w;
    Box box;
    int num_particles;
    Particle** particles;
    bool paused;

    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;

    
}Display;


Display *Display_Create(int w, int h, double fps, double init_z, int num_particles, Particle* part[], Box box);
bool Display_is_on(Display *display);
void Display_show(Display *display);
void Display_draw_HUD(Display *display);
void Display_draw_box(Display *display);
void Display_draw_grid(Display *display);
void Display_draw_particles(Display *display);
void Display_pause_play(Display *display);
bool Display_is_paused(Display *display);
void Display_inc_z(Display *display);
void Display_dec_z(Display *display);
void Display_inc_z_cte(Display *display, double inc);
void Display_zoom_out(Display *display);
void Display_zoom_in(Display *display);
void Display_zoom_rst(Display *display);