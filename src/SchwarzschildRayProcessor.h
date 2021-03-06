#ifndef BLACKHOLERAYTRACER_SCHWARZSCHILDRAYPROCESSOR_H
#define BLACKHOLERAYTRACER_SCHWARZSCHILDRAYPROCESSOR_H

#include "SchwarzschildBlackHoleEquation.h"
#include <opencv2/opencv.hpp>
#include <iostream>
#include "ThreadParams.h"
#include "Scene.h"

using namespace Models;
using namespace std;
using namespace cv;

namespace BlackHoleRaytracer {

class SchwarzschildRayProcessor {
 private:
      int width;
      int height;
      Scene *scene;

      Mat outputBitmap;
      String outputFileName;
      const int NumIterations = 10000;
       std::vector<std::thread*> workerThreads;  ///< pool of worker threads


 public:
      SchwarzschildRayProcessor(int width, int height,
          Scene *scene, string outputFileName);
      void Process();
      void RayTraceThread(ThreadParams &threadParams);
};

}  // namespace BlackHoleRaytracer

#endif  // BLACKHOLERAYTRACER_SCHWARZSCHILDRAYPROCESSOR_H
