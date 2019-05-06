#ifndef BLACKHOLERAYTRACER_DISK_H
#define BLACKHOLERAYTRACER_DISK_H

#include "CGL/CGL.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace CGL;
using namespace std;
using namespace cv;

struct Disk {
  private:
    double radiusInner;
    double radiusOuter;
    double radiusInnerSqr;
    double radiusOuterSqr;

  public:
    Disk(const double radiusInner1, const double radiusOuter1);

    bool Hit(Vector3D& point, double sqrNorm, Vector3D& prevPoint, double prevSqrNorm,
        Vector3D& velocity, SchwarzschildBlackHoleEquation equation, double r, double theta,
        double phi, Color& color, bool stop, bool debug);

  protected:
    Vector3D IntersectionSearch(Vector3D prevPoint, Vector3D velocity, SchwarzschildBlackHoleEquation equation);

    CGL::Color GetColor(int side, double r, double theta, double phi);

};

#endif //BLACKHOLERAYTRACER_DISK_H
