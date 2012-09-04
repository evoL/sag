#ifndef SAG_RANDOM_H
#define SAG_RANDOM_H

#include <random>
#include "utils/Range.h"

namespace sag {
    /**
     * @brief Provides a global random number generator.
     */
    template <typename T>
    class Random {
        std::default_random_engine engine;
    public:
        /**
         * @brief Default constructor.
         */
        Random();
        
        /**
         * @brief Returns a global instance of the generator.
         *
         * @returns Global instance of the generator
         */
        static Random& getGlobal();

        /**
         * @brief Returns a random number within the provided range.
         *
         * @param from The beginning of the range.
         * @param to The end of the range.
         *
         * @returns Random number
         */
        T inRange(T from, T to);
        
        /**
         * @brief Returns a random number within the provided range.
         *
         * @param range The Range.
         *
         * @returns Random number
         */
        T inRange(const Range<T>& range);
    };
}

#endif
