#include "Quadratic.h"

namespace sag {
    Vector<number> Quadratic::step(Vector<number>& src) {
        number x = parameters[0] + (parameters[1] + parameters[2] * src.x + parameters[3] * src.y) * src.x + (parameters[4] + parameters[5] * src.y) * src.y;
        number y = parameters[6] + (parameters[7] + parameters[8] * src.x + parameters[9] * src.y) * src.x + (parameters[10] + parameters[11] * src.y) * src.y;
        
        return Vector<number>(x,y);
    }
}