#include "allegro.hpp"
#include "common.hpp"
#include <vector>
#include <map>
#include <string>
#include "display.hpp"
#include "app_controller.hpp"

using namespace std;

class Allegro_interface{
    private:
        Display *display;
        App_controller app_controller;

        vector<Particle*> particles;

        void timer_event(ALLEGRO_EVENT event);
        void keyboard_event(ALLEGRO_EVENT event);
        void verify_event(ALLEGRO_EVENT event);
    public:
        
        Allegro_interface(int disp_w, int disp_h, int fps, double init_z, double range_z, string file_name);
        void end_app();
        void run_app();
};