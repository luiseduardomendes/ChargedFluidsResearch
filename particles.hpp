#include <vector>
#include <string>
#include "allegro.hpp"
using namespace std;

struct Pos{
    double x, y, z;
};

class Particle{
public:
    string type;
    double radius;
    ALLEGRO_COLOR color;
    Pos pos;
    Particle();
    Particle(double x, double y, double z, string type);
};