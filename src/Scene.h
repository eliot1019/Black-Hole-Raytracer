#ifndef SCENE_H
#define SCENE_H

#include "CGL/CGL.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace CGL;
using namespace std;
using namespace cv;

struct Scene {
  public:
    Scene(Vector3D &CameraPosition, Vector3 &CameraLookAt, Vector3 &UpVector, float Fov, List<IHitable> hitables, float CurvatureCoeff, float AngularMomentum); // TODO: what should we use for List data structure

    Vector3D CameraPosition();
    Vector3D CameraLookAt();
    Vector3D UpVector();
    Vector3D Fov();

    double CameraDistance();
    double CameraAngleHorz();
    double CameraAngleVert();
    double CameraTilt();
    double CameraYaw();
    double List<Disk> hitables(); // TODO: what list datastructure should we use?

    SchwarzschildBlackHoleEquation SchwarzschildEquation(); // TODO: tie to SchwarzschildBlackHoleEquation object implementation
};

#endif // SCENE_H
