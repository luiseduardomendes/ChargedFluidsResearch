#include "allegro_interface.hpp"

using namespace::std;

int main(){
    Allegro_interface app(640, 480, 60, 0, 10, "saida.txt");
    app.run_app();
    return 0;
}

