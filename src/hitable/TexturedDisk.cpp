#include "TexturedDisk.h"
#include "CGL/CGL.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include "../utils.h"
#include "../ArgbColor.h"
#include "../mappings/DiscMapping.h"
#include <opencv2/opencv.hpp>
#include <iostream>


TexturedDisk::TexturedDisk(double radiusInner, double radiusOuter, Mat texture)
    : Disk(radiusInner, radiusOuter), textureMap(radiusInner, radiusOuter, texture.cols, texture.rows) {
  textureWidth = texture.cols;
  textureBitmap = texture.clone();
}

ArgbColor TexturedDisk::GetColor(int side, double r, double theta, double phi) {
  int xPos, yPos;
  textureMap.Map(r, theta, phi, xPos, yPos);
  return ArgbColor::fromArgb(textureBitmap.at<Vec3b>(yPos, xPos)); // row major order so like this apparently. needs testing
  // original code: return Color.FromArgb(textureBitmap[yPos * textureWidth + xPos]);
}