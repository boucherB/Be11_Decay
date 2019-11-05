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


void randomizeDirection(particle &e){

    bool boolean = true;
    while(boolean){

        for(int i = 1; i < 4; ++i){
            e.p[i] = (double)rand() / RAND_MAX;
            if(((double)rand() / RAND_MAX) >= 0.5){
                e.p[i] *= -1;
            }
        }

        double rsq = (e.p[1])*(e.p[1]) + (e.p[2])*(e.p[2]) + (e.p[3])*(e.p[3]); //determining r^2

        if(rsq > 0.0000000 && rsq < 1.000000){ //if within [0,1]

            double r = sqrt(rsq);
            e.p[1] /= r; // if so normalize
            e.p[2] /= r;
            e.p[3] /= r;
            boolean = false;
        }
    }
}

void set_momentum_values(particle& e){
    for(int i = 1; i < 4; ++i){
        e.p[i] *= e.momentumMag;
    }
}

void normalizeEnergy(particle &e, particle &v, particle &a, double m_norm){
    e.p[0] /= m_norm; //normalize the energies by the mass of an electron
    v.p[0] /= m_norm;
    a.p[0] /= m_norm;

    for(int i = 1; i < 4; ++i){
        e.p[i] /= m_norm;
        v.p[i] /= m_norm;
        a.p[i] /= m_norm;
    }

    e.momentumMag /= m_norm;
    v.momentumMag /= m_norm;
    a.momentumMag /= m_norm;

    e.maxEnergy /= m_norm;
    v.maxEnergy /= m_norm;
    a.maxEnergy /= m_norm;
}

void output_text_files(double Ex_B, double Q, particle e, particle v, particle a){
    ofstream Ex_Spectrum("Ex_Spectrum.txt", ios_base::app);
    Ex_Spectrum << Ex_B << endl;
    Ex_Spectrum.close();

    ofstream Q_Value_Spectrum("Q_Value_Spectrum.txt", ios_base::app);
    Q_Value_Spectrum << Q << endl;
    Q_Value_Spectrum.close();

    ofstream Electron_Energy_Spectrum("Electron_Energy_Spectrum.txt", ios_base::app);
    Electron_Energy_Spectrum << e.p[0] << endl;
    Electron_Energy_Spectrum.close();

    ofstream Neutrino_Energies("Neutrino_Energy_Spectrum.txt", ios_base::app);
    Neutrino_Energies << v.p[0] << endl;
    Neutrino_Energies.close();

    ofstream Alpha_Energy_Spectrum("Alpha_Energy_Spectrum.txt", ios_base::app);
    Alpha_Energy_Spectrum << a.p[0] << endl;
    Alpha_Energy_Spectrum.close();

}

void output_decay_file(double decay){
    ofstream Decay_Spectrum("Decay_Spectrum.txt", ios_base::app);
    Decay_Spectrum << decay << endl;
    Decay_Spectrum.close();
}
