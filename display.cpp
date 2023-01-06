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

    al_init_font_addon();
    al_init_ttf_addon();
    this->font = al_load_ttf_font("fonte.ttf", 36, 0);
    
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
    al_clear_to_color(al_map_rgb(0x00, 0x11, 0x20));
    this->draw_grid();
    this->draw_particles();
    
    this->draw_box();
    this->draw_HUD();

    al_flip_display();
}

void Display::show_3d(){
    al_clear_to_color(al_map_rgb(0x00, 0x11, 0x20));
    this->draw_box_3d();
    this->draw_particles_3d();
    al_flip_display();
}

void Display::draw_particles_3d(){
    auto temp = this->particles;
    _sort(temp);
    
    for (auto p : temp){

        double cte = (p->pos.z*fov/(box->sup.z-box->inf.z) + 1*fov);

        al_draw_filled_circle(
            p->pos.x*zoom*CTE_CONV*cte + w/2, 
            p->pos.y*zoom*CTE_CONV*cte + h/2,
            p->radius*zoom*CTE_CONV*cte, 
            p->color
        );

        al_draw_circle(
            p->pos.x*zoom*CTE_CONV*cte + w/2, 
            p->pos.y*zoom*CTE_CONV*cte + h/2,
            p->radius*zoom*CTE_CONV*cte, 
            al_map_rgb(0,0,0), 0.2*p->radius*zoom*CTE_CONV*cte
        );
    }    
}

void Display::draw_box_3d(){
    double cte_h = 1.5*fov;
    double cte_l = 0.5/fov;
    al_draw_rectangle(
        box->inf.x * zoom*CTE_CONV*cte_h + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_h + h/2, 
        box->sup.x * zoom*CTE_CONV*cte_h + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_h + h/2, 
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
    al_draw_rectangle(
        box->inf.x * zoom*CTE_CONV*cte_l + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_l + h/2, 
        box->sup.x * zoom*CTE_CONV*cte_l + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_l + h/2, 
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
    al_draw_line(
        box->inf.x * zoom*CTE_CONV*cte_l + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_l + h/2, 
        box->inf.x * zoom*CTE_CONV*cte_h + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_h + h/2,
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
    al_draw_line(
        box->sup.x * zoom*CTE_CONV*cte_l + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_l + h/2, 
        box->sup.x * zoom*CTE_CONV*cte_h + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_h + h/2,
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
    al_draw_line(
        box->inf.x * zoom*CTE_CONV*cte_l + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_l + h/2, 
        box->inf.x * zoom*CTE_CONV*cte_h + w/2, 
        box->sup.y * zoom*CTE_CONV*cte_h + h/2,
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
    al_draw_line(
        box->sup.x * zoom*CTE_CONV*cte_l + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_l + h/2, 
        box->sup.x * zoom*CTE_CONV*cte_h + w/2, 
        box->inf.y * zoom*CTE_CONV*cte_h + h/2,
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );

}

void Display::draw_grid_3d(){
    double i = 0.5*fov;
    double inc = 1.0/10.0;
    while (i <= 1.5/fov){
        al_draw_rectangle(
            box->inf.x * zoom*CTE_CONV*i + w/2, 
            box->inf.y * zoom*CTE_CONV*i + h/2, 
            box->sup.x * zoom*CTE_CONV*i + w/2, 
            box->sup.y * zoom*CTE_CONV*i + h/2, 
            al_map_rgb(0x80,0x80,0x80),
            1
        );
        i += inc;
    }
    i = 0.5*fov;
    while (i <= 1.5/fov){
        double j = -(box->sup.x - box->inf.x)/2;
        double inc_j = (box->sup.x - box->inf.x)/10;
        while (j <= (box->sup.x - box->inf.x)/2){
            al_draw_line(
                j * zoom*CTE_CONV*i*fov + w/2, 
                box->inf.y * zoom*CTE_CONV*i*fov + h/2, 
                j * zoom*CTE_CONV*i*fov + w/2, 
                box->sup.y * zoom*CTE_CONV*i*fov + h/2, 
                al_map_rgb(0x80,0x80,0x80),
                1
            );
            j += inc_j;
        }
        double k = -(box->sup.y - box->inf.y)/2;
        double inc_k = (box->sup.y - box->inf.y)/10;
        while (k <= (box->sup.x - box->inf.x)/2){
            al_draw_line(
                box->inf.x * zoom*CTE_CONV*i*fov + w/2, 
                k * zoom*CTE_CONV*i*fov + h/2, 
                box->sup.x * zoom*CTE_CONV*i*fov + w/2, 
                k * zoom*CTE_CONV*i*fov + h/2, 
                al_map_rgb(0x80,0x80,0x80),
                1
            );
            k += inc_k;
        }
        i += inc;
    }
}

void Display::draw_HUD(){
    al_draw_textf(this->font, al_map_rgb(0xff,0xff,0xff), 2*w/3, h - 48, 0, "grid line dimension = %dÅ ", 10);
}

void Display::draw_box(){
    al_draw_rectangle(
        box->inf.x * zoom*CTE_CONV + w/2, 
        box->inf.y * zoom*CTE_CONV + h/2, 
        box->sup.x * zoom*CTE_CONV + w/2, 
        box->sup.y * zoom*CTE_CONV + h/2, 
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
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
    i = this->w / 2.0;
    while (i < this->w){
        al_draw_line(i, 0, i, this->h, al_map_rgb(0x2f,0x2f,0x2f),1);
        i += zoom*CTE_CONV*2.5;
    }
    i = this->w / 2.0;
    while (i > 0){
        al_draw_line(i, 0, i, this->h, al_map_rgb(0x2f,0x2f,0x2f),1);
        i -= zoom*CTE_CONV*2.5;
    }

    i = this->h / 2;
    while (i < this->h){
        al_draw_line(0, i, this->w, i, al_map_rgb(0x2f,0x2f,0x2f),1);
        i += zoom*CTE_CONV*2.5;
    }
    i = this->h / 2;
    while (i > 0){
        al_draw_line(0, i, this->w, i, al_map_rgb(0x2f,0x2f,0x2f),1);
        i -= zoom*CTE_CONV*2.5;
    }
    i = this->w / 2.0;
    al_draw_line(i, 0, i, this->h, al_map_rgb(0xcf,0xcf,0xcf),2);
    i = this->h / 2;
    al_draw_line(0, i, this->w, i, al_map_rgb(0xcf,0xcf,0xcf),2);
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
                al_map_rgb(0,0,0), 0.2*p->radius*zoom*CTE_CONV
            );
            Vec v(p->pos.x*zoom*CTE_CONV + w/2, p->pos.y*zoom*CTE_CONV + h/2, 0);
            draw_vector(v, v+p->acc, 10, {0,5});
        }
    }
}

void Display::draw_vector(Vec a, Vec b, double size, pdd range){
    /*magnitude is given by grey scale*/
    double t = 3/(range.second - range.first);
    Vec v = b - a;
    double c = 0xFF*v.mag()/(range.second - range.first);
    ALLEGRO_COLOR color = al_map_rgb(c, c, c);
    v = v.unit();
    v = Vec(v.x, v.y, 0);
    al_draw_line(a.x-v.x*size/2, a.y-v.y*size/2, a.x+v.x*size/2, a.y+v.y*size/2, color, 3);
    Vec o = v.ort(Vec(0,0,1)).unit()*size/2;
    double x = a.x+v.x*size/2;
    double y = a.y+v.y*size/2;
    
    al_draw_filled_triangle(x+o.x, y+o.y, x-o.x, y-o.y, x+v.x*size/2, y+v.y*size/2, color);
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