#include "utils/Particle.h"

namespace sag {
    Particle& Particle::moveTo(Vector<number> pos) {
        velocity = pos - position;
        position = pos;
        
        return *this;
    }
}