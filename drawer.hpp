#pragma once

#include "particles.hpp"
#include "allegro.hpp"
#include "vector.hpp"
#include <vector>
#include "box.hpp"

class Drawer{
private:
    double w, h;
    ALLEGRO_FONT* font;
    double conv; //zoom * CTE_CONV

    void vertical_line(double x, double thickness, ALLEGRO_COLOR color);
    void horizontal_line(double y, double thickness, ALLEGRO_COLOR color);
    void main_axis();
    void generic_grid(double linspace, ALLEGRO_COLOR color);
public:
    Drawer(double w, double h, double conv);
    Drawer();

    void update_conv(double conv);

    void vector(Vector a, Vector b, double size, double min_scale, double max_scale);
    void particle(Particle p, double z);
    void box(Box box, ALLEGRO_COLOR color, double thickness);
    void grid();
    void HUD();
};