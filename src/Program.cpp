#include <stdio.h>
#include <stdlib.h>
#include <opencv2/opencv.hpp>

#ifdef _WIN32
#include <corecrt_math_defines.h>
#endif

#include "models/Vector3D.h"
#include "Scene.h"
#include "SchwarzschildRayProcessor.h"
#include "hitable/IHitable.h"
#include "hitable/TexturedDisk.h"
#include "hitable/Horizon.h"
#include "hitable/Sky.h"


using namespace std;
using namespace cv;
using namespace BlackHoleRaytracer;

int main(int argc, char** argv) {
  // Set attributes of the camera
  Vector3D cameraPos = Vector3D(0, 3, -20);
  Vector3D lookAt = Vector3D(0, 0, 0);
  Vector3D up = Vector3D(-0.3, 1, 0);
  float fov = 55.0;
  float curvatureCoeff = -1.5;
  float angularMomentum = 0.0;

  // Output filename
  string fileName = "out.jpg";

  // List of objects in the scene
  std::vector<IHitable *> hitables;

  // Load image from given location and convert to 3 channel matrices.
  // Because of an issue with OpenCV on Mac, must use full path on your machine
  Mat diskImg = imread("images/disk_textured.png", 1);
  Mat skyImg = imread("images/sky8k.jpg", 1);
  Mat diskImgBmp, skyImgBmp;
  diskImg.convertTo(diskImgBmp, CV_8UC3);
  skyImg.convertTo(skyImgBmp, CV_8UC3);

  Mat horzTexture;

  hitables.push_back(new TexturedDisk(2.6, 12.0, diskImgBmp));
  hitables.push_back(new Horizon(horzTexture, false));
  hitables.push_back((new Sky(skyImgBmp, 30))->SetTextureOffset(M_PI / 2));

  Scene *scene = new Scene(cameraPos, lookAt, up, fov,
      hitables, curvatureCoeff, angularMomentum);

  // Start rendering the scene with given quality (currently 1280 x 720 pixels)
  SchwarzschildRayProcessor(1280, 720, scene, fileName).Process();
}
