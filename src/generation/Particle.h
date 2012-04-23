#ifndef SAG_PARTICLE_H
#define SAG_PARTICLE_H

#include <string>

#include "../utils/Vector.h"

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
        Particle(float x, float y): position(x,y) {}

        ~Particle() {} ///< Destructor.

        operator std::string(); ///< String conversion operator.
    };

}

#endif