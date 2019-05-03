#include "Horizon.h"
#include "../utils.h"

#include <opencv2/opencv.hpp>
#include <iostream>

#include "CGL/CGL.h"

using namespace CGL;
using namespace std;
using namespace CV;

Horizon::Horizon(Mat texture, bool checkered) {
	this->checkered = checkered;
	if (texture != NULL) {
		textureMap = new SphericalMapping(texture.cols, texture.rows);
		textureWidth = texture.cols;
		textureBitmap = getNativeTextureBitmap(texture);
	}
}

/*
var -> auto
Color.FromArgb -> uint8_t cast into Spectrum constructor
*/
bool Horizon::Hit(Vector3D &point, double sqrNorm, Vector3D prevPoint,
    double prevSqrNorm, Vector3D &velocity,
    SchwarzschildBlackHoleEquation equation, double r, double theta,
    double phi, Spectrum &color, bool &stop, bool debug) {

    if (prevSqrNorm > 1 && sqrNorm < 1) {
        Vector3D colpoint = IntersectionSearch(prevPoint, velocity, equation);

        double tempR = 0., tempTheta = 0., tempPhi = 0.;
        ToSpherical(colpoint.X, colpoint.Z, colpoint.Y, ref tempR, ref tempTheta, ref tempPhi);

        Spectrum col = Spectrum();
        if (checkered) {
            double m1 = DoubleMod(tempTheta, 1.04719); // Pi / 3
            double m2 = DoubleMod(tempPhi, 1.04719); // Pi / 3
            if ((m1 < 0.52359) ^ (m2 < 0.52359)) { // Pi / 6
                //col = Color.Green
                col = Spectrum(0., 1., 0.);
            }
        }
        else if (textureBitmap != NULL) {
            int xPos, yPos;
            textureMap.Map(r, theta, -phi, &xPos, &yPos); // TODO

            col = Spectrum((uint8_t)textureBitmap[yPos * textureWidth + xPos])
        }
        *color = Util.AddColor(col, color);
        *stop = true;
        return true;
    }
    return false;
}

Vector3D Horizon::IntersectionSearch(Vector3D prevPoint, Vector3D velocity,
                                     SchwarzschildBlackHoleEquation equation) {
    float stepLow = 0, stepHigh = equation.StepSize;
    Vector3D newPoint = prevPoint;
    Vector3D tempVelocity;
    while (true) {
        float stepMid = (stepLow + stepHigh) / 2;
        newPoint = prevPoint;
        tempVelocity = velocity;
        equation.Function(&newPoint, &tempVelocity, stepMid);

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
