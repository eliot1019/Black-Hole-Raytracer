#ifndef SCENE_H
#define SCENE_H

#include "CGL/CGL.h"
#include <opencv2/opencv.hpp>
#include <CGL/Vector3D.h>
#include <iostream>

using namespace CGL;
using namespace std;
using namespace cv;

struct Scene {
  public:
    Scene(Vector3D &CameraPosition, Vector3D &CameraLookAt, Vector3D &UpVector, float Fov, List<IHitable> hitables, float CurvatureCoeff, float AngularMomentum); // TODO: what should we use for List data structure

    double Vector3D<IHitable *> hitables();

    SchwarzschildBlackHoleEquation SchwarzschildEquation();
};

#endif // SCENE_H
