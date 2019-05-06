#include "Disk.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include "../utils.h"
#include "../mappings/SphericalMapping.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include "CGL/CGL.h"
#include <CGL/vector3D.h>
#include "CGL/Color.h"


using namespace CGL;
using namespace std;
using namespace CV;

Disk::Disk(const double radiusInner1, const double radiusOuter1) {
  radiusInner = radiusInner1;
  radiusOuter = radiusOuter1;
  radiusInnerSqr = radiusInner * radiusInner;
  radiusOuterSqr = radiusOuter * radiusOuter;
}

Color Disk::GetColor(int side, double r, double theta, double phi) {
  // white
  return Color::White;
}


bool Disk::Hit(Vector3D &point, double sqrNorm, Vector3D &prevPoint, double prevSqrNorm,
              Vector3D &velocity, SchwarzschildBlackHoleEquation equation, double r, double theta,
              double phi, Color &color, bool stop, bool debug) {
  // Remember what side of the plane we're currently on, so that we can detect
  // whether we've crossed the plane after stepping.
  int side = prevPoint.y > 0 ? -1 : prevPoint.y < 0 ? 1 : 0;

  // Did we cross the horizontal plane?
  bool success = false;
  if (point.y * side >= 0) {
    auto colpoint = IntersectionSearch(side, prevPoint, velocity, equation);
    auto colpointsqr = colpoint.LengthSquared();

    if ((colpointsqr >= radiusInnerSqr) && (colpointsqr <= radiusOuterSqr)) {
      double tempR = 0, tempTheta = 0, tempPhi = 0;
      Util.ToSpherical(colpoint.X, colpoint.Y, colpoint.Z, &tempR, &tempTheta, &tempPhi);

      color = Util.addColor(GetColor(side, tempR, tempPhi, tempTheta + M_PI / 12), color);
      stop = false;
      success = true;
    }
  }
  return success;
}


Vector3D Disk::IntersectionSearch(int side, Vector3D prevPoint, Vector3D velocity, SchwarzschildBlackHoleEquation equation) {
  float stepLow = 0, stepHigh = equation.StepSize;
  Vector3D newPoint = prevPoint;
  Vector3D tempVelocity;
  while (true) {
    float stepMid = (stepLow + stepHigh) / 2;
    newPoint = prevPoint;
    tempVelocity = velocity;
    equation.Function(&newPoint, &tempVelocity, stepMid);

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
