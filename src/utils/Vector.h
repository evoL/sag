#ifndef SAG_VECTOR_H
#define SAG_VECTOR_H

#include <string>

namespace sag {

    /**
     * @brief Represents a single vector.
     *
     * @author Rafał Hirsz
     */
    class Vector {
    public:
        float x, y;

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
        Vector(float x, float y): x(x), y(y) {}

        /**
         * @brief Copy constructor
         */
        Vector(Vector const &v);

        ~Vector() {} ///< Destructor.

        operator std::string(); ///< String conversion operator.
    };

}

#endif