#ifndef SKY_H
#define SKY_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "../SchwarzschildBlackHoleEquation.h"
#include "../mappings/SphericalMapping.h"
#include "IHitable.h"
#include "../ArgbColor.h"

using namespace Models;
using namespace std;
using namespace cv;

class Sky : public IHitable{

private:
    SphericalMapping textureMap;
    int textureWidth;
    Mat textureBitmap;
    double textureOffset = 0;
    double radius;
    double radiusSqr;

public:
    Sky(Mat texture, double radius);

    Sky *SetTextureOffset(double offset);

    bool Hit(Vector3D& point, double sqrNorm, Vector3D& prevPoint, double prevSqrNorm,
           Vector3D& velocity, SchwarzschildBlackHoleEquation *equation, double r, double theta,
           double phi, ArgbColor& color, bool &stop, bool debug);

//protected:
//    Vector3D IntersectionSearch(Vector3D prevPoint, Vector3D velocity, SchwarzschildBlackHoleEquation equation);

};


#endif /* SKY_H */