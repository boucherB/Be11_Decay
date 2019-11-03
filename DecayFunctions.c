#include <iostream>
#include <cstdlib>
#include <math.h>
#include <random>
#include <cstdlib>
#include <string>
#include "Be_11_Functions.h"
#include <fstream>
#include "dataExtraction.h"
#include "Be_11_Spline.h"


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

double dotProduct(particle e, particle v){
    return e.p[1]*v.p[1] + e.p[2]*v.p[2] + e.p[3]*v.p[3];
}

double normalized_dotProduct(particle e, particle v){
    return (e.p[1]*v.p[1] + e.p[2]*v.p[2] + e.p[3]*v.p[3]) / (e.momentumMag*v.momentumMag);
}

double tensor2(particle a, particle b, particle n){
    return (a.momentumMag / a.p[0])*normalized_dotProduct(n, a)*normalized_dotProduct(n, b) - (1/3.0)*normalized_dotProduct(a,b)*(a.momentumMag/a.p[0]);
}

double fermi(particle e){
    vector<double> x,y;
    vector<xy> dataVec(49); //set up the vector to store the values
    string fileFermi = "Be_11_Fermi.txt";
    int maxX, maxY, minX, minY; //initialize max and mins for x and y
    dataExtraction(fileFermi, dataVec, maxX, maxY, minX, minY); //extract the data

    for(int i = 0; i < dataVec.size(); ++i){

		x.push_back(dataVec.at(i).x); //place the values into vectors
		y.push_back(dataVec.at(i).y);

	}

	TSpline3 dataSpline("dataSpline", &x[0], &y[0], x.size());
    return dataSpline.Eval(e.momentumMag); //return the evaluated fermi value
}

double decayEquation(particle &e, particle &v, particle &a, double J, double Jp, double Jpp){

   //extraction of fermi energy
   double fermi_value = fermi(e);

   // //initialize all of the constants
   double coefficient = fermi_value*(e.maxEnergy - e.p[0])*(e.maxEnergy - e.p[0])*(e.p[0])*(e.momentumMag);
   // for the g's, g_i(E) = F_i(E, J', J, 1)
   double term1 = (g1(e.p[0], Jp, J, 1));
   double term2 = g2(e.p[0], Jp, J, 1)*(e.momentumMag / e.p[0])*normalized_dotProduct(e, v);
   double term3 = (1./10.)*tau(1, Jp, Jpp)*g12(e.p[0], Jp, J, 1)*tensor2(e, v, a);

   //eq 53 on pg 796
   return coefficient*(term1 + term2 + term3);
}
