#include "allegro_interface.hpp"
#include <cmath>
#include "common.hpp"

Allegro_interface::Allegro_interface(int disp_w, int disp_h, int fps, double init_z, string file_name){
    initialize_box({-20,20}, {-20,20}, {-20,20});
    if (!al_init())
        return;
    read_csv(file_name, this->particles);
    this->display = new Display(disp_w, disp_h, fps, init_z, this->particles, box);
    if (!display->is_on())
        return;
    
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    
    
    this->fps = fps;
    this->exec_spd = 5;
    this->on_3d = false;
}

void Allegro_interface::run_app(){
    ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();

    al_register_event_source(eventQueue, al_get_display_event_source(this->display->display));
    al_register_event_source(eventQueue, al_get_timer_event_source(this->display->timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    
    do{
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);
        
        this->verify_event(event);
        
    } while (this->app_controller.is_running());
}

void Allegro_interface::verify_event(ALLEGRO_EVENT event){
    switch (event.type){
        case (ALLEGRO_EVENT_DISPLAY_CLOSE):
            this->app_controller.end_app();
            break;  
        case (ALLEGRO_EVENT_KEY_DOWN):
            this->keyboard_event(event);
            break;
        case (ALLEGRO_EVENT_TIMER):
            this->timer_event(event);
            break;
    }
}

void Allegro_interface::keyboard_event(ALLEGRO_EVENT event){
    switch (event.keyboard.keycode){
    case ALLEGRO_KEY_ESCAPE:
        this->app_controller.end_app();
        break;
    case ALLEGRO_KEY_P:
        this->display->pause_play();
        break;
    case ALLEGRO_KEY_Z:
        this->display->inc_z(-0.25);
        break;
    case ALLEGRO_KEY_X:
        this->display->inc_z(0.25);
        break;
    case ALLEGRO_KEY_EQUALS:
        this->display->zoom_in();
        break;
    case ALLEGRO_KEY_MINUS:
        this->display->zoom_out();
        break;
    case ALLEGRO_KEY_0:
        this->display->zoom_rst();
        break;
    case ALLEGRO_KEY_Q:
        this->on_3d = !this->on_3d;
        break;
    }

}

void Allegro_interface::timer_event(ALLEGRO_EVENT event){
    ALLEGRO_TIMER* source = event.timer.source;
    if (source == this->display->timer and !this->display->is_paused()){
        this->update_particle_position();
    }
    if (on_3d)
        this->display->show_3d();
    else
        this->display->show();
}

void Allegro_interface::initialize_box(pdd x, pdd y, pdd z){
    this->box.p[0][0][0] = Vector(x.first,y.first,z.first);
    this->box.p[0][0][1] = Vector(x.first,y.first,z.second);
    this->box.p[0][1][0] = Vector(x.first,y.second,z.first);
    this->box.p[0][1][1] = Vector(x.first,y.second,z.second);
    this->box.p[1][0][0] = Vector(x.second,y.first,z.first);
    this->box.p[1][0][1] = Vector(x.second,y.first,z.second);
    this->box.p[1][1][0] = Vector(x.second,y.second,z.first);
    this->box.p[1][1][1] = Vector(x.second,y.second,z.second);

    this->box.inf.x = x.first;
    this->box.inf.y = y.first;
    this->box.inf.z = z.first;
    
    this->box.sup.x = x.second;
    this->box.sup.y = y.second;
    this->box.sup.z = z.second;
}

void Allegro_interface::update_particle_position(){
    calculate_forces();
    for (auto i : this->particles){
        i->spd = i->spd + (i->acc * (1.0/fps));
        i->pos = i->pos + (i->spd * (1.0/fps));

        if (i->pos.x > 20)
            i->pos.x = box.inf.x;
        if (i->pos.x < -20)
            i->pos.x = box.sup.x;
        if (i->pos.y > 20)
            i->pos.y = box.inf.y;
        if (i->pos.y < -20)
            i->pos.y = box.sup.y;
        if (i->pos.z > 20)
            i->pos.z = box.inf.z;
        if (i->pos.z < -20)
            i->pos.z = box.sup.z;
    }
}

Vector Allegro_interface::eletric_field_in(Vector pos){
    Vector E(0,0,0);
    for (auto p : this->particles){
        if (_calc_distance(p->pos, pos) > p->radius){
            E = E + _calc_eletric_field(pos, *p);
        }
    }
    return E;
}

Vector Allegro_interface::lennard_jones(Particle p){
    Vector L(0,0,0);
    for (auto q : this->particles){
        if (_calc_distance(p.pos, q->pos) > p.radius+q->radius){
            L = L + _calc_lennard_jones(p, *q);
        }
    }
    return L;

}

void Allegro_interface::resultant_vector(Particle *p){
    Vector acc(0,0,0);
    acc = acc + (eletric_field_in(p->pos) * p->charge) / p->mass;
    //acc = acc + (lennard_jones(*p));

    p->acc = acc;
}


void Allegro_interface::calculate_forces(){
    for (auto p : this->particles)
        this->resultant_vector(p);
}