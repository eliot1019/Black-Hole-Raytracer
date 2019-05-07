#include "CGL/CGL.h"
#include "SchwarzschildRayProcessor.h"
#include "SchwarzschildBlackHoleEquation.h"
#include "ThreadParams.h"
#include "Scene.h"

#include <opencv2/opencv.hpp>
#include <iostream>
#include <thread>
#include <ctime>


using namespace CGL;
using namespace BlackHoleRaytracer;
using namespace cv;

SchwarzschildRayProcessor::SchwarzschildRayProcessor(int width, int height, Scene scene, string outputFileName) {
  this->width = width;
  this->height = height;
  this->scene = scene;
  this->outputFileName = outputFileName;
}

void SchwarzschildRayProcessor::Process() {
  // Create main bitmap for writing pixels
  outputBitmap = Mat(height, width, CV_32SC1); //rows, cols, type, I'm not about this type but we want a signed 32 bit int.

  int numThreads = 8; //Hardcoded for now? used to be Environment.ProcessorCount;
  //could try this too: std::thread::hardware_concurrency();
  time_t now = time(0);
  cout << "Launching " << numThreads << "threads..." << endl;

  // create a vector of numThreads size with empty vectors of type int
  std::vector<std::vector<int>> lineLists(numThreads);
  std::vector<ThreadParams *> paramList;

  for (int i = 0; i < numThreads; i++) {
    lineLists[i].resize(0);
    ThreadParams *tp = (ThreadParams *) malloc(sizeof(ThreadParams));
    tp->JobId = i;
    tp->LinesList = lineLists[i];
    tp->Equation = SchwarzschildBlackHoleEquation(scene.SchwarzschildEquation);
    tp->Thread = new std::thread(&SchwarzschildRayProcessor::RayTraceThread, this);
    paramList.push_back(tp);
  }

  // not sure what this does
  for (int j = 0; j < height; j++) {
    lineLists[j % numThreads].push_back(j);
  }

  for (auto param : paramList) {
    param->Thread->join();
  }

  imwrite(outputFileName, 1);
  //GCHandle gcHandle = GCHandle.Alloc(outputBitmap, GCHandleType.Pinned);
//  Bitmap resultBmp = new Bitmap(width, height, width * 4, PixelFormat.Format32bppArgb, gcHandle.AddrOfPinnedObject());
//  resultBmp.Save(outputFileName, ImageFormat.Png);
//  if (resultBmp != null) { resultBmp.Dispose(); resultBmp = null; }
//  if (gcHandle.IsAllocated) { gcHandle.Free(); }
  cout << "Finished in "<< time(0) - now << " seconds." << endl;
}

void SchwarzschildRayProcessor::RayTraceThread(ThreadParams threadParams) {

}