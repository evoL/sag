#ifndef SAG_BOUNDS_H
#define SAG_BOUNDS_H

#include "types.h"

namespace sag {
    class Bounds {
    public:
        number xmin, xmax, ymin, ymax;
        
        Bounds(): xmin(0), xmax(0), ymin(0), ymax(0) {}
        
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
        //bool contains(sag::Vector v);
    };
}

#endif