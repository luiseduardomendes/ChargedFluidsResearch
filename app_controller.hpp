#pragma once
#include <ctime>

class App_controller{
private:
    bool close_app;
    bool pause_app;
    clock_t start_timer;
public:
    App_controller();
    void init_app();
    void end_app();
    bool is_ended();
    bool is_running();
    double get_timer();
};