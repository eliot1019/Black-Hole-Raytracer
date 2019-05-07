#include "TexturedDisk.h"
#include "CGL/CGL.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include "../utils.h"
#include "../mappings/DiscMapping.h"
#include <opencv2/opencv.hpp>
#include <iostream>

TexturedDisk::TexturedDisk(double radiusInner, double radiusOuter, Mat texture)
    : Disk(radiusInner, radiusOuter), textureMap(radiusInner, radiusOuter, texture.cols, texture.rows) {
  textureWidth = texture.cols;
  textureBitmap = Utils::getNativeTextureBitmap(texture);
}

Color TexturedDisk::GetColor(int side, double r, double theta, double phi) {
  int xPos, yPos;
  textureMap.Map(r, theta, phi, xPos, yPos);
  return Utils::getColorFromArgbHex(textureBitmap.at<char *>(yPos, xPos)); // row major order so like this apparently. needs testing
  // original code: return Color.FromArgb(textureBitmap[yPos * textureWidth + xPos]);
}