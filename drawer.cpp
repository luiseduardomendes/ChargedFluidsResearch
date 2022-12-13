#include "drawer.hpp"
#include <cmath>

Drawer::Drawer(){}
Drawer::Drawer(double w, double h, double conv){
    this->w = w;
    this->h = h;
    this->conv = conv;
}

void Drawer::update_conv(double conv){
    this->conv = conv;
}

void Drawer::grid(){
    double i;
    ALLEGRO_COLOR sec_grid_color = al_map_rgb(0x2f,0x2f,0x2f);
    ALLEGRO_COLOR main_grid_color = al_map_rgb(0x8f,0x8f,0x8f); 

    generic_grid(conv*10, main_grid_color);
    generic_grid(conv*2.5, sec_grid_color);
    main_axis();
}

void Drawer::generic_grid(double linspace, ALLEGRO_COLOR color){
    double i = this->w / 2.0;
    while(i > 0) {i -= linspace;}
    while (i < this->w){
        vertical_line(i, 1, color);
        i += linspace;
    }

    i = this->h / 2;
    while(i > 0) {i -= linspace;}
    while (i < this->h){
        horizontal_line(i, 1, color);
        i += linspace;
    }
}

void Drawer::main_axis(){
    ALLEGRO_COLOR main_ax_color = al_map_rgb(0xcf,0xcf,0xcf);
    vertical_line(w/2.0, 2, main_ax_color);
    horizontal_line(h/2.0, 2, main_ax_color);
}

void Drawer::vertical_line(double x, double thickness, ALLEGRO_COLOR color){
    al_draw_line(
        x, 0, 
        x, h, 
        color, 
        thickness
    );
}

void Drawer::horizontal_line(double y, double thickness, ALLEGRO_COLOR color){
    al_draw_line(
        0, y, 
        w, y, 
        color, 
        thickness
    );
}

void Drawer::HUD(){
    al_draw_textf(this->font, al_map_rgb(0xff,0xff,0xff), 2*w/3, h - 48, 0, "grid line dimension = %dÅ ", 10);
}

void Drawer::box(Box box, ALLEGRO_COLOR color, double thickness){
    al_draw_rectangle(
        box.inf.x * conv + w/2, 
        box.inf.y * conv + h/2, 
        box.sup.x * conv + w/2, 
        box.sup.y * conv + h/2, 
        color,
        thickness
    );
}

void Drawer::particle(Particle p, double z){
    al_draw_filled_circle(
        p.pos.x*conv + w/2, 
        p.pos.y*conv + h/2,
        sqrt(abs(pow(p.radius, 2) - pow((p.pos.z-z), 2)))*conv, 
        p.color
    );
    al_draw_circle(
        p.pos.x*conv + w/2, 
        p.pos.y*conv + h/2,
        sqrt(abs(pow(p.radius, 2) - pow((p.pos.z-z), 2)))*conv, 
        al_map_rgb(0,0,0), 0.2*p.radius*conv
    );
}

void Drawer::vector(Vector a, Vector b, double size, double min, double max){
    /*magnitude is given by grey scale*/
    double t = 3/(max - min);
    Vector v = b - a;
    double c = 0xFF*v.mag()/(max - min);
    ALLEGRO_COLOR color = al_map_rgb(c, c, c);
    v = v.unit();
    v = Vector(v.x, v.y, 0);
    al_draw_line(a.x-v.x*size/2, a.y-v.y*size/2, a.x+v.x*size/2, a.y+v.y*size/2, color, 3);
    Vector o = v.ort(Vector(0,0,1)).unit()*size/2;
    double x = a.x+v.x*size/2;
    double y = a.y+v.y*size/2;
    
    al_draw_filled_triangle(x+o.x, y+o.y, x-o.x, y-o.y, x+v.x*size/2, y+v.y*size/2, color);
}
