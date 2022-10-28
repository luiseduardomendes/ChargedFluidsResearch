#include "app_controller.hpp"

App_controller::App_controller(){
    this->init_app();
}

void App_controller::init_app(){
    this->close_app = false;
    this->start_timer = clock();
}

void App_controller::end_app(){
    this->close_app = true;
}

bool App_controller::is_ended(){
    return this->close_app;
}

bool App_controller::is_running(){
    return not this->close_app;
}

double App_controller::get_timer(){
    return double(clock() - start_timer) / CLOCKS_PER_SEC;
}