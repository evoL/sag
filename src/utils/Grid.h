#ifndef SAG_GRID_H
#define SAG_GRID_H

#include <vector>
#include "utils/Bounds.h"

namespace sag {
    class Grid {
    public:
        Bounds<int> size;

        Grid(int width, int height);
        ~Grid();
        
//        Grid& add(int x, int y);
//        Grid& add(double x, double y);
        Grid& add(int x, int y, double value);
        Grid& add(double x, double y, double value);
        
        std::vector<int> map();
        
    private:
        double *values;
        
        bool calculated;
        double maxValue;
        
        inline int index(int x, int y);
        void calculate();
    };
}

#endif