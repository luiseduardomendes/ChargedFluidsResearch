#include "allegro_interface.hpp"

using namespace::std;

int main(int argv, char **argc){
    srand(time(NULL));
    map<string, int> map = {
        {"Na", 20},
        {"Cl", 20}
    };
    Allegro_interface app(640, 480, 24, 0, map, 20);
    
    if (argv >= 2)
        app = Allegro_interface(640, 480, 24, 0, argc[1], 20);
    
    app.run_app();
    return 0;
}

