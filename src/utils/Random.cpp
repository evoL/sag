#include "utils/Random.h"
#include "utils/types.h"

namespace sag {
    template <typename T>
    Random<T>::Random() {
        std::random_device device;
        engine.seed(device());
    }

    template <typename T>
    Random<T>& Random<T>::getGlobal() {
        static Random<T> instance;
        return instance;
    }

    template <typename T>
    T Random<T>::inRange(T from, T to) {
        std::uniform_real_distribution<double> u(from, to);
        return u(engine);
    }
    
    template <typename T>
    T Random<T>::inRange(const Range<T>& range) {
        return inRange(range.min(), range.max());
    }
    
    template class Random<number>;
    template class Random<int>;
}
