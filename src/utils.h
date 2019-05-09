#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "CGL/CGL.h"
#include "CGL/Vector3D.h"
#include "CGL/Matrix4x4.h"
#include "ArgbColor.h"

using namespace CGL;
using namespace std;
using namespace cv;

namespace Utils {

  static void ToCartesian(const double r, const double theta, const double phi, double &x, double &y, double &z) {
    x = r * cos(phi) * sin(theta);
    y = r * sin(phi) * sin(theta);
    z = r * cos(theta);
  }

  static void ToSpherical(const double x, const double y, const double z, double &r, double &theta, double &phi) {
    r = sqrt(x * x + y * y + z * z);
    phi = atan2(y, x);
    theta = acos(z / r);
  }

  static void ToSpherical(const Vector3D v, double &r, double &theta, double &phi) {
    r = sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    phi = atan2(v.y, v.x);
    theta = acos(v.z / r);
  }

  static double DoubleMod(double n, double m) {
    double x = floor(n / m);
    return n - (m * x);
  }

  // Eliot: not sure about this one. let's see how it goes
  static Mat getNativeTextureBitmap(Mat texture) {
    return texture.clone();
  }

  // Used in Utils::AddColor()
  // https://stackoverflow.com/questions/23215600/algorithm-of-bitmap-getbrightness-in-c-sharp
  static float GetBrightness(Color c) {
    float r = c.r ;
    float g = c.g ;
    float b = c.b ;

    float max, min;

    max = r; min = r;

    if (g > max) max = g;
    if (b > max) max = b;

    if (g < min) min = g;
    if (b < min) min = b;

    return (max + min) / 2;
  }

  static int Cap(int x, int max) {
    if (x > max) {
      return max;
    }
    else {
      return x;
    }
  }

  static int CapMin(int x, int min) {
    if (x < min) {
      return min;
    }
    else {
      return x;
    }
  }

  static ArgbColor AddColor(ArgbColor hitColor, ArgbColor tintColor) {
    if (tintColor == ArgbColor::Transparent)
    {
      return hitColor;
    }
    float brightness = GetBrightness(tintColor);
    ArgbColor c;
//    c.r = Cap((int)((1.0 - brightness) * (hitColor.r * 255.0) + CapMin(tintColor.r * 255.0, 0) * 255. / (205. * 255.0)), 1.0);
//    c.g = Cap((int)((1.0 - brightness) * (hitColor.g * 255.0) + CapMin(tintColor.g * 255.0, 0) * 255. / (205. * 255.0)), 1.0);
//    c.b = Cap((int)((1.0 - brightness) * (hitColor.b * 255.0) + CapMin(tintColor.b * 255.0, 0) * 255. / (205. * 255.0)), 1.0);

      int R = Cap((int)((1 - brightness) * hitColor.r * 255.0) + CapMin(tintColor.r * 255.0, 0) * 255 / 205, 255);
      int G = Cap((int)((1 - brightness) * hitColor.g * 255.0) + CapMin(tintColor.g * 255.0, 0) * 255 / 205, 255);
      int B = Cap((int)((1 - brightness) * hitColor.b * 255.0) + CapMin(tintColor.b * 255.0, 0) * 255 / 205, 255);

      //convert to float
       c.r = CapMin(R / 255.0 , 0);
    c.g = CapMin(G / 255.0 , 0);
    c.b = CapMin(B / 255.0 , 0);


    return c;
  }


  // Transform a 3D Vector using a homogenous coord transform matrix
  // https://github.com/microsoft/referencesource/blob/master/System.Numerics/System/Numerics/Vector3.cs
  static Vector3D *transform(Vector3D position, Matrix4x4 matrix) {
    return new Vector3D(position.x * matrix(0,0) + position.y * matrix(1,0) + position.z * matrix(2,0) + matrix(3,0),
                        position.x * matrix(0,1) + position.y * matrix(1,1) + position.z * matrix(2,1) + matrix(3,1),
                        position.x * matrix(0,2) + position.y * matrix(1,2) + position.z * matrix(2,2) + matrix(3,2)
                        );
  }



  }

#endif /* UTILS_H */