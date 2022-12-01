#include "allegro_interface.hpp"
#include <cmath>
#include "common.hpp"

Allegro_interface::Allegro_interface(int disp_w, int disp_h, int fps, double init_z, string file_name){
    this->box = Box(20);
    if (!al_init())
        return;
    read_csv(file_name, this->particles);
    
    this->display = new Display(disp_w, disp_h, fps, init_z, this->particles, &box);
    if (!display->is_on())
        return;
    
    al_install_keyboard();
    al_init_image_addon();
    al_init_primitives_addon();
    al_init_font_addon();
    
    this->physic_events = PhysicEvents(&(this->particles), box, 1.0/fps);
    
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

    al_destroy_display(this->display->display);
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
    case ALLEGRO_KEY_M:
        this->display->fov_out();
        break;
    case ALLEGRO_KEY_N:
        this->display->fov_in();
        break;
    case ALLEGRO_KEY_Q:
        this->on_3d = !this->on_3d;
        break;
    }

}

void Allegro_interface::timer_event(ALLEGRO_EVENT event){
    ALLEGRO_TIMER* source = event.timer.source;
    if (source == this->display->timer and !this->display->is_paused()){
        this->physic_events.calculate_new_system_status();
    }
    if (on_3d)
        this->display->show_3d();
    else
        this->display->show();
}
