#include "Horizon.h"
#include "../utils.h"
#include "../mappings/SphericalMapping.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include "../ArgbColor.h"

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace Models;
using namespace std;
using namespace cv;

Horizon::Horizon(Mat texture, bool checkered)  {
	this->checkered = checkered;
	if (!texture.empty()) {
	  cout << "horizon texture is not empty" << endl;
    textureWidth = texture.cols;
    textureBitmap = texture.clone();
    textureBitmapIsNull = false;
    textureMap = new SphericalMapping(texture.cols, texture.rows);
	}
}


bool Horizon::Hit(Vector3D& point, double sqrNorm, Vector3D& prevPoint, double prevSqrNorm,
                       Vector3D& velocity, SchwarzschildBlackHoleEquation *equation, double r, double theta,
                       double phi, ArgbColor& color, bool &stop, bool debug) {

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
                col = ArgbColor(0xFF, 0x00, 0x80, 0x00);
            }
        }
        else if (!textureBitmapIsNull) {
          cout << "texturebitmap for horizon not null" << endl;
          int xPos, yPos;
          textureMap->Map(r, theta, -phi, xPos, yPos);
          col = ArgbColor::fromArgb(textureBitmap.at<Vec3b>(yPos, xPos));
        }
        color = Utils::AddColor(col, color);
        //cout << color << endl;
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
