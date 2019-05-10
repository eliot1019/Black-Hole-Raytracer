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

SchwarzschildRayProcessor::SchwarzschildRayProcessor(int width, int height, Scene *scene, string outputFileName) {
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
  outputBitmap = Mat(height, width, CV_8UC3); //rows, cols, type
  //CV_Assert(outputBitmap.channels() == 4);

  int numThreads = 8; //Hardcoded for now? used to be Environment.ProcessorCount;
  //could try this too: std::thread::hardware_concurrency();
  time_t now = time(0);
  cout << "Launching " << numThreads << " threads..." << endl;

  std::vector<std::vector<int> *> lineLists;
  std::vector<ThreadParams> paramList;
  workerThreads.resize(numThreads);

  for (int i = 0; i < numThreads; i++) {
    std::vector<int> *lineList = new std::vector<int>;
    lineLists.push_back(lineList);
    ThreadParams tp;
    tp.JobId = i;
    tp.LinesList = lineList;
    tp.Equation = new SchwarzschildBlackHoleEquation(*scene->SchwarzschildEquation);
    paramList.push_back(tp);
  }
  cout << "made paramList" << endl;
  for (int j = 0; j < height; j++) {
    lineLists[j % numThreads]->push_back(j);
  }
  cout << "made linelists" << endl;
  cout << "eliot " << lineLists[0]->size() << endl;

  for (int a = 0; a < numThreads; a++) {
    workerThreads[a] = new std::thread{&SchwarzschildRayProcessor::RayTraceThread, this, std::ref(paramList[a])};
  }

  for (int k = 0; k < workerThreads.size(); k++) {
    workerThreads[k]->join();
  }

  imwrite(outputFileName, outputBitmap);
  cout << "Finished in "<< time(0) - now << " seconds." << endl;
}

void SchwarzschildRayProcessor::RayTraceThread(ThreadParams &threadParams) {
  cout << "Starting thread " << threadParams.JobId << endl;
  float tanFov = (float) tan((M_PI / 180.0) * scene->Fov);

  Vector3D front = scene->CameraLookAt - scene->CameraPosition;
  front.normalize();
  Vector3D left = cross(scene->UpVector, front);
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

  //cout << "test " << threadParams.LinesList->size() << endl;

  try
  {
    for (int y : *(threadParams.LinesList))
    {
      //cout << "got here 1" << endl;
      yOffset = y * width;
      for (x = 0; x < width; x++) {
        color = ArgbColor::Transparent;

        Vector3D view = Vector3D(((float)x / width - 0.5f) * tanFov,
                               ((-(float)y / height + 0.5f) * height / width) * tanFov,
                                (float) 1.0);
        view = *Utils::transform(view, viewMatrix);

        Vector3D normView = view / view.norm();

        Vector3D velocity = Vector3D(normView.x, normView.y, normView.z);

        point = scene->CameraPosition;
        sqrNorm = point.norm2();

        threadParams.Equation->SetInitialConditions(point, velocity);

        for (int iter = 0; iter < NumIterations; iter++) {
          prevPoint = point;
          prevSqrNorm = sqrNorm;

          threadParams.Equation->Function(point, velocity);
          sqrNorm = point.norm2();

          Utils::ToSpherical(point.x, point.y, point.z, tempR, tempTheta, tempPhi);

          // Check if the ray hits anything
          for(IHitable *hitable : scene->hitables) {
            stop = false;
            if (hitable->Hit(point, sqrNorm, prevPoint, prevSqrNorm, velocity, threadParams.Equation, tempR,
                tempTheta, tempPhi, color, stop, debug)) {
              if (stop)
              {
                // The ray has found its stopping point (or rather its starting point).
                break;
              }
            }
          }
          if (stop) {
            break;
          }
        }

        Vec3b c;
        c[0] = (uchar)color.b;
        c[1] = (uchar)color.g;
        c[2] = (uchar)color.r;
        outputBitmap.at<Vec3b>(y, x) = c;
        //cout << c << endl;

      }
      cout << "Thread " << threadParams.JobId << ": Line " << y << " rendered." << endl;
    }
  }
  catch (Exception &e)
  {
    cout << "Thread " << threadParams.JobId << ": Error " << e.msg << endl;
  }
  cout << "Thread " << threadParams.JobId << " finished." << endl;
}

