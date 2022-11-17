#pragma once

#include <stdbool.h>
#include "allegro.h"
#include "common.h"
#include "display.h"
#include "vector.h"
#include "simulation.h"
#include "box.h"

typedef struct Allegro_interface{
    Display *display;
    Simulation *simulation;

    double fps;
    double exec_spd;
    Box box;
    bool running;

} AllegroInterface;


void AIEndApp(AllegroInterface *);
void AIRunApp(AllegroInterface *);
void AITimerEvent(AllegroInterface *, ALLEGRO_EVENT event);
void AIKeyboardEvent(AllegroInterface *, ALLEGRO_EVENT event);
void AICheckEvent(AllegroInterface *, ALLEGRO_EVENT event);
bool AIIsRunning(AllegroInterface *);


AllegroInterface *AllegroInterfaceCreate(int disp_w, int disp_h, int fps, double init_z, char file_name[]);

