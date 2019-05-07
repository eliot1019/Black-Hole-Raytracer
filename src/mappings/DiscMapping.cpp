#include <iostream>
#include <math.h>

#include "DiscMapping.h"
#include "CGL/CGL.h"

DiscMapping::DiscMapping(double rMin1, double rMax1, int sizeX1, int sizeY1) {
  rMax = rMax1;
  rMin = rMin1;
  sizeX = sizeX1;
  sizeY = sizeY1;
}

void DiscMapping::Map(const double r, const double theta, const double phi, int &x, int &y) {
  if (r < rMin || r > rMax)
  {
    x = 0;
    y = sizeY;
  }

  x = (int)(phi / (2 * M_PI) * sizeX) % sizeX;
  if (x < 0) { x = sizeX + x; }
  y = (int)((r - rMin) / (rMax - rMin) * sizeY);
  if (y > sizeY - 1) { y = sizeY - 1; }
}