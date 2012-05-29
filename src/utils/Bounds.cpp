#include "Bounds.h"

namespace sag {
    bool Bounds::contains(number x, number y) {
        return (x >= xmin) && (x <= xmax) && (y >= ymin) && (y <= ymax);
    }
    
    bool Bounds::contains(Vector v) {
        return contains(v.x, v.y);
    }
}