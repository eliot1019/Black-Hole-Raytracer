#include "ArgbColor.h"

#include <stdio.h>
#include <string.h>
#include <ostream>
#include <sstream>
#include <iomanip>
#include <opencv2/opencv.hpp>

using namespace std;

// Color table
// https://docs.microsoft.com/en-us/dotnet/api/system.windows.media.colors?redirectedfrom=MSDN&view=netframework-4.8
const ArgbColor ArgbColor::White  = ArgbColor(1,1,1,1);
const ArgbColor ArgbColor::Black  = ArgbColor(1,0,0,0);
const ArgbColor ArgbColor::Transparent  = ArgbColor(0,1,1,1);

// Will skip the array constructor from Color. Don't use it for ARGB


// Replace C# project's Color.FromArgb(Int32) with this
ArgbColor ArgbColor::fromArgb(const cv::Vec4b x) {
  // Extract 8-byte chunks and normalize.
  ArgbColor c;
//  c.b = (float)( ( x & 0xFF000000 ) >> 24 ) / 255.0;
//  c.g = (float)( ( x & 0x00FF0000 ) >> 16 ) / 255.0;
//  c.r = (float)( ( x & 0x0000FF00 ) >>  8 ) / 255.0;
//  c.a = 1.0;

  c.b = (float)(x[0] / 255.0);
  c.g = (float)(x[1] / 255.0);
  c.r = (float)(x[2] / 255.0);
  c.a = (float)(x[3] / 255.0);

  return c;
}

// Output uint32_t that will be stored in our bitmaps
uint32_t ArgbColor::toArgb( void ) const {
  int A = (unsigned char) max( 0., min( 255.0, 255.0 * a ));
  int R = (unsigned char) max( 0., min( 255.0, 255.0 * r ));
  int G = (unsigned char) max( 0., min( 255.0, 255.0 * g ));
  int B = (unsigned char) max( 0., min( 255.0, 255.0 * b ));

  stringstream ss;
  ss << hex;

  ss << B << G << R << A;
  string hexStr = ss.str();

  // convert the string returned by to hex to an unsigned int
  std::istringstream converter(hexStr);
  unsigned int value;
  converter >> std::hex >> value;

  return value;
}
