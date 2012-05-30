#include "Random.h"

namespace sag {
    Random::Random() {}
    
    Random& Random::get() {
        static Random instance;
        return instance;
    }
    
    number Random::inRange(number from, number to) {
        std::uniform_real_distribution<number> u(from, to);
        return u(engine);
    }
}