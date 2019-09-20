
// Created by brandon on 7/25/19.

/*
 * Do we need the delta function
 *
 the random number for the probabilities is fucked
 ask about mass normalization (electron)

are the changes right, namely the electron energies
why did I create a Fermi thing
why are my neutron energies so low
 */

#include <iostream>
#include <time.h>
#include "Be_11_Functions.h" //this is where the xy struct is
#include <math.h>
#include <random>
#include <stdlib.h>
#include <cstdlib>
#include "dataExtraction.h"
#include "Be_11_Spline.h"
#include "DecayFunctions.h"

using namespace std;

int main(){

    srand(time(0)); //sets randomization

    for(int i = 0; i < 20; ++i){
        //this is all within the rest frame of the beta decay daughter
        double m_norm = 0.511, me = (0.511), m_B_11 = 11.009305166,
        m_Be_11 = 11.021661081, m_alpha = 4.00260325413, m_Li = 7.01600343666;
        double L = 1;  //angular momentum
        double v_star; //velocity of the alpha particle
        double J = 1/2, Jp = 3/2, Jpp; //spins
        //direction for the neutrino(k) and alpha(n)

        //setting up the particles
        particle electron; //initialize an electron with 4-vector momentum and max energy
        particle neutrino;
        particle alpha;

        //extraction of excitation energy
        bool B_11_check = 1;
        string fileEx = "11Be_AlphaDecayFSD.dat";
        double Ex_B = (data_Extraction_Value(fileEx, 251, B_11_check))/(1000);
        B_11_check = 0;

        //Q-value and max energy of electron
        double Q = m_Be_11 - Ex_B; //The Q value is approximated for beta decays

        //electron energy and momentum
        electron_energy(electron, Q);
        electron.p[0] = electron.p[0] + me;
        electron.momentumMag = sqrt(electron.p[0]*electron.p[0] - me*me);

        //neutrino energy and momentum
        neutrino.p[0] = ((m_B_11*m_B_11 - me*me - m_Be_11*m_Be_11 + 2*m_Be_11*electron.p[0]) / 2*(electron.p[0]+electron.momentumMag));
        neutrino.momentumMag = neutrino.p[0];

        // //excitation of Li
        double Ex_Li;
        if((double)rand() / RAND_MAX <= 0.921){
            Ex_Li = 8.6641;
        }else{
            Ex_Li = 9.14171;
        }

        //alpha particle
        alpha.p[0] = abs((m_Li*m_Li - m_B_11*m_B_11 - m_alpha*m_alpha) / (2*m_B_11));
        alpha.momentumMag = sqrt(abs(alpha.p[0]*alpha.p[0] - m_alpha*m_alpha));

        //direction of the electron and neutrino (completely random)
        randomizeDirection(electron);
        randomizeDirection(neutrino);
        randomizeDirection(alpha);
        //
        double decay = decayEquation(electron, neutrino, alpha);
        // //cout << decay << endl;
        //
        //print out the results
        print(Q, Ex_B, electron, neutrino, alpha, decay);
    }


    return 0;
}
