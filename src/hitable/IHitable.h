
#include "CGL/CGL.h"
#include "../SchwarzschildBlackHoleEquation.h"
#include "../ArgbColor.h"

// IHitable is an abstract class with pure virtual functions, C++'s version of an interface

class IHitable {
  public:
    IHitable(){}
    ~IHitable(){}
    virtual bool Hit(Vector3D& point, double sqrNorm, Vector3D& prevPoint, double prevSqrNorm,
      Vector3D& velocity, SchwarzschildBlackHoleEquation equation, double r, double theta,
      double phi, ArgbColor& color, bool stop, bool debug) = 0;

};


