#ifndef SAG_BOUNDS_H
#define SAG_BOUNDS_H

#include "Vector.h"

namespace sag {
    template <typename T>
    class Bounds {
    public:
        T xmin, xmax, ymin, ymax;
        
        Bounds(): xmin(0), xmax(0), ymin(0), ymax(0) {}
        
        Bounds(T xmin, T xmax, T ymin, T ymax): xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax) {}
        
        template <typename U>
        Bounds<T>& operator=(const Bounds<U>& b);
        
        /**
         * @brief Checks whether the bounds contain a point specified by the arguments.
         *
         * @param x The horizontal coordinate of the point.
         * @param y The vertical coordinate of the point.
         */
        bool contains(T x, T y);
        
        /**
         * @brief Checks whether the bounds contain a point specified by a Vector.
         *
         * @param v A Vector representing the point.
         */
        bool contains(Vector<T> v);
        
        /**
         * @brief Creates a random Vector inside the bounds.
         */
        Vector<T> getRandomVector();
        
        /**
         * @brief Converts a vector into different bounds.
         *
         * @param v The vector to convert.
         * @param b Bounds to convert the vector to.
         */
        template <typename U>
        Vector<U> convert(Vector<T> &v, Bounds<U>& b);
    };
}

#endif