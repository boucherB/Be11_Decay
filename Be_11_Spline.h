#ifndef BE_11_DECAY_BE_11_SPLINE_H
#define BE_11_DECAY_BE_11_SPLINE_H

#include <vector>
#include "Be_11_Functions.h"
#include <TSpline.h>

double Be_11_Spline(std::vector<xy> dataVec, int, int, int, int, bool);
double randVal(std::vector<xy> dataVec, TSpline3 dataSpline, int, int, int, int, bool);

#endif
