#ifndef SAG_GRID_H
#define SAG_GRID_H

#include <vector>
#include "utils/types.h"
#include "utils/Vector.h"
#include "utils/Bounds.h"

namespace sag {
    class Grid {
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
        Dimensions size;

        Grid(int width, int height);
        ~Grid();
        
        Grid& add(int x, int y, double value=1);
        Grid& add(float x, float y, double value=1);
        
        Grid& addProjected(Vector<number>& v, Bounds<number>& bounds, double value=1);
        
        std::vector<int> map();
        
    private:
        double *values;
        
        bool calculated;
        double maxValue;
        double avgValue;
        
        inline int index(int x, int y);
        void calculate();
    };
}

#endif