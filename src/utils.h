#ifndef UTILS_H
#define UTILS_H

#include <iostream>

#include "CGL/CGL.h"

using namespace CGL;
using namespace std;

void ToCartesian(double r, double theta, double phi, double &x, double &y, double &z);
void ToSpherical(double x, double y, double z, double &r, double &theta, double &phi);
void ToSpherical(Vector3D v, double &r, double &theta, double &phi);
double DoubleMod(double n, double m);
std::vector<char> getNativeTextureBitmap(Mat texture); // TODO
Spectrum AddColor(Spectrum hitColor, Spectrum tintColor);
int Cap(int x, int max);
int CapMin(int x, int min);

#endif /* UTILS_H */