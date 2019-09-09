
// Created by brandon on 7/25/19.

/*
 * Determine if we need spline for fermi
 * New Q-value function which is the differences in mass of 11Be and 11B
 * Need to fix the masses with amdc
 * Spline alpha decay
 * Alpha energy and momentum
 * Do we need the delta function
 * Divide everything by the mass of e
 * Determine momentum using conserv
 *
 */

#include <iostream>
#include <time.h>
#include "Be_11_Functions.h" //this is where the xy struct is
#include <math.h>
#include <random>
#include <stdlib.h>
#include "dataExtraction.h"
#include "Be_11_Spline.h"

using namespace std;

int main(){

    srand(time(0)); //sets randomization

    //this is all within the rest frame of the beta decay daughter
    double Ex, Eli, Q; //some of the variables for energy
    double amuConversion = 931.5; //MeV
    double level0 = 11.5093; //11Be level, initial level, in MeV
    double level1 = 9.873; //11B level, final level, in MeV
    int Z; //atomic number of Beryllium
    double m_norm = 0.511, me = (0.511 / m_norm), mv = 0, m_B_11 = 11.009305166*amuConversion / m_norm,
    m_Be_11 = 11.021661081*amuConversion / m_norm; //mass of the electron, neutrino in MeV
    double L = 1;  //angular momentum
    double v_star; //velocity of the alpha particle
    double J = 1/2; //spins
    double Jp = 3/2;
    double Jpp; //spline function to determine ex or ground state of 7Li
    //direction for the neutrino(k) and alpha(n)

    //setting up the particles
    particle electron; //initialize an electron with 4-vector momentum and max energy
    particle neutrino;
    particle alpha;

    //extraction of excitation energy
    string fileEx = "11Be_AlphaDecayFSD.dat";
    vector<xy> exEnergy(251);
    dataExtraction(fileEx, exEnergy);
    Be_11_Spline(exEnergy);

    Q = m_Be_11 - Ex; //The Q value is approximated for beta decays
    electron.maxEnergy = Q - Ex + me; //find the maximum electron energy

    //electron energy and momentum
    electron.p[0] = (electron.maxEnergy  - me)*(rand() % (2)) + me;
    electron.momentumMag = sqrt(electron.p[0]*electron.p[0] - me*me);

    //neutrino energy and momentum
    //neutrino.p[0] = (m_B_11*m_B_11 - me*me - m_Be_11*m_Be_11 + 2*m_Be_11*electron.p[0]) / 2(electron.p[0]+electron.momentumMag);
    //neutrino.momentumMag = neutrino.p[0];

    //direction of the electron and neutrino (completely random)
    randomizeDirection(electron);
    randomizeDirection(neutrino);
    randomizeDirection(alpha);



    return 0;
}
