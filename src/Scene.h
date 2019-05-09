#ifndef SCENE_H
#define SCENE_H

#include "CGL/CGL.h"
#include "CGL/Vector3D.h"
#include "hitable/IHitable.h"
#include "utils.h"

#include <opencv2/opencv.hpp>
#include <iostream>

using namespace CGL;
using namespace std;
using namespace cv;

struct Scene {
  public:
    Vector3D CameraPosition;
    Vector3D CameraLookAt;
    Vector3D UpVector;

    float Fov;
    double CameraDistance;
    double CameraAngleHorz;
    double CameraAngleVert;
    double CameraTilt;

    vector<IHitable *> hitables;
    SchwarzschildBlackHoleEquation *SchwarzschildEquation;



    Scene(Vector3D &CameraPosition, Vector3D &CameraLookAt, Vector3D &UpVector, float Fov, vector<IHitable *> hitables,
        float CurvatureCoeff, float AngularMomentum) {
      this->CameraPosition = CameraPosition;
      this->CameraLookAt = CameraLookAt;
      this->UpVector = UpVector;
      this->hitables = hitables;
      this->Fov = Fov;

      double tempR = 0;
      double tempTheta = 0;
      double tempPhi = 0;

      Utils::ToSpherical(CameraPosition.x, CameraPosition.y, CameraPosition.z, tempR, tempTheta, tempPhi);
      this->CameraDistance = tempR;
      this->CameraAngleVert = tempTheta;
      this->CameraAngleHorz = tempPhi - 0.1;
      this->SchwarzschildEquation = new SchwarzschildBlackHoleEquation(CurvatureCoeff);
    }

};

#endif // SCENE_H
