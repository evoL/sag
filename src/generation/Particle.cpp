#include "Particle.h"

#include <sstream>
#include "utils/Random.h"

namespace sag {

    Particle::operator std::string() {
        std::ostringstream oss;

        oss << "Particle (position: ";
        oss << (std::string) position;
        oss << ")";

        return oss.str();
    }
    
    Particle Particle::getRandom(Bounds<number> &b) {
        return Particle(Random<number>::get().inRange(b.xmin, b.xmax), 
                        Random<number>::get().inRange(b.ymin, b.ymax));
    }
}