#ifndef BLACKHOLERAYTRACER_ARGBCOLOR_H
#define BLACKHOLERAYTRACER_ARGBCOLOR_H

#include <opencv2/opencv.hpp>


class ArgbColor {
 public:
    uint8_t a;  // alpha channel
    uint8_t r;  // < value of red chanel
    uint8_t g;  // < value of green chanel
    uint8_t b;  // < value of blue chanel
    static const ArgbColor White;
    static const ArgbColor Black;
    static const ArgbColor Transparent;

    ArgbColor(uint8_t a = 255, uint8_t r = 0,
        uint8_t g = 0, uint8_t b = 0) : r(r), g(g), b(b), a(a) { }

    // const dog
    friend std::ostream& operator<<(std::ostream& strm, const ArgbColor& c);

    // comparison
    inline bool operator==(const ArgbColor& rhs) const {
    return a == rhs.a && r == rhs.r && g == rhs.g && b == rhs.b;
    }

    inline bool operator!=(const ArgbColor& rhs) const {
    return !operator==( rhs );
    }

    /*
    Construct a ArgbColor object from a uint32_t in argb format
    https://en.wikipedia.org/wiki/RGBA_color_space#ARGB_(word-order)
    */
    static ArgbColor fromArgb(cv::Vec3b x);
};


#endif  // BLACKHOLERAYTRACER_ARGBCOLOR_H
