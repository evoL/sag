#ifndef SAG_GRID_H
#define SAG_GRID_H

#include <vector>

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