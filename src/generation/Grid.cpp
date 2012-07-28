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
        if (!size.contains((int)x, (int)y)) return *this;
        
        // linear filtering
        
        double xfrac = x - (int)x;
        double yfrac = y - (int)y;
        double ixfrac = 1 - xfrac;
        double iyfrac = 1 - yfrac;
        
        int idx = index((int)x, (int)y);
        
        values[idx]             += ixfrac * iyfrac * value;
        values[idx+1]           +=  xfrac * iyfrac * value;
        values[idx+size.xmax]   += ixfrac *  yfrac * value;
        values[idx+size.xmax+1] +=  xfrac *  yfrac * value;
        
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