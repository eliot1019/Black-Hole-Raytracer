#include <iostream>
#include <math.h>
#ifdef _WIN32
#include <corecrt_math_defines.h>
#endif

#include "DiscMapping.h"

DiscMapping::DiscMapping(double rMin, double rMax, int sizeX, int sizeY) {
  if (sizeX == 0 || sizeY == 0) {
    // Image may be loaded incorrectly or given the wrong path
    throw std::overflow_error("Image loaded incorrectly");
  }

  this->rMax = rMax;
  this->rMin = rMin;
  this->sizeX = sizeX;
  this->sizeY = sizeY;
}

void DiscMapping::Map(const double r, const double theta, const double phi, int &x, int &y) {
  if (r < rMin || r > rMax)
  {
    x = 0;
    y = sizeY;
  }

  x = (int)((phi / (2 * M_PI)) * sizeX) % sizeX;
  if (x < 0) { x = sizeX + x; }
  y = (int)(((r - rMin) / (rMax - rMin)) * sizeY);
  if (y > sizeY - 1) { y = sizeY - 1; }
}