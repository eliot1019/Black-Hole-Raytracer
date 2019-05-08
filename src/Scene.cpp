#include "Scene.h"
#include "SchwarzschildBlackHoleEquation.h"
#include "utils.h"
#include "CGL/CGL.h"
#include <CGL/Vector3D.h>
#include "CGL/Color.h"

using namespace CGL;
using namespace std;
using namespace cv;

Scene::Scene(Vector3D &CameraPosition, Vector3D &CameraLookAt, Vector3D &UpVector, float Fov, Vector3D<IHitable *>  &hitables, float CurvatureCoeff, float AngularMomentum) { // TODO: what should we use for List data structure
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

  SchwarzschildEquation = new SchwarzschildBlackHoleEquation(CurvatureCoeff);
}
