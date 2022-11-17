#include "display.h"
//#include "common.h"

#define CTE_CONV 5

Display *Display_Create(int w, int h, double fps, double init_z, int num_particles, Particle* part[], Box box){
    Display *display = (Display*)malloc(sizeof(Display));
    
    display->on = true;
    display->num_particles = num_particles;

    if (!(display->display = al_create_display(w, h)))
        display->on = false;

    display->w = w;
    display->h = h;

    display->current_z = init_z;
    
    display->particles = part;

    //al_init_ttf_addon();
    //display.font = al_load_ttf_font("fonte.ttf", 36, 0);
    
    display->timer = al_create_timer(1.0/fps);
    al_start_timer(display->timer);
    display->paused = false;

    display->zoom = 2.5;
    display->box = box;

    return display;
}

bool Display_is_on(Display *display){
    return display->on;
}

void Display_show(Display *display){
    al_clear_to_color(al_map_rgb(0x00, 0x11, 0x20));
    Display_draw_grid(display);
    Display_draw_particles(display);
    Display_draw_box(display);
    Display_draw_HUD(display);

    al_flip_display();
}

void Display_draw_HUD(Display *disp){
    // al_draw_textf(display.font, al_map_rgb(0xff,0xff,0xff), 2*w/3, h - 48, 0, "grid line dimension = %dÅ ", 10);
}

void Display_draw_box(Display *display){
    al_draw_rectangle(
        display->box.inf.x * display->zoom*CTE_CONV + display->w/2, 
        display->box.inf.y * display->zoom*CTE_CONV + display->h/2, 
        display->box.sup.x * display->zoom*CTE_CONV + display->w/2, 
        display->box.sup.y * display->zoom*CTE_CONV + display->h/2, 
        al_map_rgb(0xc0,0xc0,0xc0),
        2
    );
}

void Display_draw_grid(Display *display){
    double i;
    i = display->w / 2.0;
    while (i < display->w){
        al_draw_line(i, 0, i, display->h, al_map_rgb(0x8f,0x8f,0x8f),2);
        i += display->zoom*CTE_CONV*10;
    }
    i = display->w / 2.0;
    while (i > 0){
        al_draw_line(i, 0, i, display->h, al_map_rgb(0x8f,0x8f,0x8f),2);
        i -= display->zoom*CTE_CONV*10;
    }

    i = display->h / 2.0;
    while (i < display->h){
        al_draw_line(0, i, display->w, i, al_map_rgb(0x8f,0x8f,0x8f),2);
        i += display->zoom*CTE_CONV*10;
    }
    i = display->h / 2.0;
    while (i > 0){
        al_draw_line(0, i, display->w, i, al_map_rgb(0x8f,0x8f,0x8f),2);
        i -= display->zoom*CTE_CONV*10;
    }
    i = display->w / 2.0;
    while (i < display->w){
        al_draw_line(i, 0, i, display->h, al_map_rgb(0x2f,0x2f,0x2f),1);
        i += display->zoom*CTE_CONV*2.5;
    }
    i = display->w / 2.0;
    while (i > 0){
        al_draw_line(i, 0, i, display->h, al_map_rgb(0x2f,0x2f,0x2f),1);
        i -= display->zoom*CTE_CONV*2.5;
    }

    i = display->h / 2.0;
    while (i < display->h){
        al_draw_line(0, i, display->w, i, al_map_rgb(0x2f,0x2f,0x2f),1);
        i += display->zoom*CTE_CONV*2.5;
    }
    i = display->h / 2.0;
    while (i > 0){
        al_draw_line(0, i, display->w, i, al_map_rgb(0x2f,0x2f,0x2f),1);
        i -= display->zoom*CTE_CONV*2.5;
    }
    i = display->w / 2.0;
    al_draw_line(i, 0, i, display->h, al_map_rgb(0xcf,0xcf,0xcf),2);
    i = display->h / 2.0;
    al_draw_line(0, i, display->w, i, al_map_rgb(0xcf,0xcf,0xcf),2);
}

void Display_draw_particles(Display *display){
    Particle* p;
    for (int i = 0; i < display->num_particles; i ++){
        p = display->particles[i];
        if (p->pos.z > display->current_z - p->radius && p->pos.z < display->current_z + p->radius){
            al_draw_filled_circle(
                p->pos.x*display->zoom*CTE_CONV + display->w/2, 
                p->pos.y*display->zoom*CTE_CONV + display->h/2,
                sqrt(abs(pow(p->radius, 2) - pow((p->pos.z-display->current_z), 2)))*display->zoom*CTE_CONV, 
                p->color
            );
            al_draw_circle(
                p->pos.x*display->zoom*CTE_CONV + display->w/2, 
                p->pos.y*display->zoom*CTE_CONV + display->h/2,
                sqrt(abs(pow(p->radius, 2) - pow((p->pos.z-display->current_z), 2)))*display->zoom*CTE_CONV, 
                al_map_rgb(0,0,0), 0.2*p->radius*display->zoom*CTE_CONV
            );
        }
    }
}

void Display_pause_play(Display *display){
    if (display->paused){
        display->paused = false;
    }
    else{
        display->paused = true;
    }
}

bool Display_is_paused(Display *display){
    return display->paused;
}

void Display_inc_z(Display *display){
    display->current_z += 1;
}

void Display_dec_z(Display *display){
    display->current_z -= 1;
}

void Display_inc_z_cte(Display *display, double inc){
    display->current_z += inc;
}

void Display_zoom_out(Display *display){
    display->zoom *= 0.9;
}

void Display_zoom_in(Display *display){
    display->zoom *= 1.1;
}

void Display_zoom_rst(Display *display){
    display->zoom = 1;
}