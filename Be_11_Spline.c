#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <random>
#include <ctime>
#include <math.h>
// #include <TROOT.h>
#include <TSpline.h>
#include "Be_11_Spline.h"
#include "Be_11_Functions.h"

using namespace std;

double Be_11_Spline(vector<xy> dataVec, int maxX, int maxY, int minX, int minY, bool B_11_check){

	vector<double> x, y; //initialize a couple of vectors for the x and y values

	for(int i = 0; i < dataVec.size(); ++i){

		x.push_back(dataVec.at(i).x); //inserts all of the values of x and y accordingly
		y.push_back(dataVec.at(i).y);

	}

	TSpline3 dataSpline("dataSpline", &x[0], &y[0], x.size()); //creates the spline function

	return randVal(dataVec, dataSpline, maxX, maxY, minX, minY, B_11_check); //returns the value passing the rejection test
}

double randVal(vector<xy> dataVec, TSpline3 dataSpline, int maxX, int maxY, int minX, int minY, bool B_11_check){

	double randomX; //initialize the random values
	double randomY;

	while(true){ //loop until rejection test is met
		randomX = ((double)rand() / RAND_MAX)*(dataVec.at(maxX).x); //randomizes a value from zero to the max
		randomY = ((double)rand() / RAND_MAX)*(dataVec.at(maxY).y);

		//check if the random Y is within the spline function, check it's the excitation energy of B and if the random X is greater than the minimum
		if((dataSpline.Eval(randomX) >= randomY) && B_11_check && ((randomX/1000) < 11.021661081*931.49432) && (randomX >= dataVec.at(minX).x)){
			return randomX; //if so output the results
		}
	}
}