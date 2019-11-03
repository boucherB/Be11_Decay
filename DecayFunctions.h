#ifndef BE_11_DECAY_DECAY_FUNCTIONS
#define BE_11_DECAY_DECAY_FUNCTIONS
#include <iostream>
#include "Be_11_Functions.h"
#include "TSpline.h"
#include <string>

using namespace std;

//internal functions
double dotProduct(particle e, particle v);
double normalized_dotProduct(particle e, particle v);

double decayEquation(particle &e, particle &v, particle &a, double J, double Jp, double Jpp); //the final decay Equation
double fermi(particle e);

//internal functions for decay equation
double theta(double u, double v); //theta function
double delta1(double E, double v_star, double X); //delta functions
double g1(double E, double v, double u, double s); //g-functions
double g2(double E, double v, double u, double s);
double g12(double E, double v, double u, double s);
double tau(double L, double Jp, double Jpp); //tau functions
double omega(double L, double Jp, double Jpp); //omega functions
double tensor2(particle e, particle v, particle a); //tensor

#endif
