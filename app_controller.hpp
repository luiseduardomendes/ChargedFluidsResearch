#pragma once

class App_controller{
private:
    bool close_app;
    bool pause_app;
public:
    App_controller();
    void init_app();
    void end_app();
    bool is_ended();
    bool is_running();
};