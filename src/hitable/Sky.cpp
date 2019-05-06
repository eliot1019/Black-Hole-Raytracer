#include <opencv2/opencv.hpp>
#include <iostream>

#include "CGL/CGL.h"
#include "Sky.h"
#include "../mappings/SphericalMapping.h"
#include "../utils.h"

using namespace CGL;
using namespace std;
using namespace cv;

Sky::Sky(Mat texture, double radius) {
    this->radius = radius;
    radiusSqr = radius * radius;
    if (texture != NULL) {
        textureMap = new SphericalMapping(texture.cols, texture.rows);
        textureWidth = texture.cols;
        textureBitmap = getNativeTextureBitmap(texture);
    }
}

Sky Sky::SetTextureOffset(double offset) {
    textureOffset = offset;
    return this;
}

bool Sky::Hit(Vector3D &point, double sqrNorm, Vector3D prevPoint,
    double prevSqrNorm, Vector3D &velocity, SchwarzschildBlackHoleEquation equation,
    double r, double theta, double phi, Spectrum &color, bool &stop, bool debug) {
    if (sqrNorm > radiusSqr) {
        int xPos, yPos;
        textureMap.Map(r, theta, phi, &xPos, &yPos);

        *color = AddColor((uint8_t)textureBitmap[yPos * textureWidth + xPos], color);
        *stop = true;
        return true;
    }
    return false;
}

Vector3D Sky::IntersectionSearch(Vector3D prevPoint, Vector3D velocity, SchwarzschildBlackHoleEquation equation) {
    float stepLow = 0., stepHigh = equation.StepSize;
    Vector3D newPoint = prevPoint;
    Vector3D tempVelocity;
    while (true) {
        float stepMid = (stepLow + stepHigh) / 2.;
        newPoint = prevPoint;
        tempVelocity = velocity;
        equation.Function(&newPoint, &tempVelocity, stepMid);

        double distance = newPoint.norm2();
        if (abs(stepHigh - stepLow) < 0.00001) {
            break;
        }
        if (distance > radius) {
            stepHigh = stepMid;
        }
        else {
            stepLow = stepMid;
        }
    }
    return newPoint;
}