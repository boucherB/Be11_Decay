/*still need to figure out the delta
get the decay equation working
produce a decay histogram
figure out whether we need a delta or not
separate the spline functions
work on the readme
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

    for(int i = 0; i < 1000000; ++i){

        //this is all within the rest frame of the beta decay daughter
        double m_norm = 0.511, me = m_norm, m_B_11 = 11.009305166,
        m_Be_11 = 11.021661081, m_alpha = 4.00260325413, m_Li = 7.01600343666; //from AMDC
        double mass_conversion = 931.49432; //Mev
        double J = 1/2, Jp = 3/2, Jpp; //spins

        //convert the masses to MeV
        m_B_11 *= mass_conversion;
        m_Be_11 *= mass_conversion;
        m_alpha *= mass_conversion;
        m_Li *= mass_conversion;

        //setting up the particles
        //initialize an electron with 4-vector momentum, momentum magnitude and max energy
        particle e; //electron
        particle v; //neutrino
        particle a; //alpha
        particle Li; //Lithium
        particle B; //Boron

        //direction of the electron and neutrino (completely random)
        randomizeDirection(e);
        randomizeDirection(v);
        randomizeDirection(a);

        for(int i = 1; i < 4; ++i){
            Li.p[i] = -1*a.p[i]; //momentum is equal and opposite of Li
        }

        //extraction of excitation energy
        bool B_11_check = 1; //checks if this is for the exciation energy of Boron
        string fileEx = "11Be_AlphaDecayFSD.dat"; //keV
        double Ex_B = (data_Extraction_Value(fileEx, 251, B_11_check) / (1000)); //determines the excitation energy (MeV)
        m_B_11 += Ex_B;

        //Q-value and max energy of electron
        double Q = m_Be_11 - m_B_11; //Set the resulting Q-value

        //electron energy and momentum
        double electron_kinetic = ((double)rand() / RAND_MAX)*Q; //determines the max kinetic energy
        e.p[0] = electron_kinetic + me; //total energy, text pg 275
        e.momentumMag = sqrt(e.p[0]*e.p[0] - me*me); //momentum magnitude for the momentum
        set_momentum_values(e);

        //neutrino energy and momentum
        double m_B_11_ion = m_B_11 - me;
        v.p[0] = ((m_B_11_ion*m_B_11_ion - me*me - m_Be_11*m_Be_11 + 2*m_Be_11*e.p[0]) / (2*(e.p[0] - dotProduct(e, v) - m_Be_11)));
        v.momentumMag = v.p[0]; //neutrino is assumed to be massless
        set_momentum_values(v);

        for(int i = 1; i < 4; ++i){
            B.p[i] = -(e.p[i] + v.p[i]); //determining the momentum of the recoil
        }

        //excitation of Li
        double Ex_Li;
        double excited_level = 9.142; //need to make sure the decay to excited is energetically possible
        if(Ex_B >= excited_level){
            if((double)rand() / RAND_MAX <= 0.921){
                Ex_Li = 0; //ground state energy
                Jpp = 3./2.;
            }else{
                Ex_Li = 0.47761; //excited state
                Jpp = 1./2.;
            }
        }else{
            Ex_Li = 0; //ground state energy
            Jpp = 3./2.;
        }
        m_Li += Ex_Li; //mass of lithium plus its excitation energy

        //solving for the velocity of 11B
        //need Galilean transformation
        //double v_center = (e.p[0] + n.p[0]) / (me + m_B_11_ion);

        //alpha particle
        //double Q_alpha = m_B_11 - m_Li - m_alpha; //alpha Q value
        //a.p[0] = (Q_alpha) / (1 + (m_alpha/m_Li)); //equation 8.6 in textbook (pg 248)
        a.p[0] = ((m_alpha*m_alpha + m_B_11_ion*m_B_11_ion - m_Li*m_Li)*sqrt(m_B_11_ion*m_B_11_ion + B.p[1]*B.p[1] + B.p[2]*B.p[2] + B.p[3]*B.p[3])
        + sqrt(dotProduct(a, B)*dotProduct(a, B)*(pow(m_alpha, 4.0) + pow((m_B_11_ion*m_B_11_ion + m_Li*m_Li), 2) - 2*m_alpha*m_alpha*(m_B_11_ion*m_B_11_ion
        + m_Li*m_Li - 2*(dotProduct(a, B)*dotProduct(a, B) - (B.p[1]*B.p[1] + B.p[2]*B.p[2] +B.p[3]*B.p[3])))))) / (2*(m_B_11_ion*m_B_11_ion) - (dotProduct(a, B)*dotProduct(a, B) - (B.p[1]*B.p[1] + B.p[2]*B.p[2] +B.p[3]*B.p[3])));
        a.p[0] -= m_alpha;
        a.momentumMag = sqrt(a.p[0]*a.p[0] - m_alpha*m_alpha);

        //create the text files with raw data
        output_text_files(Ex_B, Q, e, v, a);

        //normalize all of the values by the electron mass
        normalizeEnergy(e, v, a, m_norm);

        //decay equation
        double decay = decayEquation(e, v, a, J, Jp, Jpp);

        //create output text files for decay
        output_decay_file(decay);

    }
    return 0;
}