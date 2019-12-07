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

    e.kinetic_energy /= m_norm;
    v.kinetic_energy /= m_norm;
    a.kinetic_energy /= m_norm;
}

void unnormalizeEnergy(particle &e, particle &v, particle &a, double m_norm){
    e.p[0] *= m_norm; //normalize the energies by the mass of an electron
    v.p[0] *= m_norm;
    a.p[0] *= m_norm;

    for(int i = 1; i < 4; ++i){
        e.p[i] *= m_norm;
        v.p[i] *= m_norm;
        a.p[i] *= m_norm;
    }

    e.momentumMag *= m_norm;
    v.momentumMag *= m_norm;
    a.momentumMag *= m_norm;

    e.maxEnergy *= m_norm;
    v.maxEnergy *= m_norm;
    a.maxEnergy *= m_norm;

    e.kinetic_energy *= m_norm;
    v.kinetic_energy *= m_norm;
    a.kinetic_energy *= m_norm;
}

void randomizePosition(particle &e, particle &a, particle &Li, particle &Gamma){

    double FWHM = 2.0; //mm
    double sigma = FWHM / 2.355; //approximately sigma


    for(int i = 0; i < 3; ++i){

        double temp = generateGaussian(0., sigma);

        e.position[i] = temp;
        a.position[i] = temp;
        Li.position[i] = temp;
        Gamma.position[i] = temp;

    }

}

double generateGaussian(double mu, double sigma){

    double u1 = (double)rand()/RAND_MAX; //generate number from 0 to 1
    double u2 = (double)rand()/RAND_MAX;

    double z0 = sqrt(-2*log(u1))*sin(2*M_PI*u2); //Box-Muller transform

    ofstream gaussian("Gaussian.txt", ios_base::app);
    gaussian << z0 + sigma*mu << endl;
    gaussian.close();

    return z0 + sigma*mu;

}

void output_text_files(double Ex_B, double Q, particle e, particle v, particle a, particle Li, particle Gamma, int counter){

    ofstream Final_Output("Final_Output.txt", ios_base::app);
    Final_Output << "#" << counter << endl;
    Final_Output << "/gps/particle e-" << endl;
    Final_Output << "/gps/energy " << e.kinetic_energy << " MeV" << endl;
    Final_Output << "/gps/direction " << e.p[1] << " " << e.p[2] << " " << e.p[3] << endl;
    Final_Output << "/gps/position " << "0 0 0 mm" << endl;
    Final_Output << "/run/beamOn 1" << endl;
    Final_Output << "/gps/particle He4" << endl;
    Final_Output << "/gps/energy " << a.kinetic_energy << " MeV" << endl;
    Final_Output << "/gps/direction " << a.p[1] << " " << a.p[2] << " " << a.p[3] << endl;
    Final_Output << "/gps/position " << "0 0 0 mm" << endl;
    Final_Output << "/run/beamOn 1" << endl;
    Final_Output << "/gps/particle Li7" << endl;
    Final_Output << "/gps/energy " << Li.kinetic_energy << " MeV" << endl;
    Final_Output << "/gps/direction " << Li.p[1] << " " << Li.p[2] << " " << Li.p[3] << endl;
    Final_Output << "/gps/position " << "0 0 0 mm" << endl;
    Final_Output << "/run/beamOn 1" << endl;

    if(Gamma.p[0] > 0){
        Final_Output << "/gps/particle gamma" << endl;
        Final_Output << "/gps/energy " << Gamma.p[0] << " MeV" << endl;
        Final_Output << "/gps/direction " << Gamma.p[1] << " " << Gamma.p[2] << " " << Gamma.p[3] << endl;
        Final_Output << "/gps/position " << "0 0 0 mm" << endl;
        Final_Output << "/run/beamOn 1" << endl;
    }

}

void output_decay_file(double decay){
    ofstream Decay_Spectrum("Decay_Spectrum.txt", ios_base::app);
    Decay_Spectrum << decay << endl;
    Decay_Spectrum.close();
}
