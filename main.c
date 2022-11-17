#include "allegro_interface.h"


int main(int argv, char **argc){
    //AllegroInterface *app = AllegroInterfaceCreate(1024, 640, 24, 0, argc[1]);
    AllegroInterface *app = AllegroInterfaceCreate(1024, 640, 24, 0, "saida.txt");
    AIRunApp(app);
    return 0;
}

