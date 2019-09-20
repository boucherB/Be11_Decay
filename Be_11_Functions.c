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
    vector<xy> dataVec(numLines);
    int maxX, maxY, minX, minY;
    dataExtraction(file, dataVec, maxX, maxY, minX, minY);
    return Be_11_Spline(dataVec, maxX, maxY, minX, minY, B_11_check);
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
            e.p[1] = e.p[1]*e.momentumMag / r; // if so normalize
            e.p[2] /= e.p[2]*e.momentumMag / r;
            e.p[3] /= e.p[3]*e.momentumMag / r;
            return;
        }
    }
}
