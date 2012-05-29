#include "Particle.h"

#include <sstream>
#include "../utils/utils.h"

namespace sag {

    Particle::operator std::string() {
        std::ostringstream oss;

        oss << "Particle (position: ";
        oss << (std::string) position;
        oss << ")";

        return oss.str();
    }
    
    Particle Particle::getRandom(Bounds &b) {
        return Particle( randRange(b.xmin, b.xmax), randRange(b.ymin, b.ymax) );
    }
}