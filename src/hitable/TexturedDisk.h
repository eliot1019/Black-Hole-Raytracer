#ifndef BLACKHOLERAYTRACER_TEXTUREDDISK_H
#define BLACKHOLERAYTRACER_TEXTUREDDISK_H

#include "CGL/CGL.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include "Disk.h"
#include "../utils.h"
#include "../mappings/DiscMapping.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace CGL;
using namespace std;
using namespace cv;

struct TexturedDisk : Disk {
  private:
    DiscMapping textureMap;
    int textureWidth;
    Mat textureBitmap;

public:
  TexturedDisk(double radiusInner, double radiusOuter, Mat texture);

protected:
  Color GetColor(int side, double r, double theta, double phi);
};

#endif //BLACKHOLERAYTRACER_TEXTUREDDISK_H
