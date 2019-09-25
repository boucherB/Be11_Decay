# Be11_Decay
Simulation of 11Be decay

The initial code is the simulation of the alpha-delayed beta decay.
The goal is the determination of the kinematics of the decay products, the alpha particle and 7Li.

## Getting Started
Begin by downloading the project by cloning the repository

```
git clone https://github.com/boucherB/Be11_Decay.git
```
Then compile the project,
```
make
```
Finally run the program,
```
./Be_11
```

## Internal Construction
The program is written in C++. The overall structure of the program is laid out within Be_11_Main.c.
This main file details the internal physics of the simulation.
After initializing the mass, spin and angular momentum variables, main communicates with Be_11_Functions.c which contains the functions directly used by main. In order to determine the excitation energy, the program will randomize a value derived from 11Be_AlphaDecayFSD.dat who's data is extracted by dataExtraction.c. This data is then analyzed using a cubic spline function within Be_11_Spline.c.

## Physics
The following link displays the beta alpha and beta proton delayed decay of Beryllium 11,
http://www.tunl.duke.edu/nucldata/GroundStatedecays/11Be.shtml

Initially we determine the excitation energy of 11B. The most excited level of 11B has a distribution of energy. From this point we solve for the Q-value,
