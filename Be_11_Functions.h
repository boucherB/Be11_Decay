
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

double data_Extraction_Value(std::string file, int numLines, bool B_11_check);
void print(double Q, double Ex, particle electron, particle neutrino, particle alpha, double decay);
void randomizeDirection(particle &e);

#endif
