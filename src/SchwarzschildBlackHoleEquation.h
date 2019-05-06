#ifndef BLACKHOLERAYTRACER_SCHWARZSCHILDBLACKHOLEEQUATION_H
#define BLACKHOLERAYTRACER_SCHWARZSCHILDBLACKHOLEEQUATION_H


#include "CGL/CGL.h"
#include "CGL/vector3D.h"
#include <vector>


using namespace CGL;

struct SchwarzschildBlackHoleEquation {
  const float DefaultStepSize = 0.16f;

  float h2;
  float StepSize;

  /// Multiplier for the potential, ranging from 0 for no curvature, to -1.5 for full curvature.
  float PotentialCoefficient;

  // Used for Rk4 method
//    std::vector<double> *Y;
//    std::vector<double> *F;
//    std::vector<double> *K1;
//    std::vector<double> *K2;
//    std::vector<double> *K3;
//    std::vector<double> *K4;

  SchwarzschildBlackHoleEquation(float potentialCoef) {
//          Y = new std::vector<double>();
//          F = new std::vector<double>();
//          K1 = new std::vector<double>();
//          K2 = new std::vector<double>();
//          K3 = new std::vector<double>();
//          K4 = new std::vector<double>();
    PotentialCoefficient = potentialCoef;
    StepSize = DefaultStepSize;
  }

  // Note: this function marked as unsafe in c# code
  void SetInitialConditions(Vector3D& point, Vector3D& velocity) {
    Vector3D c = cross(point, velocity);
    h2 = c.norm2();
  }

  void Function(Vector3D& point, Vector3D& velocity)
  {
    Function(point, velocity, (point.norm() / 30.0) * StepSize);
  }

  void Function(Vector3D& point,  Vector3D& velocity, float step) {
    point += velocity * step;

    // this is the magical - 3/2 r^(-5) potential...
    Vector3D accel = PotentialCoefficient * h2 * point / (float)pow(point.norm2(), 2.5);
    velocity += accel * step;

    // C# project has commented out rk4 stuff here
  }

};


#endif //BLACKHOLERAYTRACER_SCHWARZSCHILDBLACKHOLEEQUATION_H
