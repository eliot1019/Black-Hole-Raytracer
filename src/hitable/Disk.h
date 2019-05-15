#ifndef BLACKHOLERAYTRACER_DISK_H
#define BLACKHOLERAYTRACER_DISK_H

#include "../ArgbColor.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "IHitable.h"

using namespace Models;
using namespace std;
using namespace cv;

class Disk : public IHitable{
  private:
    double radiusInner;
    double radiusOuter;
    double radiusInnerSqr;
    double radiusOuterSqr;

  public:
    Disk(double radiusInner, double radiusOuter);

    bool Hit(Vector3D& point, double sqrNorm, Vector3D& prevPoint, double prevSqrNorm,
        Vector3D& velocity, SchwarzschildBlackHoleEquation *equation, double r, double theta,
        double phi, ArgbColor& color, bool &stop, bool debug);

  protected:
    Vector3D IntersectionSearch(int side, Vector3D prevPoint, Vector3D velocity, SchwarzschildBlackHoleEquation *equation);

    virtual ArgbColor GetColor(int side, double r, double theta, double phi);

};

#endif //BLACKHOLERAYTRACER_DISK_H
