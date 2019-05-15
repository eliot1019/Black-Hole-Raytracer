#ifndef SPHERICALMAPPING_H
#define SPHERICALMAPPING_H

#include <iostream>

using namespace std;

struct SphericalMapping {
    private:
        int SizeX;
        int SizeY;

    public:
        SphericalMapping(int sizex, int sizey);

        void Map(double r, double theta, double phi, int &x, int &y);
        void MapCartesian(double x, double y, double z, int &u, int &v);
};

#endif /* SPHERICALMAPPING_H */