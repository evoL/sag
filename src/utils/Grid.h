#ifndef SAG_GRID_H
#define SAG_GRID_H

#include <vector>
#include <functional>
#include <limits>
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
        struct Info {
            double minValue, maxValue, avgValue;
            Info(): minValue(std::numeric_limits<double>::max()),
            		maxValue(std::numeric_limits<double>::min()),
            		avgValue(0) {}
        };
        
        Dimensions size;

        Grid(int width, int height);
        ~Grid();
        
        Grid& clear();
        
        Grid& resize(int w, int h);
        
        Grid& add(int x, int y, double value=1);
        Grid& add(float x, float y, double value=1);
        
        Grid& addProjected(const Vector<number>& v, const Bounds<number>& bounds, double value=1);
        
        std::vector<int> map(std::function<int(double, const Info&)> fn);
        std::vector<int> map();
        
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
