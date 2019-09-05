#include <iostream>
#include <cstdlib>
#include <math.h>
#include <random>
#include <cstdlib>
#include "Be_11_Functions.h"
#include <fstream>
#include "dataExtraction.h"


using namespace std;

//The entire lot of functions come from Equation 53
double tau(double L, double Jp, double Jpp){

    double tau1coeff = 2 / (Jp*(Jp + 1));
    double tau2coeff = 10 / (7*Jp*(Jp + 1));

    if(L == 1){
        if(Jp == Jpp + 1){
            return tau1coeff*(2*Jp + 3)*(Jp + 1);
        }else if(Jp == Jpp){
            return -tau1coeff*(2*Jp + 3)*(2*Jp - 1);
        }else{
            return tau1coeff*(2*Jp - 1)*Jp;
        }

    }else{
        if(Jp == Jpp + 2){
            return tau2coeff*2*(2*Jp + 3)*(Jp + 1);
        }else if(Jp == Jpp + 1){
            return -tau2coeff*(2*Jp + 3)*(Jp - 5);
        }else if(Jp == Jpp){
            return -tau2coeff*(2*Jp + 5)*(2*Jp - 3);
        }else if(Jp == Jpp - 1){
            return -tau2coeff*(2*Jp - 1)*(Jp + 6);
        }else{
            return tau2coeff*2*(2*Jp - 1)*Jp;
        }
    }
}

double omega(double L, double Jp, double Jpp) {

    if (L == 1) {
        return 0;
    } else if (L == 2) {

        double omegacoeff = 20 / 63;
        if (Jp == Jpp + 2) {
            return omegacoeff * (2 * Jp + 5) * (2 * Jp + 3) / (Jp * (Jp - 1));
        } else if (Jp == Jpp + 1) {
            return -2 * omegacoeff * (2 * Jp + 5) * (2 * Jp + 3) * (2 * Jp - 3) / (Jp * (Jp + 1)*(Jp - 1));
        } else if (Jp == Jpp) {
            return 6 * omegacoeff * (2 * Jp + 5) * (2 * Jp - 3) / (Jp * (Jp + 1));
        } else if (Jp == Jpp - 1) {
            return -2 * omegacoeff * (2 * Jp - 3) * (2 * Jp - 1) * (2 * Jp + 5) / (Jp * (Jp + 1) * (Jp + 2));
        } else {
            return omegacoeff * (2 * Jp - 3) * (2 * Jp - 1) / ((Jp + 1) * (Jp + 2));
        }

    }
}

double theta(double u, double v){

    if(u == v + 1){
        return -(u + 1) / (2*u - 1);
    }else if(u == v){
        return 1;
    }else{
        return -u / (2*u + 3);
    }

}

//within g1, g2 and g12, c1 is one as it is entirely GT, change in L = 1
double g1(double E, double v, double u, double s){

	double a1 = 0;
	double c1 = 1; //the beta decay is GT because of the spin sequence
	
	return pow(abs(a1),2)+pow(abs(c1),2);
	
}

double g2(double E, double v, double u, double s){

	double a1 = 0;
	double c1 = 1; //the beta decay is GT because of the spin sequence
	
	return pow(abs(a1), 2) - pow(abs(c1), 2)/3;
	
}

double g12(double E, double v, double u, double s){

	double a1 = 0;
    double c1 = 1; //the beta decay is GT because of the spin sequence
	double theta_uv = theta(u,v);
	
	return -theta_uv*pow(abs(c1),2);
}


double delta1(double E, double v_star, double X){
	
	double a1 = 0;
    double c1 = 1; //the beta decay is GT because of the spin sequence
	double M;
	
	return -2*pow(abs(c1),2) / (M * v_star);
	
	
}

void randomizeDirection(particle &e){

    while(true){
        e.p[1] = (double)rand() / RAND_MAX; //randomizing the directions
        e.p[2] = (double)rand() / RAND_MAX;
        e.p[3] = (double)rand() / RAND_MAX;

        double rsq = (e.p[1])*(e.p[1]) + (e.p[2])*(e.p[2]) + (e.p[3])*(e.p[3]); //determining r^2

        if(rsq > 0.0000000 && rsq < 1.000000){ //if within [0,1]

            double r = sqrt(rsq);
            e.p[1] = e.p[1]*e.momentumMag / r; // if so normalize
            e.p[2] /= e.p[2]*e.momentumMag / r;
            e.p[3] /= e.p[3]*e.momentumMag / r;
            return;
        }
    }
}

double dotProduct(particle e, particle v){
    return e.p[1]*v.p[1] + e.p[2]*v.p[2] + e.p[3]*v.p[3];
}

//double decayEquation(particle &e, particle &v, particle &a){
//
//    //extraction of fermi energy
//    string fileFermi = "Be_11_Fermi.txt";
//    vector<xy> fermiEnergy(49);
//    dataExtraction(fileFermi, fermiEnergy);
//    //just need the spline function
//
//    //initialize all of the constants
//    double G_v = 0.0001; //Gv*m_p = 10^-5
//    double theta_c = 15; //degrees
//    //double Fermi = Fermi(particle e); //NEED FERMI FUNCTION
//    double J = 1/2; //J = 1/2+
//    double Jp = 3/2; //J' = 3/2+
//    double Jpp; //will be decided by alpha decay, spline function
//
//    //double coefficient = Fermi*((G_v)*(G_v)*cos(theta_c)*cos(theta_c) / (2*pow((2*pi),6)));
//    // for the g's, g_i(E) = F_i(E, J', J, 1)
//    double term1 = (g1(e.p[0], Jp, J, 1));
//    double term2 = g2(e.p[0], Jp, J, 1)*(1 / e.p[0])*dotProduct(e, v);
//    double term3 = (1/10)*tau(1, Jp, Jpp)*g12(e.p[0], Jp, J, 1)*tensor2(e, v, a)*dotProduct(e, v) / e.p[0];
//
//    //eq 53 on pg 796
//    double decay = coefficient*(term1 + term2 + term3);
//    return decayRejectionTest(decay, 1.0);
//
//}

double tensor2(particle e, particle v, particle a){
    return (e.p[0])*dotProduct(a, e)*dotProduct(a, v) - (1/3.0)*dotProduct(e,v);
}

//double decayRejectionTest(double value, double max_y){
//
//    double randFactorY = rand()/RAND_MAX;
//
//    if(value >= randFactorY*max_y){
//        return randFactorY*max_y;
//    }else{
//        rejectionTest(value, max_y);
//    }
//}

