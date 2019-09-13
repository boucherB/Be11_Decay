
// Created by brandon on 7/25/19.

/*

 * Spline alpha decay
 * Alpha energy and momentum
 * Do we need the delta function
 * Determine momentum using conserv
 *
 the random number for the probabilities is fucked
 ask about mass normalization (electron)
 ask about the negative Q-value
 what is the decay equation used for
 need to fix the momentum magnitude to get the proper fermi value
gamma
distribution for alpha decay
 */

#include <iostream>
#include <time.h>
#include "Be_11_Functions.h" //this is where the xy struct is
#include <math.h>
#include <random>
#include <stdlib.h>
#include "dataExtraction.h"
#include "Be_11_Spline.h"
#include "DecayFunctions.h"

using namespace std;

int main(){

    srand(time(0)); //sets randomization

    //this is all within the rest frame of the beta decay daughter
    double m_norm = 0.511, me = (0.511 / m_norm), mv = 0, m_B_11 = 11.009305166,
    m_Be_11 = 11.021661081; //mass of the electron, neutrino in MeV
    double m_alpha = 4.00260325413;
    double m_Li = 7.01600343666;
    double L = 1;  //angular momentum
    double v_star; //velocity of the alpha particle
    double J = 1/2, Jp = 3/2, Jpp; //spins
    //direction for the neutrino(k) and alpha(n)

    //setting up the particles
    particle electron; //initialize an electron with 4-vector momentum and max energy
    particle neutrino;
    particle alpha;

    //direction of the electron and neutrino (completely random)
    randomizeDirection(electron);
    randomizeDirection(neutrino);
    randomizeDirection(alpha);

    //extraction of excitation energy
    string fileEx = "11Be_AlphaDecayFSD.dat";
    double Ex_B = (data_Extraction_Value(fileEx, 251))/1000;

    //Q-value and max energy of electron
    double Q = m_Be_11 - Ex_B; //The Q value is approximated for beta decays

    //electron energy and momentum
    electron.maxEnergy = Q - Ex_B + me; //find the maximum electron energy
    electron.p[0] = (electron.maxEnergy  - me)*(rand() % (2)) + me;
    electron.momentumMag = sqrt(electron.p[0]*electron.p[0] - me*me);

    //neutrino energy and momentum
    neutrino.p[0] = (m_B_11*m_B_11 - me*me - m_Be_11*m_Be_11 + 2*m_Be_11*electron.p[0]) / 2*(electron.p[0]+electron.momentumMag);
    neutrino.momentumMag = neutrino.p[0];

    //excitation of Li
    string file_Li = "AlphaDecay.txt";
    double Ex_Li = data_Extraction_Value(file_Li, 2);

    //alpha particle
    alpha.p[0] = (m_Li*m_Li - m_B_11*m_B_11 - m_alpha*m_alpha) / (2*m_B_11);
    alpha.momentumMag = sqrt(alpha.p[0]*alpha.p[0] - m_alpha*m_alpha);

    //print out the results
    print(Q, Ex_B, electron, neutrino, alpha);

    cout << decayEquation(electron, neutrino, alpha);

    return 0;
}
