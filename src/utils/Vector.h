#ifndef SAG_VECTOR_H
#define SAG_VECTOR_H

#include <string>

namespace sag {

    /**
     * @brief Represents a single vector.
     *
     * @author Rafał Hirsz
     */
    template <typename T>
    class Vector {
    public:
        T x, y;

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
        Vector(T x, T y): x(x), y(y) {}

        /**
         * @brief Copy constructor
         */
        Vector(Vector<T> const &v): x(v.x), y(v.y) {}

        ~Vector() {} ///< Destructor.

        /**
         * @brief Assignment operator.
         */
        Vector<T>& operator=(const Vector<T>& v) {
            x = v.x;
            y = v.y;
            
            return *this;
        }
        
        operator std::string(); ///< String conversion operator.
        
        ///////////////////////////////////////////// OPERATIONS
        
        /**
         * @brief Adds a vector described by passed coordinates to current vector.
         *
         * @param x The horizontal coordinate.
         * @param y The vertical coordinate.
         */
        Vector<T>& add(T x, T y);
    };

}

#endif