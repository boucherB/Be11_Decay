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

double Be_11_Spline(vector<xy> dataVec, int maxX, int maxY, int minX, int minY){

	vector<double> x, y;
	cout << dataVec.size() << endl;;

	for(int i = 0; i < dataVec.size(); ++i){

		x.push_back(dataVec.at(i).x);
		y.push_back(dataVec.at(i).y);

	}

	TSpline3 dataSpline("dataSpline", &x[0], &y[0], x.size());



	return randVal(dataVec, dataSpline, maxX, maxY, minX, minY);
}

double randVal(vector<xy> dataVec, TSpline3 dataSpline, int maxX, int maxY, int minX, int minY){

	double randomX = ((double)rand() / RAND_MAX)*(dataVec.at(maxX).x);
	cout << randomX << " " << dataVec.at(maxX).x << " ";
	double randomY = ((double)rand() / RAND_MAX)*(dataVec.at(maxY).y);
	cout << randomY << " " << dataVec.at(maxY).y << endl;

	if((randomX >= dataVec.at(minX).x) && (randomY >= dataVec.at(minY).y)){
		cout << "check" << endl;
		if(rejTest(dataSpline, randomX, randomY)){
			cout << "check2" << endl;
			return randomX;
		}else{
			randVal(dataVec, dataSpline, maxX, maxY, minX, minY);
		}
	}else{
		randVal(dataVec, dataSpline, maxX, maxY, minX, minY);
	}
}
//
bool rejTest(TSpline3 dataSpline, double randomX, double randomY){
	if((dataSpline.Eval(randomX) <= randomY)){
		return true;
	}else{
		return false;
	}


}
