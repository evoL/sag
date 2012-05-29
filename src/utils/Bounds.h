#ifndef SAG_BOUNDS_H
#define SAG_BOUNDS_H

#include "Vector.h"
#include "types.h"

namespace sag {
    class Bounds {
    public:
        number xmin, xmax, ymin, ymax;
        
        Bounds(number xmin, number xmax, number ymin, number ymax): xmin(xmin), xmax(xmax), ymin(ymin), ymax(ymax) {}
        
        /**
         * @brief Checks whether the bounds contain a point specified by the arguments.
         *
         * @param x The horizontal coordinate of the point.
         * @param y The vertical coordinate of the point.
         */
        bool contains(number x, number y);
        
        /**
         * @brief Checks whether the bounds contain a point specified by a Vector.
         *
         * @param v A Vector representing the point.
         */
        bool contains(Vector v);
    };
}

#endif