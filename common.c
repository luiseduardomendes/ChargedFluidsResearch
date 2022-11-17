#include "common.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

Particle **read_csv(char file_name[], int *nParticles){
    
    FILE* file = fopen(file_name, "r");
    char temp[100];
    int n;

    if (fgets(temp, 100, file))
        *nParticles = atoi(temp);
    n = *nParticles;

    Particle **particles = (Particle **) malloc(sizeof(Particle *) * n);

    for (int i = 0; i < n; i ++){
        char type[3];
        float v[3];
        const char sep[2] = "-";

        Particle *p = (Particle *)malloc(sizeof(Particle));
        
        if (!fgets(temp, 100, file))
            continue;

        strcpy(type, strtok(temp, sep));

        v[0] = atof(strtok(NULL, sep));
        v[1] = atof(strtok(NULL, sep));
        v[2] = atof(strtok(NULL, sep));

        p = ParticleCreateByTypeAndInitState(
            type, 
            VectorCreateInitState(v[0], v[1], v[2]), 
            VectorCreateZero(), 
            VectorCreateZero()
        );
        particles[i] = p;
    }

    return particles;   
}

Vector _calc_eletric_field(Vector point, Particle p){
    double e0 = 2.077193348 * pow(10,-2); // (e^2 * s^2) / (u * A^3)
    double k = 1/(4*M_PI*e0);
    double d = _calc_distance(point, p.pos);
    Vector E;
    if (d > p.radius)
        E = VectorCteMult(VectorSub(point, p.pos), (k * p.charge / pow(d, 3/2)));
    return E;
}

Vector _calc_lennard_jones(Particle p1, Particle p2){
    Vector d = VectorSub(p1.pos, p2.pos);
    double cutwca = pow(2, 1/6);
    double dist;
    double c5;
    unsigned int Lx = 2*p1.radius;
    Vector lennard;
    Vector d2 = VectorCreateInitState(round(d.x/Lx), round(d.y/Lx), round(d.z/Lx));
    d = VectorSub(d, d2);

    dist = VectorMag(d);

    if(dist < cutwca){
        c5 = 5.0 * (-6.0 / pow(dist, 7) + 12.0 / pow(dist, 13));
        if(dist <= 0.8)
            c5 = 5.0 * (-6.0 / pow(0.8, 7) + 12.0 / pow(0.8, 13));
    lennard = VectorCteDiv(VectorCteMult(d, c5), dist);
    }
    return lennard;
}    


double _calc_distance(Vector p1, Vector p2){
    return VectorMag(VectorSub(p2, p1));
}
