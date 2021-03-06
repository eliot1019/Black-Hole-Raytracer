#ifndef BLACKHOLERAYTRACER_TEXTUREDDISK_H
#define BLACKHOLERAYTRACER_TEXTUREDDISK_H

#include "../SchwarzschildBlackHoleEquation.h"
#include "Disk.h"
#include "../ArgbColor.h"
#include "../utils.h"
#include "../mappings/DiscMapping.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace Models;
using namespace std;
using namespace cv;

class TexturedDisk : public Disk {
  private:
    DiscMapping textureMap;
    int textureWidth;
    Mat textureBitmap;

public:
  TexturedDisk(double radiusInner, double radiusOuter, Mat texture);

protected:
  ArgbColor GetColor(int side, double r, double theta, double phi);
};

#endif //BLACKHOLERAYTRACER_TEXTUREDDISK_H
