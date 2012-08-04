#include "utils/Random.h"

#include <ctime>
#include "utils/types.h"

namespace sag {
    template <typename T>
    Random<T>::Random() {
        engine.seed(time(NULL));
    }

    template <typename T>
    Random<T>& Random<T>::get() {
        static Random<T> instance;
        return instance;
    }

    template <typename T>
    T Random<T>::inRange(T from, T to) {
        std::uniform_real_distribution<T> u(from, to);
        return u(engine);
    }

    Random<int>& Random<int>::get() {
        static Random<int> instance;
        return instance;
    }

    int Random<int>::inRange(int from, int to) {
        std::uniform_int_distribution<int> u(from, to);
        return u(engine);
    }

    ///////// BECAUSE OF LINKER ERRORS

    template Random<number>& Random<number>::get();
    template number Random<number>::inRange(number from, number to);
}
