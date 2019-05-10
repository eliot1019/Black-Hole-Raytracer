// Files taken from https://github.com/cal-cs184/p1-rasterizer/tree/master/CGL

#include "vector3D.h"

namespace CGL {

    std::ostream& operator<<(std::ostream& os, const Vector3D& v) {
        os << "(" << v.x << "," << v.y << "," << v.z << ")";
        return os;
    }

} // namespace CGL
