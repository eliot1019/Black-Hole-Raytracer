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
const ArgbColor ArgbColor::White  = ArgbColor(0xFF,0xFF,0xFF,0xFF);
const ArgbColor ArgbColor::Black  = ArgbColor(0xFF,0x00,0x00,0x00);
const ArgbColor ArgbColor::Transparent  = ArgbColor(0x00,0xFF,0xFF,0xFF);


// Replace C# project's Color.FromArgb() with this
ArgbColor ArgbColor::fromArgb(const cv::Vec3b x) {
  ArgbColor c;

  c.b = (uint8_t) x[0];
  c.g = (uint8_t) x[1];
  c.r = (uint8_t) x[2];
  c.a = 0xFF;

  return c;
}

std::ostream& operator<<(std::ostream &strm, const ArgbColor &c) {
  return strm << "[Alpha=" << unsigned(c.a) << ",Red=" << unsigned(c.r) << ",Green=" << unsigned(c.g) << ",Blue=" << unsigned(c.b) << "]";
}



// Output uint32_t that will be stored in our bitmaps
//uint32_t ArgbColor::toArgb( void ) const {
//  int A = (unsigned char) max( 0., min( 255.0, 255.0 * a ));
//  int R = (unsigned char) max( 0., min( 255.0, 255.0 * r ));
//  int G = (unsigned char) max( 0., min( 255.0, 255.0 * g ));
//  int B = (unsigned char) max( 0., min( 255.0, 255.0 * b ));
//
//  stringstream ss;
//  ss << hex;
//
//  ss << B << G << R << A;
//  string hexStr = ss.str();
//
//  // convert the string returned by to hex to an unsigned int
//  std::istringstream converter(hexStr);
//  unsigned int value;
//  converter >> std::hex >> value;
//
//  return value;
//}
