#include "Disk.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include "../utils.h"
#include "../mappings/SphericalMapping.h"
#include "../ArgbColor.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include "CGL/CGL.h"
#include <CGL/vector3D.h>


using namespace CGL;
using namespace std;
using namespace cv;

Disk::Disk(const double radiusInner, const double radiusOuter) {
  this->radiusInner = radiusInner;
  this->radiusOuter = radiusOuter;
  radiusInnerSqr = radiusInner * radiusInner;
  radiusOuterSqr = radiusOuter * radiusOuter;
}

ArgbColor Disk::GetColor(int side, double r, double theta, double phi) {
  // white
  return ArgbColor::White;
}


bool Disk::Hit(Vector3D &point, double sqrNorm, Vector3D &prevPoint, double prevSqrNorm,
              Vector3D &velocity, SchwarzschildBlackHoleEquation *equation, double r, double theta,
              double phi, ArgbColor &color, bool &stop, bool debug) {
  // Remember what side of the plane we're currently on, so that we can detect
  // whether we've crossed the plane after stepping.
  int side = prevPoint.y > 0 ? -1 : prevPoint.y < 0 ? 1 : 0;

  // Did we cross the horizontal plane?
  bool success = false;
  if (point.y * side >= 0) {
    Vector3D colpoint = IntersectionSearch(side, prevPoint, velocity, equation);
    double colpointsqr = colpoint.norm2();

    if ((colpointsqr >= radiusInnerSqr) && (colpointsqr <= radiusOuterSqr)) {
      double tempR = 0;
      double tempTheta = 0;
      double tempPhi = 0;
      Utils::ToSpherical(colpoint.x, colpoint.y, colpoint.z, tempR, tempTheta, tempPhi);

      color = Utils::AddColor(GetColor(side, tempR, tempPhi, tempTheta + M_PI / 12), color);
      stop = false;
      success = true;
    }
  }
  return success;
}


Vector3D Disk::IntersectionSearch(int side, Vector3D prevPoint, Vector3D velocity, SchwarzschildBlackHoleEquation *equation) {
  float stepLow = 0, stepHigh = equation->StepSize;
  Vector3D newPoint = prevPoint;
  Vector3D tempVelocity;
  while (true) {
    float stepMid = (stepLow + stepHigh) / 2;
    newPoint = prevPoint;
    tempVelocity = velocity;
    equation->Function(newPoint, tempVelocity, stepMid);
    if (abs(stepHigh - stepLow) < 0.00001) {
      break;
    }
    if (side * newPoint.y > 0) {
      stepHigh = stepMid;
    }
    else{
      stepLow = stepMid;
    }
  }
  return newPoint;
}
