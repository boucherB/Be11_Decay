
// Created by brandon on 7/25/19.

/*
 * Do we need the delta function
 *

need to add zero for the fermi value
why are my neutron energies so high

TCanvas for multiple histograms
 */

#include <iostream>
#include <time.h>
#include "Be_11_Functions.h" //this is where the xy struct is
#include <math.h>
#include <random>
#include <stdlib.h>
#include <cstdlib>
#include <fstream>
#include "dataExtraction.h"
#include "Be_11_Spline.h"
#include "DecayFunctions.h"
#include "TH1D.h"
#include "TCanvas.h"
#include <TROOT.h>

using namespace std;

int main(){

    srand(time(0)); //sets randomization
    int j = 0;

    for(int i = 0; i < 1000000; ++i){

        //this is all within the rest frame of the beta decay daughter
        double m_norm = 0.511, me = m_norm, m_B_11 = 11.009305166,
        m_Be_11 = 11.021661081, m_alpha = 4.00260325413, m_Li = 7.01600343666;
        double mass_conversion = 931.49432; //Mev!
        m_B_11 *= mass_conversion;
        m_Be_11 *= mass_conversion;
        double L = 1;  //angular momentum
        double v_star; //velocity of the alpha particle
        double J = 1/2, Jp = 3/2, Jpp; //spins

        //setting up the particles
        particle electron; //initialize an electron with 4-vector momentum, momentum magnitude and max energy
        particle neutrino;
        particle alpha;
        normalizeEnergy(electron, neutrino, alpha, m_norm);


        //direction of the electron and neutrino (completely random)
        randomizeDirection(electron);
        randomizeDirection(neutrino);
        randomizeDirection(alpha);

        //extraction of excitation energy
        bool B_11_check = 1; //checks if this is for the exciation energy of Boron
        string fileEx = "11Be_AlphaDecayFSD.dat"; //keV
        double Ex_B = (data_Extraction_Value(fileEx, 251, B_11_check) / (1000)); //determines the excitation energy (MeV)
        m_B_11 += Ex_B;
        B_11_check = 0;

        //Q-value and max energy of electron
        double Q = m_Be_11 - m_B_11; //Set the resulting Q-value

        //electron energy and momentum
        electron_energy(electron, Q); //determines the max kinetic energy
        electron.p[0] += me; //total energy, text pg 275
        electron.momentumMag = sqrt(electron.p[0]*electron.p[0] - me*me); //momentum magnitude for the momentum
        set_momentum_values(electron);

        //neutrino energy and momentum
        double m_B_11_ion = m_B_11 - me;
        neutrino.p[0] = ((m_B_11_ion*m_B_11_ion - me*me - m_Be_11*m_Be_11 + 2*m_Be_11*electron.p[0]) / (2*(electron.p[0] - dotProduct(electron, neutrino) - m_Be_11)));
        neutrino.momentumMag = neutrino.p[0]; //neutrino is assumed to be massless
        //set_moment    // cout << "Mass of 11B:       " << m_B_11 << endl;
        // cout << "Mass of 11Be:      " << m_Be_11 << endl;
        // cout << "Excitation Energy: " << Ex_B << endl;
        // cout << "Q value:           " << Q << endl;
        // cout << "Electron Energy:   " << electron.p[0] << endl;
        // cout << "Neutrino Energy:   " << neutrino.p[0] << endl;um_values(neutrino);

        // //excitation of Li
        double Ex_Li;
        if((double)rand() / RAND_MAX <= 0.921){
            Ex_Li = 0;
        }else{
            Ex_Li = 0.47761;
        }

        m_Li += Ex_Li; //mass of lithium plus its excitation energy

        //alpha particle
        alpha.p[0] = (-m_Li*m_Li + m_B_11*m_B_11 + m_alpha*m_alpha) / (2*m_B_11);
        alpha.momentumMag = sqrt(alpha.p[0]*alpha.p[0] - m_alpha*m_alpha);


        // cout << "Mass of 11B:       " << m_B_11 << endl;
        // cout << "Mass of 11Be:      " << m_Be_11 << endl;
        // cout << "Excitation Energy: " << Ex_B << endl;
        // cout << "Q value:           " << Q << endl;
        // cout << "Electron Energy:   " << electron.p[0] << endl;
        // cout << "Neutrino Energy:   " << neutrino.p[0] << endl;

        output_text_files(Ex_B, Q, electron, neutrino, alpha);
        //normalize all of the values by the electron mass
        normalizeEnergy(electron, neutrino, alpha, m_norm);

        // double decay = decayEquation(electron, neutrino, alpha);
        // cout << "Decay:             " << decay << endl;
        // cout << endl;
        //create the text files with raw data


    }

    return 0;
}
