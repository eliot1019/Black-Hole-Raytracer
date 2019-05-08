#include "CGL/CGL.h"
#include "CGL/Matrix4x4.h"
#include "SchwarzschildRayProcessor.h"
#include "SchwarzschildBlackHoleEquation.h"
#include "ThreadParams.h"
#include "Scene.h"
#include "utils.h"
#include "hitable/IHitable.h"
#include "ArgbColor.h"

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

  // Primitive type defined in the form
  // CV_<bit-depth>{U|S|F}C(<number_of_channels>)
  // U = unsigned integer, S = signed integer, F = float
  // https://stackoverflow.com/questions/27183946/what-does-cv-8uc3-and-the-other-types-stand-for-in-opencv
  outputBitmap = Mat(height, width, CV_32SC4); //rows, cols, type

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
    tp->Thread = new std::thread(&SchwarzschildRayProcessor::RayTraceThread, tp);
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

void SchwarzschildRayProcessor::RayTraceThread(ThreadParams *threadParams) {
  ThreadParams param = *threadParams;
  cout << "Starting thread " << threadParams->JobId << endl;
  float tanFov = (float) tan((M_PI / 180.0) * scene.Fov);

  Vector3D front = scene.CameraLookAt - scene.CameraPosition;
  front.normalize();
  Vector3D left = cross(scene.UpVector, front);
  left.normalize();
  Vector3D nUp = cross(front, left);

  double matrixData[16] = {left.x, left.y, left.z, 0.0,
                          nUp.x, nUp.y, nUp.z, 0.0,
                          front.x, front.y, front.z, 0.0,
                          0.0, 0.0, 0.0, 0.0};
  Matrix4x4 viewMatrix = Matrix4x4(matrixData);


  bool debug = false;
  ArgbColor color;
  int x, yOffset;
  Vector3D point, prevPoint;
  double sqrNorm, prevSqrNorm;
  double tempR = 0, tempTheta = 0, tempPhi = 0;
  bool stop = false;

  try
  {
    for (int y : param.LinesList)
    {
      yOffset = y * width;
      for (x = 0; x < width; x++) {
        color = ArgbColor::Transparent;

        Vector3D view = Vector3D(((float)x / width - 0.5f) * tanFov,
                               ((-(float)y / height + 0.5f) * height / width) * tanFov,
                                (float) 1.0);
        view = *Utils::transform(view, viewMatrix);

        Vector3D normView = view / view.norm();

        Vector3D velocity = Vector3D(normView.X, normView.Y, normView.Z);

        point = scene.CameraPosition;
        sqrNorm = point.norm2();

        param.Equation.SetInitialConditions(point, velocity);

        for (int iter = 0; iter < NumIterations; iter++)
        {
          prevPoint = point;
          prevSqrNorm = sqrNorm;

          param.Equation.Function(point, velocity);
          sqrNorm = point.norm2();

          Utils::ToSpherical(point.x, point.y, point.z, tempR, tempTheta, tempPhi);

          // Check if the ray hits anything
          for(IHitable hitable : scene.hitables)
          {
            stop = false;
            if (hitable.Hit(point, sqrNorm, prevPoint, prevSqrNorm, velocity, param.Equation, tempR, tempTheta, tempPhi, color, stop, debug))
            {
              if (stop)
              {
                // The ray has found its stopping point (or rather its starting point).
                break;
              }
            }
          }
          if (stop)
          {
            break;
          }

        }

        outputBitmap.at<uint32_t>(y, x) = color.toArgb();

      }
      cout << "Thread " << param.JobId << ": Line " << y << " rendered." << endl;
    }
  }
  catch (Exception &e)
  {
    cout << "Thread " << param.JobId << ": Error " << e.msg << endl;
  }
  cout << "Thread " << param.JobId << " finished." << endl;
}

