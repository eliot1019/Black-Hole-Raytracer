#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <opencv2/opencv.hpp>
#include "CGL/CGL.h"
#include "CGL/Color.h"
#include "CGL/Vector3D.h"

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
    float r = (float)c.r / 255.0f;
    float g = (float)c.g / 255.0f;
    float b = (float)c.b / 255.0f;

    float max, min;

    max = r; min = r;

    if (g > max) max = g;
    if (b > max) max = b;

    if (g < min) min = g;
    if (b < min) min = b;

    return (max + min) / 2;
  }


// Based off CGL's color.cpp fromHex(). Only difference is to also zero out alpha value
// Replace C# project's Color.FromArgb(Int32) with this
  static Color getColorFromArgbHex(const char* s) {
    // Ignore leading hashmark.
    if( s[0] == '#' ) {
      s++;
    }

    // Set stream formatting to hexadecimal.
    stringstream ss;
    ss << hex;

    // Convert to integer.
    unsigned int rgb;
    ss << s;
    ss >> rgb;

    // Extract 8-byte chunks and normalize.
    Color c;
    c.r = (float)( ( rgb & 0x00FF0000 ) >> 16 ) / 255.0;
    c.g = (float)( ( rgb & 0x0000FF00 ) >>  8 ) / 255.0;
    c.b = (float)( ( rgb & 0x000000FF ) >>  0 ) / 255.0;

    return c;
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

  static Color AddColor(Color hitColor, Color tintColor) {
    // Assuming tintColor is not transparent
    float brightness = GetBrightness(tintColor);
    Color c;
    c.r = Cap((int)(1. - brightness) * hitColor.r + CapMin(tintColor.r, 0) * 255. / 205., 255);
    c.g = Cap((int)(1. - brightness) * hitColor.g + CapMin(tintColor.g, 0) * 255. / 205., 255);
    c.b = Cap((int)(1. - brightness) * hitColor.b + CapMin(tintColor.b, 0) * 255. / 205., 255);
    return c;
  }

}

#endif /* UTILS_H */