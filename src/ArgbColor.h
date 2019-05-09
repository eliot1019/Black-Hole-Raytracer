#ifndef BLACKHOLERAYTRACER_ARGBCOLOR_H
#define BLACKHOLERAYTRACER_ARGBCOLOR_H

#include "CGL/color.h"
#include <opencv2/opencv.hpp>

using namespace CGL;

class ArgbColor : public Color{
public:
  float a = 1.0; // alpha channel
  static const ArgbColor White;
  static const ArgbColor Black;
  static const ArgbColor Transparent;

  ArgbColor( float a = 1.0, float r = 0, float g = 0, float b = 0 )
        : Color(r,g,b), a(a) { }

  ArgbColor(Color c) : Color(c.r, c.g, c.b) {}

  // NOTE: Don't use ArgbColor's array indexing or array constructor.

  ArgbColor( const unsigned char* arr ) {
    throw "Don't use ArgbColor's array indexing or array constructor.";
  }

  // Array-style access
  float& operator[](int k) {
    throw "Don't use ArgbColor's array indexing or array constructor.";
    //return (&a)[k];
  }
  const float& operator[](int k) const {
    //return (&a)[k];
    throw "Don't use ArgbColor's array indexing or array constructor.";
  }

  // Addition.
  inline ArgbColor operator+( const ArgbColor& rhs ) const {
    return ArgbColor( a + rhs.a, r + rhs.r, g + rhs.g, b + rhs.b);
  }

  inline ArgbColor& operator+=( const ArgbColor& rhs ) {
    a+= rhs.a; r += rhs.r; g += rhs.g; b += rhs.b;
    return *this;
  }

  // Vector multiplication.
  inline ArgbColor operator*( const ArgbColor& rhs ) const {
    return ArgbColor( a * rhs.a, r * rhs.r, g * rhs.g, b * rhs.b);
  }

  inline ArgbColor& operator*=( const ArgbColor& rhs ) {
    a*= rhs.a; r *= rhs.r; g *= rhs.g; b *= rhs.b;
    return *this;
  }

  // Scalar multiplication.
  inline ArgbColor operator*( float s ) const {
    return ArgbColor( a * s, r * s, g * s, b * s );
  }

  inline ArgbColor& operator*=( float s ) {
    a *= s; r *= s; g *= s; b *= s;
    return *this;
  }

  // comparison
  inline bool operator==( const ArgbColor& rhs ) const {
    return a == rhs.a && r == rhs.r && g == rhs.g && b == rhs.b;
  }

  inline bool operator!=( const ArgbColor& rhs ) const {
    return !operator==( rhs );
  }

  /**
   * Construct a ArgbColor object from a uint32_t in argb format
   */
   //https://en.wikipedia.org/wiki/RGBA_color_space#ARGB_(word-order)
  static ArgbColor fromArgb( cv::Vec4b x );

  /**
   * Returns a 32 bit integer in ARGB format
   */
  uint32_t toArgb( ) const;
};


#endif //BLACKHOLERAYTRACER_ARGBCOLOR_H
