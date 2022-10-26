#include "allegro.hpp"
#include "particles.hpp"
#include <vector>

using namespace std;

class Display{
private:   
    bool on;
    double current_z;
    double range_z;
    vector<Particle*> particles;
public:
    ALLEGRO_DISPLAY* display;
    ALLEGRO_TIMER* timer;
    Display();
    Display(int, int, double, double, double, vector<Particle*>);
    void draw_particles();
    void draw_grid();
    bool is_on();
};