#include "Horizon.h"
#include "../utils.h"
#include "../mappings/SphericalMapping.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include "../ArgbColor.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include "CGL/CGL.h"

using namespace CGL;
using namespace std;
using namespace cv;

Horizon::Horizon(Mat texture, bool checkered) : textureMap(texture.cols, texture.rows) {
	this->checkered = checkered;
	textureWidth = texture.cols;
	textureBitmap = Utils::getNativeTextureBitmap(texture);
}


bool Horizon::Hit(Vector3D& point, double sqrNorm, Vector3D& prevPoint, double prevSqrNorm,
                       Vector3D& velocity, SchwarzschildBlackHoleEquation *equation, double r, double theta,
                       double phi, ArgbColor& color, bool stop, bool debug) {

    // Has the ray fallen past the horizon?
    if (prevSqrNorm > 1 && sqrNorm < 1) {
        Vector3D colpoint = IntersectionSearch(prevPoint, velocity, equation);

        double tempR = 0., tempTheta = 0., tempPhi = 0.;
        Utils::ToSpherical(colpoint.x, colpoint.z, colpoint.y, tempR, tempTheta, tempPhi);

        ArgbColor col = ArgbColor::Black;
        if (checkered) {
            double m1 = Utils::DoubleMod(tempTheta, 1.04719); // Pi / 3
            double m2 = Utils::DoubleMod(tempPhi, 1.04719); // Pi / 3
            if ((m1 < 0.52359) ^ (m2 < 0.52359)) { // Pi / 6
                //col = Color.Green
                col = Color(0., 1., 0.);
            }
        }
        else if (!textureBitmap.empty()) {
          int xPos, yPos;
          textureMap.Map(r, theta, -phi, xPos, yPos);
          col = ArgbColor::fromArgb(textureBitmap.at<uint32_t>(yPos, xPos));
        }
        color = Utils::AddColor(col, color);
        stop = true;

        return true;
    }
    return false;
}

Vector3D Horizon::IntersectionSearch(Vector3D prevPoint, Vector3D velocity,
                                     SchwarzschildBlackHoleEquation *equation) {
    float stepLow = 0, stepHigh = equation->StepSize;
    Vector3D newPoint = prevPoint;
    Vector3D tempVelocity;
    while (true) {
        float stepMid = (stepLow + stepHigh) / 2;
        newPoint = prevPoint;
        tempVelocity = velocity;
        equation->Function(newPoint, tempVelocity, stepMid);

        double distance = newPoint.norm2();
        if (abs(stepHigh - stepLow) < 0.00001) {
            break;
        }
        if (distance < radius) {
            stepHigh = stepMid;
        }
        else {
            stepLow = stepMid;
        }
    }
    return newPoint;
}
