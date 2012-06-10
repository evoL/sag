#ifndef SAG_RANDOM_H
#define SAG_RANDOM_H

#include <random>

namespace sag {
    /**
     * @brief Provides a global random number generator.
     */
    template <typename T>
    class Random {
        Random();
        Random(const Random&);
        Random& operator=(const Random&);
        
        std::default_random_engine engine;
    public:
        /**
         * @brief Returns an instance of the generator
         */
        static Random& get();
        
        /**
         * @brief Returns a random number within the provided range.
         *
         * @param from The beginning of the range.
         * @param to The end of the range.
         */
        T inRange(T from, T to);
    };
    
    template <>
    class Random <int> {
        std::default_random_engine engine;
    public:
        /**
         * @brief Returns a random integer within the provided range.
         *
         * @param from The beginning of the range.
         * @param to The end of the range.
         */
        int inRange(int from, int to);
    };
}

#endif