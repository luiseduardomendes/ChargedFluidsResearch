#include "allegro_interface.hpp"

using namespace::std;

int main(){
    Allegro_interface app(1024, 640, 24, 0, "saida.txt");
    app.run_app();
    return 0;
}

