#include "Disk.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include "../utils.h"
#include "../mappings/SphericalMapping.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include "CGL/CGL.h"
#include <CGL/vector3D.h>
#include "CGL/Color.h"

using namespace CGL;
using namespace std;
using namespace cv;

Scene::Scene(Vector3D &CameraPosition, Vector3 &CameraLookAt, Vector3 &UpVector, float Fov, List<IHitable> hitables, float CurvatureCoeff, float AngularMomentum) { // TODO: what should we use for List data structure
  this->CameraPosition = CameraPosition;
  this->CameraLookAt = CameraLookAt;
  this->UpVector = UpVector;
  this->hitables = hitables;
  this->Fov = Fov;

  double tempR = 0;
  double tempTheta = 0;
  double tempPhi = 0;

  Utils::ToSpherical(CameraPosition.X, CameraPosition.Y, CameraPosition.Z, ref tempR, ref tempTheta, ref tempPhi);
  CameraDistance = tempR;
  CameraAngleVert = tempTheta;
  CameraAngleHorz = tempPhi - 0.1;

  // TODO: tie into SchwarzschildBlackHoleEquation object implementation
  // SchwarzschildEquation = new SchwarzschildBlackHoleEquation(CurvatureCoeff);
  // KerrEquation = new KerrBlackHoleEquation(CameraDistance, CameraAngleHorz, CameraAngleVert, AngularMomentum);

}
