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
        std::uniform_real_distribution<T> u(from, to);
        return u(engine);
    }
    
    template <typename T>
    T Random<T>::inRange(const Range<T>& range) {
        return inRange(range.min(), range.max());
    }
    
    Random<int>::Random() {
        std::random_device device;
        engine.seed(device());
    }

    Random<int>& Random<int>::getGlobal() {
        static Random<int> instance;
        return instance;
    }

    int Random<int>::inRange(int from, int to) {
        std::uniform_int_distribution<int> u(from, to);
        return u(engine);
    }
    
    int Random<int>::inRange(const Range<int>& range) {
        return inRange(range.min(), range.max());
    }

    ///////// BECAUSE OF LINKER ERRORS

    template Random<number>& Random<number>::getGlobal();
    template number Random<number>::inRange(number from, number to);
    template number Random<number>::inRange(const Range<number>& range);
}
