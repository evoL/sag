#ifndef SAG_VECTOR_H
#define SAG_VECTOR_H

#include <string>
#include "types.h"
#include "Bounds.h"

namespace sag {

    /**
     * @brief Represents a single vector.
     *
     * @author Rafał Hirsz
     */
    class Vector {
    public:
        number x, y;

        /**
         * @brief Default constructor.
         */
        Vector(): x(0), y(0) {}

        /**
         * @brief Constructs a vector using specified coordinates.
         *
         * @param x The horizontal coordinate.
         * @param y The vertical coordinate.
         */
        Vector(number x, number y): x(x), y(y) {}

        /**
         * @brief Copy constructor
         */
        Vector(Vector const &v);

        ~Vector() {} ///< Destructor.

        operator std::string(); ///< String conversion operator.
        
        ///////////////////////////////////////////// OPERATIONS
        
        /**
         * @brief Adds a vector described by passed coordinates to current vector.
         *
         * @param x The horizontal coordinate.
         * @param y The vertical coordinate.
         */
        Vector& add(number x, number y);
        
        /**
         * @brief Randomizes the vector in specified bounds.
         *
         * @param b Bounds.
         */
        Vector& randomize(Bounds &b);
    };

}

#endif