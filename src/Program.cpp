#include "CGL/CGL.h"
#include "CGL/Vector3D.h"
#include "Scene.h"
#include "SchwarzschildRayProcessor.h"
#include "hitable/IHitable.h"
#include "hitable/TexturedDisk.h"
#include "hitable/Horizon.h"
#include "hitable/Sky.h"

#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace BlackHoleRaytracer;

int main( int argc, char** argv ) {
  Vector3D cameraPos = Vector3D(0, 3, -20);
  Vector3D lookAt = Vector3D(0, 0, 0);
  Vector3D up = Vector3D(-0.3, 1, 0);
  float fov = 55.0;
  float curvatureCoeff = -1.5;
  float angularMomentum = 0.0;
  string fileName = "output_image.png";

  std::vector<IHitable *> hitables;

  Mat diskImg = imread("/Users/eliothan/cs/cs184/blackhole-raytracer/src/disk_textured.png", IMREAD_UNCHANGED);
  Mat skyImg = imread("/Users/eliothan/cs/cs184/blackhole-raytracer/src/sky8k.png", IMREAD_UNCHANGED);
  Mat diskImgBmp, skyImgBmp;
  diskImg.convertTo(diskImgBmp, CV_8UC4);
  skyImg.convertTo(skyImgBmp, CV_8UC4);

  Mat horzTexture;

  hitables.push_back(new TexturedDisk(2.6, 12.0, diskImgBmp));
  hitables.push_back(new Horizon(horzTexture, false));
  hitables.push_back((new Sky(skyImgBmp, 30))->SetTextureOffset(M_PI / 2));

  Scene *scene = new Scene(cameraPos, lookAt, up, fov, hitables, curvatureCoeff, angularMomentum);

  SchwarzschildRayProcessor(352, 240, scene, fileName).Process();
}
