#include "Grid.h"

namespace sag {
    Grid::Grid(int width, int height):
        size(0, width, 0, height),
        calculated(false),
        maxValue(0)
    {
        values = new double[width*height];
    }
    
    Grid::~Grid() {
        delete[] values;
    }
    
    Grid& Grid::add(int x, int y, double value) {
        if (!size.contains(x, y)) return *this;
        
        values[index(x,y)] += value;
        
        calculated = false;
        return *this;
    }
    
    Grid& Grid::add(double x, double y, double value) {
        int ix = (int) x;
        int iy = (int) y;
        
        // linear filtering
        double xfrac = x - ix;
        double yfrac = y - iy;
        double ixfrac = 1 - xfrac;
        double iyfrac = 1 - yfrac;
        
        if (size.contains(ix, iy))
            values[index(ix, iy)]     += ixfrac * iyfrac * value;
        if (size.contains(ix+1, iy))
            values[index(ix+1, iy)]   +=  xfrac * iyfrac * value;
        if (size.contains(ix, iy+1))
            values[index(ix, iy+1)]   += ixfrac *  yfrac * value;
        if (size.contains(ix+1, iy+1))
            values[index(ix+1, iy+1)] +=  xfrac *  yfrac * value;
        
        calculated = false;
        return *this;
    }
    
    std::vector<int> Grid::map() {
        // TODO: enable customization of the mapping process with lambdas
        
        // Pre-calculate things like maximum value
        calculate();
        
        int s = size.xmax * size.ymax;
        
        std::vector<int> result;
        result.resize(s);
        
        for (int i = s-1; i>=0; i--) {
            // TODO: result[i] = lambda(values[i]);
            result[i] = (int)(values[i] / maxValue * 255);
//            result[i] = (values[i] > 255) ? 255 : (int)(values[i]);
        }
        
        return result;
    }
    
    int Grid::index(int x, int y) {
        return y * size.xmax + x;
     }
    
    void Grid::calculate() {
        if (calculated) return;
        
        int s = size.xmax * size.ymax;
        for (int i = s - 1; i >= 0; i--) {
            if (maxValue < values[i]) maxValue = values[i];
        }
        
        calculated = true;
    }
    
    
}