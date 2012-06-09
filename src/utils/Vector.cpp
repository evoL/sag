#include "Vector.h"

#include <sstream>
#include "Random.h"

namespace sag {

    Vector::Vector(Vector const &v) {
        x = v.x;
        y = v.y;
    }

    Vector::operator std::string() {
        std::ostringstream oss;

        oss << "Vector [";
        oss << x;
        oss << ", ";
        oss << y;
        oss << "]";

        return oss.str();
    }
    
    /////////////////////////////////////////////
    
    Vector& Vector::add(number x, number y) {
        this->x += x;
        this->y += y;
        
        return *this;
    }
    
    Vector& Vector::randomize(Bounds &b) {
        x = Random::get().inRange(b.xmin, b.xmax);
        y = Random::get().inRange(b.ymin, b.ymax);
        
        return *this;
    }

}