#ifndef BLACKHOLERAYTRACER_DISCMAPPING_H
#define BLACKHOLERAYTRACER_DISCMAPPING_H

#include <iostream>

#include "CGL/CGL.h"

using namespace CGL;
using namespace std;

struct DiscMapping {
  private:
    double rMin;
    double rMax;
    int sizeX;
    int sizeY;

  public:
    DiscMapping(double rMin, double rMax, int sizeX1, int sizeY1);

    void Map(double r, double theta, double phi, int &x, int &y);
};

#endif //BLACKHOLERAYTRACER_DISCMAPPING_H
