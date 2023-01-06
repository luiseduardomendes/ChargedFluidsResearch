#include "common.hpp"
#include <fstream>
#include <cmath>

void read_csv(string file_name, vector<Particle *> &particles){
    
    ifstream input(file_name);
    int file_size;
    string temp;

    input >> file_size;
    getline(input, temp);

    for (int i = 0; i < file_size; i ++){
        float v[3];
        string part_type;
        
        input >> part_type;
        input >> v[0];
        input >> v[1];
        input >> v[2];
        
        particles.push_back(new Particle(v[0], v[1], v[2], part_type));
    }
    
}

void split(string str, vector<float>& v, string& particle_type, char sep){
    size_t begin = 0, end;
    v.clear();
    end = str.find(sep, begin);
    particle_type = str.substr(begin, end);
    begin = end + 1;

    while ((end = str.find(sep, begin)) != string::npos){
        v.push_back(atof(str.substr(begin, end).c_str()));
        begin = end + 1;
    }
    v.push_back(atof(str.substr(begin).c_str()));
}

Vec _calc_eletric_field(Vec point, Particle p){
    double e0 = 2.077193348 * pow(10,-2); // (e^2 * s^2) / (u * A^3)
    double k = 1/(4*M_PI*e0);
    double d = _calc_distance(point, p.pos);
    Vec E;
    if (d > p.radius)
        E = (point-p.pos) * (k * p.charge / pow(d, 3/2));
    return E;
}

Vec _calc_lennard_jones(Particle p1, Particle p2){
    Vec d = p1.pos - p2.pos;
    double cutwca = pow(2, 1/6);
    double dist;
    double c5;
    unsigned int Lx = 2*p1.radius;
    Vec lennard;
    Vec d2(round(d.x/Lx), round(d.y/Lx), round(d.z/Lx));
    d = d - d2;

    dist = sqrt(d.dot(d));

    if(dist < cutwca){
        c5 = 5.0 * (-6.0 / pow(dist, 7) + 12.0 / pow(dist, 13));
        if(dist <= 0.8)
            c5 = 5.0 * (-6.0 / pow(0.8, 7) + 12.0 / pow(0.8, 13));
    lennard = d * c5 / dist;
    }
    return lennard;
}    


double _calc_distance(Vec p1, Vec p2){
    return sqrt(pow(p1.x-p2.x, 2) + pow(p1.y-p2.y, 2) + pow(p1.z-p2.z, 2));
}

void _sort(vector<Particle *> &arr){
    int n = arr.size();
    for (int gap = n/2; gap > 0; gap /= 2){
        for (int i = gap; i < n; i += 1){            
            Particle* temp = arr[i];
            
            int j;           
            for (j = i; j >= gap && *(arr[j - gap]) > *temp; j -= gap)
                arr[j] = arr[j - gap];
             
            arr[j] = temp;
        }
    }
}

Vec gausran_vector(){
    return Vec(gausran(), gausran(), gausran());
}

double gausran(){
    
    int g;
    double ran1,ran2,PI,R1,R2,res;
    ran1 = (double)rand()/RAND_MAX;
    ran2 = (double)rand()/RAND_MAX;
    PI   = 4.0*atan(1.0);
    R1   = -log(1.0-ran1);
    R2   = 2.0*PI*ran2;
    R1   = sqrt(2.0*R1);
    res  = R1*cos(R2);
    return res;
}

double unirand(double min, double max){
	double random  = ((double) rand()) / RAND_MAX;
	double range = (max - min) * random;
	double n = range + min;	
	
	return n;
}

Vec random_pos_in_box(Box box){
    Vec v;
    v.x = unirand(box.inf.x, box.sup.x);
    v.y = unirand(box.inf.y, box.sup.y);
    v.z = unirand(box.inf.z, box.sup.z);
    return v;
}

bool check_colision(vector<Particle*> v, Particle* part){
    for (auto p : v){
        if (colide(*p, *part)){
            return true;
        }
    }
    return false;
}

bool colide(Particle p1, Particle p2){
    return (p1.pos - p2.pos).mag() < (p1.radius + p2.radius);
}
