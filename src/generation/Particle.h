#ifndef SAG_PARTICLE_H
#define SAG_PARTICLE_H

#include <string>

#include "../utils/types.h"
#include "../utils/Vector.h"
#include "../utils/Bounds.h"

namespace sag {

    /**
     * @brief Represents a particle.
     *
     * @author Rafał Hirsz
     */
    class Particle {
    public:
        Vector position;

        /**
         * @brief Constructs a particle at the position specified by passed coordinates.
         *
         * @param x The horizontal coordinate.
         * @param y The vertical coordinate.
         */
        Particle(number x, number y): position(x,y) {}

        ~Particle() {} ///< Destructor.

        operator std::string(); ///< String conversion operator.
        
        /**
         * @brief Creates a particle fitting in the specified bounds. The position is randomized.
         *
         * @param bounds The bounds the particle must fit.
         */
        static Particle getRandom(Bounds &b);
    };

}

#endif