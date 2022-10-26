#pragma once

#include "allegro.hpp"
#include "particles.hpp"
#include <vector>

using namespace std;

class Display{
private:   
    bool on;
    double current_z;
    int h, w;
    vector<Particle*> particles;
    bool paused;
public:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;
    Display();
    Display(int, int, double, double, vector<Particle*>);
    void draw_particles();
    void draw_grid();
    bool is_on();
    void pause_play();
    bool is_paused();

    void inc_z();
    void dec_z();
    void inc_z(double inc);
};