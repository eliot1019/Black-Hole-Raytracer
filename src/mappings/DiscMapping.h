#ifndef BLACKHOLERAYTRACER_DISCMAPPING_H
#define BLACKHOLERAYTRACER_DISCMAPPING_H

#include <iostream>

using namespace std;

struct DiscMapping {
  private:
    double rMin;
    double rMax;
    int sizeX;
    int sizeY;

  public:
    DiscMapping(double rMin, double rMax, int sizeX, int sizeY);

    void Map(double r, double theta, double phi, int &x, int &y);
};

#endif //BLACKHOLERAYTRACER_DISCMAPPING_H
