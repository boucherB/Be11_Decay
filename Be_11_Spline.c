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

	vector<double> x, y;

	for(int i = 0; i < dataVec.size(); ++i){

		x.push_back(dataVec.at(i).x);
		y.push_back(dataVec.at(i).y);

	}

	TSpline3 dataSpline("dataSpline", &x[0], &y[0], x.size());

	return randVal(dataVec, dataSpline, maxX, maxY, minX, minY, B_11_check);
}

double randVal(vector<xy> dataVec, TSpline3 dataSpline, int maxX, int maxY, int minX, int minY, bool B_11_check){

	double randomX = ((double)rand() / RAND_MAX)*(dataVec.at(maxX).x);
	double randomY = ((double)rand() / RAND_MAX)*(dataVec.at(maxY).y);

	if((randomX >= dataVec.at(minX).x) && (randomY >= dataVec.at(minY).y)){
		if(rejTest(dataSpline, randomX, randomY, B_11_check)){
			return randomX;
		}else{
			randVal(dataVec, dataSpline, maxX, maxY, minX, minY, B_11_check);
		}
	}else{
		randVal(dataVec, dataSpline, maxX, maxY, minX, minY, B_11_check);
	}
}
//
bool rejTest(TSpline3 dataSpline, double randomX, double randomY, bool B_11_check){

	if((dataSpline.Eval(randomX) <= randomY) && B_11_check && ((randomX/1000) < 11.021661081)){
		return true;
	}else{
		return false;
	}


}
