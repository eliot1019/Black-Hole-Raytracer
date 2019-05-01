#ifndef HORIZON_H
#define HORIZON_H

#include <opencv2/opencv.hpp>
#include <iostream>

#include "CGL/CGL.h"

using namespace CGL;
using namespace std;
using namespace CV;

/* 
TODOS:

Define `SphericalMapping` under `BlackHoleRaytracer/Mappings/SphericalMapping.cs`

*Notes

Equivalents:
ref -> &
Vector3 -> Vector3D
Bitmap -> Mat
Color -> Spectrum

*/

// Struct definition + method signatures
struct Horizon {

	private:
		bool checkered;

		SphericalMapping textureMap;
		int textureWidth;
		int[] textureBitmap;
		double radius = 1.0;

	public:
		Horizon(Mat texture, bool checkered);

		bool Hit(Vector3D &point, double sqrNorm, Vector3D prevPoint,
			double prevSqrNorm, Vector3D &velocity,
			SchwarzschildBlackHoleEquation equation, double r, double theta,
			double phi, Spectrum &color, bool &stop, bool debug);

	protected:
        Vector3D IntersectionSearch(Vector3D prevPoint, Vector3D velocity,
            SchwarzschildBlackHoleEquation equation);

};


#endif /* HORIZON_H */