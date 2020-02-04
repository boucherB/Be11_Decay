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
#include <iomanip>
#include "dataExtraction.h"
#include "Be_11_Spline.h"
#include "DecayFunctions.h"
#include "TH1D.h"
#include "TCanvas.h"
#include <TROOT.h>
#include <TMVA/TSpline1.h>
#include <TGraph.h>


using namespace std;

int main(){

    srand(time(0)); //sets randomization

    int counter = 0; //counter used for the final output file

    //From this point to the beginning of the loop is to set up the maximum decay, otherwise it was favoring low excitation energies
    //initializing all of the masses and setting the spins
    double m_norm = 0.5109989461, me = m_norm, m_B_11 = 11.009305166,
    m_Be_11 = 11.021661081, m_alpha = 4.00260325413, m_Li = 7.01600343666; //from AMDC
    double mass_conversion = 931.49410242; //Mev

    //convert the masses to MeV
    m_B_11 *= mass_conversion;
    m_Be_11 *= mass_conversion;
    m_alpha *= mass_conversion;
    m_Li *= mass_conversion;

    particle electron; //dumby particle, which is the electron, to feed into the fermi function

    //need to set up the maximum decay value
    const int DIVISIONS = 500;
    double EEx[DIVISIONS], decayMax[DIVISIONS];

    for(int j = 0; j < DIVISIONS; ++j){

        double dEx = (m_Be_11 - m_B_11) / double(DIVISIONS - 1) / 0.5109989; //need to run through this
        EEx[j] = j*dEx;

        double E0 = (m_Be_11 - m_B_11)/0.5109989 - EEx[j] + 1.;

        double dEe = (E0 - 1.)/double(DIVISIONS - 1);
        double Ee = 1.; //start electron energy at Te = 0

        decayMax[j] = 0;

        for(int i = 0; i < (DIVISIONS); ++i){

            //set electron Energies

            Ee += dEe;
            electron.p[0] = Ee;
            electron.maxEnergy = E0;
            electron.momentumMag = sqrt(Ee*Ee - 1.);

            double Ee_dist = fermi(electron)*(electron.maxEnergy - electron.p[0])*(electron.maxEnergy - electron.p[0])*(electron.p[0])*(electron.momentumMag);

            if(Ee_dist > decayMax[j]){
                decayMax[j] = Ee_dist; //We are creating an array by which we can apply a spline function
            }
        }
    }

    auto g = TGraph(DIVISIONS, EEx, decayMax);
    auto s = TMVA::TSpline1("s", &g);


    for(int i = 0; i < 1000; ++i){ //9900000 events

        //re-initialize everything
        //initializing all of the masses and setting the spins
        m_norm = 0.5109989461, me = m_norm, m_B_11 = 11.009305166,
        m_Be_11 = 11.021661081, m_alpha = 4.00260325413, m_Li = 7.01600343666; //from AMDC
        mass_conversion = 931.49410242; //Mev
        double J = 1./2., Jp = 3./2., Jpp; //spins

        //convert the masses to MeV
        m_B_11 *= mass_conversion;
        m_Be_11 *= mass_conversion;
        m_alpha *= mass_conversion;
        m_Li *= mass_conversion;

        //initialize all the particles
        particle e; //electron
        particle v; //neutrino
        particle a; //alpha
        particle Li; //Lithium
        particle B; //Boron
        particle Gamma; //Gamma

        //randomize the directions
        randomizeDirection(e);
        randomizeDirection(v);
        randomizeDirection(a);
        randomizeDirection(Gamma);

        //randomize the position using Gaussian distribution
        randomizePosition(e, a, Li, Gamma);

        //extraction of excitation energy
        bool B_11_check = 1; //checks if this is for the exciation energy of Boron
        string fileEx = "11Be_AlphaDecayFSD.dat"; //keV
        double Ex_B = (data_Extraction_Value(fileEx, 285, B_11_check) / (1000)); //determines the excitation energy (MeV)
        m_B_11 += Ex_B; //add the excitation energy to the ground state mass

        //Q-value
        double Q = m_Be_11 - m_B_11; //Set the resulting Q-value
        e.maxEnergy = Q + m_norm;

        //electron energy and momentum
        e.kinetic_energy = ((double)rand() / RAND_MAX)*Q; //determines the max kinetic energy
        e.p[0] = e.kinetic_energy + me; //total energy, text pg 275
        e.momentumMag = sqrt(e.p[0]*e.p[0] - me*me); //momentum magnitude for the momentum
        set_momentum_values(e);

        //neutrino energy and momentum
        double m_B_11_ion = m_B_11 - me;
        v.p[0] = ((m_B_11_ion*m_B_11_ion - me*me - m_Be_11*m_Be_11 + 2*m_Be_11*e.p[0]) / (2*(e.p[0] - dotProduct(e, v) - m_Be_11)));
        v.momentumMag = v.p[0]; //neutrino is assumed to be massless
        set_momentum_values(v);

        //the momentum of B = -(momentum of e + momentum of v)
        for(int i = 1; i < 4; ++i){
            B.p[i] = -(e.p[i] + v.p[i]); //determining the momentum of the recoil
        }

        //excitation of Li
        double Ex_Li;
        double excited_level = 9.142; //need to make sure the decay to excited is energetically possible
        //bool is_lithium_excited = false; //used this to verify the recoil of Li was small enough to ignore
        if(Ex_B >= excited_level){
            if((double)rand() / RAND_MAX <= 0.921){
                Ex_Li = 0; //ground state energy
                Gamma.p[0] = 0;
                Jpp = 3./2.;
            }else{
                Ex_Li = 0.47761; //exci((double)rand() / RAND_MAX)*decay_maxted state
                Gamma.p[0] = Ex_Li; //gamma energy is the excitation energy
                Jpp = 1./2.;
                //is_lithium_excited = true;
            }
        }else{
            Ex_Li = 0; //ground state energy
            Jpp = 3./2.;
        }
        m_Li += Ex_Li; //mass of lithium plus its excitation energy

        //alpha particle
        m_Li -= me; //subtract off an electron from the Lithium mass
        a.p[0] = (m_B_11_ion*m_B_11_ion + m_alpha*m_alpha - m_Li*m_Li) / (2*m_B_11_ion);

        //recoil energy, gamma
        // if(is_lithium_excited){
        //     double recoil = ((m_Li)*(m_Li) + (m_Li - Ex_Li)*(m_Li - Ex_Li))/(2*m_Li) - (m_Li - Ex_Li); //total energy of Li in rest frame of excited Li
        //     cout << recoil << endl;
        // }


	    a.momentumMag = sqrt(a.p[0]*a.p[0] - m_alpha*m_alpha); //all within the lab frame
        set_momentum_values(a);

        //Galilean transformation with the velocity of the recoil
        for(int i = 1; i < 4; ++i){
            Li.p[i] = -1*a.p[i] + ((m_Li*B.p[i])/m_B_11_ion);
        }

        //the momentum of Li is equal and opposite to the alpha particle
        Li.momentumMag = sqrt(Li.p[1]*Li.p[1] + Li.p[2]*Li.p[2] + Li.p[3]*Li.p[3]);
        //set_momentum_values(Li);
        Li.kinetic_energy = sqrt(Li.momentumMag*Li.momentumMag + m_Li*m_Li) - m_Li;


        //transformation for the alpha particle
        for(int i = 1; i < 4; ++i){
            a.p[i] += (m_alpha*B.p[i] / m_B_11_ion);
        }

        //setting the alpha momentum in the Be rest fram
        a.momentumMag = sqrt(a.p[1]*a.p[1] + a.p[2]*a.p[2] + a.p[3]*a.p[3]);
        a.kinetic_energy = sqrt(a.momentumMag*a.momentumMag + m_alpha*m_alpha) - m_alpha; //kinetic energy

        //normalize all of the values by the electron mass
        normalizeEnergy(e, v, a, m_norm);

        //decay equation
        double decay = decayEquation(e, v, a, J, Jp, Jpp);

        //setting the max decay value
        //double decay_max = 1.;
        double decay_max = 2*s.Eval(Ex_B/0.5109989); //the decay maximum is a spline function

       	//random decay
        double rand_decay = ((double)rand() / RAND_MAX)*decay_max; //what is the actual maximum

       	//rejection test for the decays2.36755
        if(rand_decay <= decay){

            //increase the counter by one
            ++counter;

	        //unnormalize the inputs to the decay function
            unnormalizeEnergy(e, v, a, m_norm);

            //create the text files with raw data
            output_text_files(Ex_B, Q, e, v, a, Li, Gamma, counter);

            //create output text files for decay
            output_decay_file(decay);

        }

    }
    return 0;
}
