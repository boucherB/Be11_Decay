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
int j = 0;
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

		randomX = random_factor(dataVec.at(maxX).x, dataVec.at(minX).x); //randomizes a value from minimum to the max
		randomY = random_factor(dataVec.at(maxY).y, 0);

		//check if the random Y is within the spline function, check it's the excitation energy of B and if the random X is greater than the minimum
		if((dataSpline.Eval(randomX) >= randomY) && B_11_check){
			return randomX; //if so output the results
		}
	}
}

double random_factor(double max, double min){
	double f = (double)rand() / RAND_MAX;
	return f*(max - min) + min;
}