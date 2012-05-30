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
    
    Particle Particle::getRandom(Bounds &b) {
        return Particle( Random::get().inRange(b.xmin, b.xmax), Random::get().inRange(b.ymin, b.ymax) );
    }
}