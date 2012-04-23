#include "Vector.h"

#include <sstream>

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
    
    Vector& Vector::add(float x, float y) {
        this->x += x;
        this->y += y;
        
        return *this;
    }

}