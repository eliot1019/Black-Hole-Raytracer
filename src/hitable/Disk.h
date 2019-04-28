#ifndef BLACKHOLERAYTRACER_DISK_H
#define BLACKHOLERAYTRACER_DISK_H


namespace CGL184 {
  struct Disk {
     double radiusInner;
     double radiusOuter;
     double radiusInnerSqr;
     double radiusOuterSqr;

    Disk(const double radiusInner1, const double radiusOuter1) : {
      radiusInner = radiusInner1;
      radiusOuter = radiusOuter1;
      radiusInnerSqr = radiusInner * radiusInner;
      radiusOuterSqr = radiusOuter * radiusOuter;
    }

    Spectrum

  };

}


#endif //BLACKHOLERAYTRACER_DISK_H
