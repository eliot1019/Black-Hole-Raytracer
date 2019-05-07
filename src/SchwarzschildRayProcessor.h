#ifndef BLACKHOLERAYTRACER_SCHWARZSCHILDRAYPROCESSOR_H
#define BLACKHOLERAYTRACER_SCHWARZSCHILDRAYPROCESSOR_H

#include "CGL/CGL.h"
#include "SchwarzschildBlackHoleEquation.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "ThreadParams.h"
//#include "Scene.h"

using namespace CGL;
using namespace std;
using namespace cv;

namespace BlackHoleRaytracer {
  class SchwarzschildRayProcessor {
  private:
      int width;
      int height;
      Scene scene;

      Mat outputBitmap;
      String outputFileName;
      const int NumIterations = 10000;


  public:
      SchwarzschildRayProcessor(int width, int height, Scene scene, string outputFileName);
      void Process();
      void RayTraceThread(ThreadParams threadParams);

  };



}

#endif //BLACKHOLERAYTRACER_SCHWARZSCHILDRAYPROCESSOR_H
