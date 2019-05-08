#ifndef BLACKHOLERAYTRACER_THREADPARAMS_H
#define BLACKHOLERAYTRACER_THREADPARAMS_H

#include "SchwarzschildBlackHoleEquation.h"
#include <thread>

using namespace std;

struct ThreadParams {
  int JobId;
  std::vector<int> LinesList;
  SchwarzschildBlackHoleEquation Equation;
  std::thread * Thread;
};


#endif //BLACKHOLERAYTRACER_THREADPARAMS_H
