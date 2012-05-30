#include "Random.h"

#include <ctime>

namespace sag {
    Random::Random() {
        engine.seed(time(NULL));
    }
    
    Random& Random::get() {
        static Random instance;
        return instance;
    }
    
    number Random::inRange(number from, number to) {
        std::uniform_real_distribution<number> u(from, to);
        return u(engine);
    }
}