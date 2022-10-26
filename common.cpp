#include "common.hpp"
#include <fstream>

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