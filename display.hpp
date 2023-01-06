#pragma once

#include "allegro.hpp"
#include "particles.hpp"
#include "box.hpp"
#include <vector>

using namespace std;

typedef pair<double, double> pdd;

class Display{
private:   
    bool on;
    double fov;
    double zoom;
    double current_z;
    int h, w;
    Box *box;
    vector<Particle*> particles;
    bool paused;

    ALLEGRO_FONT *font;
public:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;

    Display(int, int, double, double, vector<Particle*>, Box*);

    void show_3d();
    void draw_particles_3d();
    void draw_box_3d();
    void draw_grid_3d();

    void show();
    void draw_particles();
    void draw_HUD();
    void draw_box();
    void draw_grid();
    void draw_vectors();

    bool is_on();
    
    void pause_play();
    bool is_paused();

    void inc_z();
    void dec_z();
    void inc_z(double inc);

    void zoom_out();
    void zoom_in();
    void zoom_rst();

    void fov_out();
    void fov_in();

    void draw_vector(Vec a, Vec b, double size, pdd range);
};