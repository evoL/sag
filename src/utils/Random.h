#ifndef SAG_RANDOM_H
#define SAG_RANDOM_H

#include <random>
#include "types.h"

namespace sag {
    /**
     * @brief Provides a global random number generator.
     */
    class Random {
    public:
        /**
         * @brief Returns an instance of the generator
         */
        static Random& get();
        
        /**
         * @brief Returns a random number within the provided range.
         *
         * @param from The beginning of the range.
         * @param to Te end of the range.
         */
        number inRange(number from, number to);
    private:
        Random();
        Random(const Random&);
        Random& operator=(const Random&);
        
        std::default_random_engine engine;
    };
}

#endif