#include <iostream>
#include <cstdlib>
#include <math.h>
#include <random>
#include <cstdlib>
#include "Be_11_Functions.h"
#include "DecayFunctions.h"
#include <fstream>
#include "dataExtraction.h"
#include "Be_11_Spline.h"


using namespace std;

double data_Extraction_Value(string file, int numLines, bool B_11_check){
    vector<xy> dataVec(numLines); //setting up the vector, according to the number of lines in the data file
    int maxX, maxY, minX, minY; //initialize the maximum and minimum values
    dataExtraction(file, dataVec, maxX, maxY, minX, minY); //extracts the data, should return the vector
    return Be_11_Spline(dataVec, maxX, maxY, minX, minY, B_11_check); //returns the value of the rejection test
}

void print(double Q, double Ex, particle electron, particle neutrino, particle alpha, double decay){
    cout << endl;
    cout << "---------------------" << endl;
    cout << "Excitation Energy: " << Ex << endl;
    cout << "Q-value: " << Q << endl;
    cout << "---------------------" << endl;
    cout << "Electron Max Energy: " << electron.maxEnergy << endl;
    cout << "Electron Energy: " << electron.p[0] << endl;
    cout << "Electron Momentum: " << electron.momentumMag << endl;
    cout << "---------------------" << endl;
    cout << "Neutrino Energy: " << neutrino.p[0] << endl;
    cout << "Neutrino Momentum: " << neutrino.momentumMag << endl;
    cout << "---------------------" << endl;
    cout << "Alpha Energy: " << alpha.p[0] << endl;
    cout << "Alpha Momentum: " << alpha.momentumMag << endl;
    cout << "---------------------" << endl;
    cout << "Decay: " << decay << endl;
    cout << endl;
}

void randomizeDirection(particle &e){

    while(true){
        e.p[1] = (double)rand() / RAND_MAX; //randomizing the directions
        e.p[2] = (double)rand() / RAND_MAX;
        e.p[3] = (double)rand() / RAND_MAX;

        double rsq = (e.p[1])*(e.p[1]) + (e.p[2])*(e.p[2]) + (e.p[3])*(e.p[3]); //determining r^2

        if(rsq > 0.0000000 && rsq < 1.000000){ //if within [0,1]

            double r = sqrt(rsq);
            e.p[1] /= r; // if so normalize
            e.p[2] /= r;
            e.p[3] /= r;
            return;
        }
    }
}

void electron_energy(particle &e, double Q){
    double me = 0.511; //mass of electron
    e.maxEnergy = (Q + me); //max total electron energy, text pg 275
    double electron_max_kinetic = e.maxEnergy - me; //electron max kinetic energy

    e.p[0] = rand_energy(e, Q, electron_max_kinetic); //randomize the electron energy

}

double rand_energy(particle &e, double Q, double electron_max_kinetic){

    //this all stems from eq 9.25 on pg280
    double rand_kinetic; //initialize the random values
    double rand_N;
    double N;

    while(true){

        rand_kinetic = ((double)rand() / RAND_MAX)*electron_max_kinetic; //randomize the kinetic from the max to zero
        //rand_N = ((double)rand() / RAND_MAX)*0.05; //randomly chose one to be max
        N = sqrt(rand_kinetic*rand_kinetic + 2*rand_kinetic)*pow(Q - rand_kinetic, 2)*(rand_kinetic + 0.511);

        ofstream electronEnergySpectrum("ElectronEnergyOutput.txt", ios_base::app);
        electronEnergySpectrum << N;
        electronEnergySpectrum << rand_kinetic;
        electronEnergySpectrum << endl;
        electronEnergySpectrum.close();
        cout << N << " " << rand_kinetic << endl;
        return rand_kinetic; //if true return the random kinetic energy
    }
}

void normalizeEnergy(particle &e, particle &v, particle &a, double m_norm){
    e.p[0] /= m_norm; //normalize the energies by the mass of an electron
    v.p[0] /= m_norm;
    a.p[0] /= m_norm;
}