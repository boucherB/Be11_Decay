
#ifndef BE_11_DECAY_BE_11_FUNCTIONS_H
#define BE_11_DECAY_BE_11_FUNCTIONS_H

#include <iostream>
#include <string>
#include "Be_11_Functions.h"

struct particle{
	double p[4]; // 4-momentum vector
    double maxEnergy;
    double momentumMag;
};

struct xy{
    double x;
    double y;
};


void set_momentum_values(particle& e);
double data_Extraction_Value(std::string file, int numLines, bool B_11_check);
void randomizeDirection(particle &e);
void normalizeEnergy(particle &e, particle &v, particle &a, double);
void unnormalizeEnergy(particle &e, particle &v, particle &a, double);
void output_text_files(double, double, particle e, particle v, particle a);
void output_decay_file(double decay);

#endif
