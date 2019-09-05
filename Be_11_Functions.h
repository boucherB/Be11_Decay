
#ifndef BE_11_DECAY_BE_11_FUNCTIONS_H
#define BE_11_DECAY_BE_11_FUNCTIONS_H
#include <iostream>


using namespace std;


struct particle{
	double p[4]; // 4-momentum vector
    double maxEnergy;
    double momentumMag;
};

struct xy{
    double x;
    double y;
};

//internal functions
void randomizeDirection(particle &e);
double dotProduct(particle e, particle v);

//energy extraction
double energyExtraction(string file, int n, double const max_x, double const max_y, bool boolx);

//internal functions for decay equation
double theta(double u, double v); //theta function
double delta1(double E, double v_star, double X); //delta functions
double g1(double E, double v, double u, double s); //g-functions
double g2(double E, double v, double u, double s);
double g12(double E, double v, double u, double s);
double tau(double L, double Jp, double Jpp); //tau functions
double omega(double L, double Jp, double Jpp); //omega functions
double tensor2(particle e, particle v, particle a); //tensor
//rejection test produces the random value within the range
double decayRejectionTest(double value, double max_y);
double splineRejectionTest(); //need the spline funciton
double randomizeDecay();

#endif
