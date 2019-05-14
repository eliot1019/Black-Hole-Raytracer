#include <iostream>
#include <math.h>

#ifdef _WIN32
#include <corecrt_math_defines.h>
#endif

#include "SphericalMapping.h"

using namespace std;

SphericalMapping::SphericalMapping(int sizex, int sizey) {
    if (sizex == 0 || sizey == 0) {
        // Image may be loaded incorrectly or given the wrong path
        throw std::overflow_error("Image loaded incorrectly");
    }
    this->SizeX = sizex;
    this->SizeY = sizey;
}

void SphericalMapping::Map(const double r, const double theta, const double phi, int &x, int &y) {
    x = (int)((phi / (2.0 * M_PI)) * SizeX) % SizeX;
    y = (int)((theta / M_PI) * SizeY) % SizeY;
    if (x < 0) { x = SizeX + x; }
    if (y < 0) { y = SizeY + y; }
}

void SphericalMapping::MapCartesian(const double x, const double y, const double z, int &u, int &v) {
    u = (int)((0.5 + atan2(z, x) / (2. * M_PI)) * SizeX) % SizeX;
    v = (int)((0.5 - (asin(y) / M_PI)) * SizeY) % SizeY;
    if (u < 0) { u = SizeX + u; }
    if (v < 0) { v = SizeY + v; }
}
