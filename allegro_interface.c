#include <math.h>
#include "allegro_interface.h"
#include "common.h"
#include "vector.h"

AllegroInterface* AllegroInterfaceCreate(int disp_w, int disp_h, int fps, double init_z, char file_name[]){
    int nParticles;
    AllegroInterface *alInt = (AllegroInterface *) malloc(sizeof(AllegroInterface));

    Vector BoxInf = VectorCreateInitState(-20, -20, -20);
    Vector BoxSup = VectorCreateInitState(20, 20, 20);
    Box box = BoxInit(BoxInf, BoxSup);

    alInt->simulation = SimulationCreate(file_name, fps, box);
    nParticles = alInt->simulation->nParticles;

    if (!al_init())
        return alInt;

    alInt->display = Display_Create(disp_w, disp_h, fps, init_z, nParticles, alInt->simulation->particles, box);
    if (!Display_is_on(alInt->display))
        return alInt;
    
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    
    
    alInt->fps = fps;
    alInt->exec_spd = 5;

    return alInt;
}

bool AIIsRunning(AllegroInterface *alInt){
    return alInt->running;
}

void AIRunApp(AllegroInterface *alInt){
    alInt->running = true;

    ALLEGRO_EVENT_QUEUE *eventQueue = al_create_event_queue();
    al_register_event_source(eventQueue, al_get_display_event_source(alInt->display->display));
    al_register_event_source(eventQueue, al_get_timer_event_source(alInt->display->timer));
    al_register_event_source(eventQueue, al_get_keyboard_event_source());
    
    do{
        ALLEGRO_EVENT event;
        al_wait_for_event(eventQueue, &event);
        
        AICheckEvent(alInt, event);
        
    } while (AIIsRunning(alInt));
}

void AICheckEvent(AllegroInterface *alInt, ALLEGRO_EVENT event){
    switch (event.type){
        case (ALLEGRO_EVENT_DISPLAY_CLOSE):
            AIEndApp(alInt);
            break;  
        case (ALLEGRO_EVENT_KEY_DOWN):
            AIKeyboardEvent(alInt, event);
            break;
        case (ALLEGRO_EVENT_TIMER):
            AITimerEvent(alInt, event);
            break;
    }
}

void AIKeyboardEvent(AllegroInterface *alInt, ALLEGRO_EVENT event){
    switch (event.keyboard.keycode){
    case ALLEGRO_KEY_ESCAPE:
        AIEndApp(alInt);
        break;/*
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
        break;*/
    }

}

void AIEndApp(AllegroInterface *alInt){
    alInt->running = false;
}

void AITimerEvent(AllegroInterface *alInt, ALLEGRO_EVENT event){
    ALLEGRO_TIMER* source = event.timer.source;
    if (source == alInt->display->timer && !Display_is_paused(alInt->display)){
        SimulationUpdateParticlePosition(alInt->simulation);
    }
    Display_show(alInt->display);
}



Vector SimulationEletricFieldIn(Simulation *sim, Vector pos){
    Vector E = VectorCreateZero();
    for (int i = 0; i < sim->nParticles; i++){
        Particle *p = sim->particles[i];
        if (_calc_distance(p->pos, pos) > p->radius){
            E = VectorAdd(E, _calc_eletric_field(pos, *p));
        }
    }
    return E;
}

Vector SimulationLennardJones(Simulation *sim, Particle p){
    Vector L = VectorCreateZero();
    for (int i = 0; i < sim->nParticles; i ++){
        Particle *q = sim->particles[i];
        if (_calc_distance(p.pos, q->pos) > p.radius+q->radius){
            L = VectorAdd(L, _calc_lennard_jones(p, *q));
        }
    }
    return L;

}

void SimulationResultantVector(Simulation *sim, Particle *p){
    Vector acc = VectorCreateZero();
    acc = VectorCteDiv(VectorAdd(acc, VectorCteMult(SimulationEletricFieldIn(sim, p->pos), p->charge)), p->mass);
    //acc = acc + (lennard_jones(*p));

    p->acc = acc;
}


void SimulationCalculateForces(Simulation *sim){
    for (int i = 0; i < sim->nParticles; i ++){
        Particle *p = sim->particles[i];
        SimulationResultantVector(sim, p);
    }
}