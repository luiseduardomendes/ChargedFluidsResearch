#include "allegro_interface.hpp"

using namespace::std;

int main(int argv, char **argc){
    Allegro_interface app(1360 , 768, 24, 0, argc[1]);
    app.run_app();
    return 0;
}

