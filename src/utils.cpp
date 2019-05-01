#include <iostream>

#include "utils.h"
#include "CGL/CGL.h"

using namespace CGL;
using namespace std;

void ToCartesian(double r, double theta, double phi, double &x, double &y, double &z) {
    *x = r * cos(phi) * sin(theta);
    *y = r * sin(phi) * sin(theta);
    *z = r * cos(theta);
}

void ToSpherical(double x, double y, double z, double &r, double &theta, double &phi) {
    *r = sqrt(x * x + y * y + z * z);
    phi = atan2(y, x);
    theta = acos(z / *r);
}

void ToSpherical(Vector3D v, double &r, double &theta, double &phi) {
    *r = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    phi = atan2(v.y, v.x);
    theta = acos(v.z / *r);
}

double DoubleMod(double n, double m) {
    double x = floor(n / m);
    return n - (m * x);
}

std::vector<char> getNativeTextureBitmap(Mat texture); // TODO

Spectrum AddColor(Spectrum hitColor, Spectrum tintColor); // TODO

int Cap(int x, int max) {
    if (x > max) {
        return max;
    }
    else {
        return x;
    }
}

int CapMin(int x, int min) {
    if (x < min) {
        return min;
    }
    else {
        return x;
    }
}