#include <opencv2/opencv.hpp>
#include <iostream>

#include "CGL/CGL.h"
#include "Sky.h"
#include "../mappings/SphericalMapping.h"
#include "../utils.h"
#include "../ArgbColor.h"

using namespace CGL;
using namespace std;
using namespace cv;

Sky::Sky(Mat texture, double radius) : textureMap(texture.cols, texture.rows) {
    this->radius = radius;
    radiusSqr = radius * radius;
    if (!texture.empty()) {
        textureWidth = texture.cols;
        textureBitmap = Utils::getNativeTextureBitmap(texture);

    }
}

Sky *Sky::SetTextureOffset(double offset) {
    textureOffset = offset;
    return this; // may need to change return type of function to Sky* instead
}

bool Sky::Hit(Vector3D& point, double sqrNorm, Vector3D& prevPoint, double prevSqrNorm,
                   Vector3D& velocity, SchwarzschildBlackHoleEquation *equation, double r, double theta,
                   double phi, ArgbColor& color, bool stop, bool debug) {
    if (sqrNorm > radiusSqr) {
        int xPos, yPos;
        textureMap.Map(r, theta, phi, xPos, yPos);
        color = Utils::AddColor(ArgbColor::fromArgb(textureBitmap.at<Vec4b>(yPos, xPos)), color);
        stop = true;
        return true;
    }
    return false;
}

//Vector3D Sky::IntersectionSearch(Vector3D prevPoint, Vector3D velocity, SchwarzschildBlackHoleEquation *equation) {
//    float stepLow = 0., stepHigh = equation.StepSize;
//    Vector3D newPoint = prevPoint;
//    Vector3D tempVelocity;
//    while (true) {
//        float stepMid = (stepLow + stepHigh) / 2.;
//        newPoint = prevPoint;
//        tempVelocity = velocity;
//        equation->Function(newPoint, tempVelocity, stepMid);
//
//        double distance = newPoint.norm2();
//        if (abs(stepHigh - stepLow) < 0.00001) {
//            break;
//        }
//        if (distance > radius) {
//            stepHigh = stepMid;
//        }
//        else {
//            stepLow = stepMid;
//        }
//    }
//    return newPoint;
//}