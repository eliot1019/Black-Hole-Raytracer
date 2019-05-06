#ifndef BLACKHOLERAYTRACER_TEXTUREDDISK_H
#define BLACKHOLERAYTRACER_TEXTUREDDISK_H

#include "CGL/CGL.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include "Disk.h"
#include "../utils.h"
//#include "../mappings/DiscMapping.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace CGL;
using namespace std;
using namespace cv;

// TODO: Util.getNativeTextureBitMap, DiscMapping

struct TexturedDisk : Disk {
  private:
    DiscMapping textureMap;
    int textureWidth;
    Mat textureBitmap;

public:
  TexturedDisk(double radiusInner, double radiusOuter, Mat texture)
      : Disk(radiusInner, radiusOuter) {
    textureMap = new DiscMapping(radiusInner, radiusOuter, texture.Width, texture.Height);
    textureWidth = texture.cols;
    textureBitmap = Util.getNativeTextureBitmap(texture);
  }

protected:
  Color TexturedDisk::GetColor(int side, double r, double theta, double phi) {
    int xPos, yPos;
    textureMap.Map(r, theta, phi, &xPos, &yPos);
    return Utils::getColorFromArgbHEX(textureBitmap.at(yPos, xPos)); // row major order so like this apparently. needs testing
    // original code: return Color.FromArgb(textureBitmap[yPos * textureWidth + xPos]);
  }
};

#endif //BLACKHOLERAYTRACER_TEXTUREDDISK_H
