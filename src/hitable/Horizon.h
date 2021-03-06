#ifndef HORIZON_H
#define HORIZON_H

#include "../SchwarzschildBlackHoleEquation.h"
#include "../mappings/SphericalMapping.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "IHitable.h"
#include "../ArgbColor.h"

using namespace Models;
using namespace std;
using namespace cv;

class Horizon : public IHitable{

	private:
		bool checkered;

		SphericalMapping *textureMap;
		int textureWidth;
		Mat textureBitmap;
		double radius = 1.0;
		bool textureBitmapIsNull = true;

	public:
		Horizon(Mat texture, bool checkered);

		bool Hit(Vector3D& point, double sqrNorm, Vector3D& prevPoint, double prevSqrNorm,
					 Vector3D& velocity, SchwarzschildBlackHoleEquation *equation, double r, double theta,
					 double phi, ArgbColor& color, bool &stop, bool debug);

	protected:
        Vector3D IntersectionSearch(Vector3D prevPoint, Vector3D velocity, SchwarzschildBlackHoleEquation *equation);

};


#endif /* HORIZON_H */