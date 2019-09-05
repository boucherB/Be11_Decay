/*
 * How to compile:
 *
 * 2 step method:
 *
 * g++ `root-config --cflags` -c main.cpp
 * g++ `root-config --libs` main.o
 *
 * this will generate the executable 'a.out'.
 * This method is more useful when you're using a
 * Makefile to compile.
 *
 * 1 step method:
 *
 * g++ 'root-config --cflags --libs` main.cpp
 *
 * this will generate the executable 'a.out'.
 *
 * NOTE: the '`' character is a "backtick", which
 * is next to the "1" key.
 *
 */
#include <iostream>
#include <vector>
#include <algorithm>

#include <TSpline.h>

using namespace std;

int main() {
	vector<double> x, y;

	x.push_back(0); x.push_back(10);
	y.push_back(0); y.push_back(10);

	TSpline3 myspline("myspline", &x[0], &y[0], x.size());

	cout << "Filling a spline from vectors: " << endl;
	for(int i = 0; i < 11; i++) {
		cout << i << " " << myspline.Eval(i) << endl;
	}

	double xx[2], yy[2];
	xx[0] = 0; xx[1] = 10;
	yy[0] = 10; yy[1] = 0;

	TSpline3 myspline2("myspline", xx, yy, 2);

	cout << "\nFilling a spline from arrays: " << endl;
	for(int i = 0; i < 11; i++) {
		cout << i << " " << myspline2.Eval(i) << endl;
	}

	return 1;
}
