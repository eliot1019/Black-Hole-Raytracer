#ifndef BLACKHOLERAYTRACER_SCHWARZSCHILDBLACKHOLEEQUATION_H
#define BLACKHOLERAYTRACER_SCHWARZSCHILDBLACKHOLEEQUATION_H

#include "models/vector3D.h"

#include <vector>


using namespace Models;

struct SchwarzschildBlackHoleEquation {
  const float DefaultStepSize = 0.16f;

  float h2;
  float StepSize;

  // Multiplier for the potential
  // ranging from 0 for no curvature, to -1.5 for full curvature
  float PotentialCoefficient;

  explicit SchwarzschildBlackHoleEquation(float potentialCoef) {
    PotentialCoefficient = potentialCoef;
    StepSize = DefaultStepSize;
  }

  SchwarzschildBlackHoleEquation(SchwarzschildBlackHoleEquation &other) {
    this->StepSize = other.StepSize;
    this->PotentialCoefficient = other.PotentialCoefficient;
  }

  // Note: this function marked as unsafe in c# code
  void SetInitialConditions(Vector3D& point, Vector3D& velocity) {
    Vector3D c = cross(point, velocity);
    h2 = c.norm2();
  }

  void Function(Vector3D& point, Vector3D& velocity) {
    Function(point, velocity, (point.norm() / 30.0) * StepSize);
  }

  void Function(Vector3D& point, Vector3D& velocity, float step) {
    point += velocity * step;

    // this is the magical - 3/2 r^(-5) potential...
    Vector3D accel = PotentialCoefficient * h2 *
        point / (float)pow(point.norm2(), 2.5);
    velocity += accel * step;
  }
};


#endif  // BLACKHOLERAYTRACER_SCHWARZSCHILDBLACKHOLEEQUATION_H
