#include <iostream>
#include <math.h>

#include "SphericalMapping.h"
#include "CGL/CGL.h"

using namespace CGL;
using namespace std;

SphericalMapping::SphericalMapping(int sizex, int sizey) {
    SizeX = sizex;
    SizeY = sizey;
}

void SphericalMapping::Map(const double r, const double theta, const double phi, int &x, int &y) {
    x = (int)((phi / (2. * M_PI)) * SizeX) % SizeX;
    y = (int)((theta / M_PI) * SizeY) % SizeY;

    if (x < 0) {
        x = SizeX + x;
    }
    if (y < 0) {
        y = SizeY + y;
    }
}

void SphericalMapping::MapCartesian(const double x, const double y, const double z, int &u, int &v) {
    u = (int)((0.5 + atan2(z, x) / (2. * M_PI)) * SizeX) % SizeX;
    v = (int)((0.5 - (asin(y) / M_PI)) * SizeY) % SizeY;
    if (u < 0) {
        u = SizeX + u;
    }
    if (v < 0) {
        v = SizeY + v;
    }
}
