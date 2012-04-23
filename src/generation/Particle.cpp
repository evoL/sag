#include "Particle.h"

#include <sstream>

namespace sag {

    Particle::operator std::string() {
        std::ostringstream oss;

        oss << "Particle (position: ";
        oss << (std::string) position;
        oss << ")";

        return oss.str();
    }

}