#pragma once

#include "allegro.hpp"
#include "particles.hpp"
#include "box.hpp"
#include <vector>

using namespace std;

class Display{
private:   
    bool on;
    double zoom;
    double current_z;
    int h, w;
    Box box;
    vector<Particle*> particles;
    bool paused;

    ALLEGRO_FONT *font;
public:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;

    Display(int, int, double, double, vector<Particle*>, Box);

    void show();
    void draw_particles();
    void draw_HUD();
    void draw_box();
    void draw_grid();

    bool is_on();
    
    void pause_play();
    bool is_paused();

    void inc_z();
    void dec_z();
    void inc_z(double inc);

    void zoom_out();
    void zoom_in();
    void zoom_rst();
};