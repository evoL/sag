#ifndef SAG_GRID_H
#define SAG_GRID_H

#include <vector>
#include <functional>
#include <limits>
#include "utils/types.h"
#include "utils/Vector.h"
#include "utils/Bounds.h"

namespace sag {
    /**
     * @brief Accumulates pixels on a grid
     */
	class Grid {
        /**
         * Represents dimensions
         */
		class Dimensions {
        public:
            int width, height;
            
            Dimensions(): width(0), height(0) {}
            Dimensions(int w, int h): width(w), height(h) {}
            
            bool contains(int x, int y) {
                return (x >= 0) && (y >= 0) && (x < width) && (y < height);
            }
        };
    public:
		/**
		 * Represents some information about data in Grid.
		 */
        struct Info {
            double minValue, maxValue, avgValue;
            Info(): minValue(std::numeric_limits<double>::max()),
            		maxValue(std::numeric_limits<double>::min()),
            		avgValue(0) {}
        };
        
        Dimensions size;

        Grid(int width, int height);
        ~Grid();
        
        /**
         * @brief Clears grid
         *
         * @returns This grid
         */
        Grid& clear();
        
        /**
         * @brief Resizes grid to the specific dimesions
         *
         * @param w Width
         * @param h Height
         *
         * @returns This grid
         */
        Grid& resize(int w, int h);
        
        /**
         * @brief Adds given value to specific coordinates.
         *
         * @param x X-coordinate
         * @param y Y-coordinate
         * @param value (optional) Value to be added. By default set to 1.
         *
         * @returns This grid
         */
        Grid& add(int x, int y, double value=1);

        /**
		 * @brief Adds given value to specific coordinates (floating-point version).
		 *
		 * @param x X-coordinate
		 * @param y Y-coordinate
		 * @param value (optional) Value to be added. By default set to 1.
		 *
		 * @returns This grid
		 */
        Grid& add(float x, float y, double value=1);
        
        /**
         *  @brief Projects a vector in the specified boundaries to the grid
         *
         *  @param Vector
         *  @param Bounds
         *  @param value (optional) Value to be added. By default set to 1.
         *
         *  @returns This grid
         */
        Grid& addProjected(const Vector<number>& v, const Bounds<number>& bounds, double value=1);
        
        /**
         * @brief Maps the grid using given function
         *
         * @param fn Mapping function
         *
         * @returns Vector of integers scaled to the range from 0 to 255
         */
        std::vector<int> map(std::function<int(double, const Info&)> fn);

        /**
		 * @brief Maps the grid using default function
		 *
		 * @returns Vector of integers scaled to the range from 0 to 255
		 */
        std::vector<int> map();
        
        /**
         * @brief Returns some information about grid
         *
         * @return Some info
         */
        inline const Info& getInfo() const { return info; }
        
    private:
        double *values;
        
        bool calculated;
        Info info;
        
        inline int index(int x, int y);
        void calculate();
    };
}

#endif
