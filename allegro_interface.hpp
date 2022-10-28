#pragma once

#include "allegro.hpp"
#include "common.hpp"
#include <vector>
#include <map>
#include <string>
#include <iostream>
#include "display.hpp"
#include "app_controller.hpp"

using namespace std;

class Allegro_interface{
    private:
        Display *display;
        App_controller app_controller;

        vector<Particle*> particles;

        double fps;

        void timer_event(ALLEGRO_EVENT event);
        void keyboard_event(ALLEGRO_EVENT event);
        void verify_event(ALLEGRO_EVENT event);
        void update_particle_position();
    public:
        
        Allegro_interface(int disp_w, int disp_h, int fps, double init_z, string file_name);
        void end_app();
        void run_app();
};