#include "utils/Particle.h"

namespace sag {
    Particle& Particle::moveTo(Vector<number> pos) {
        acceleration = (pos - position) - velocity;
        velocity = pos - position;
        position = pos;
        
        return *this;
    }
}