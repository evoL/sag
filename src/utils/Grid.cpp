#include "Grid.h"

namespace sag {
    Grid::Grid(int width, int height):
        size(width, height),
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
    
    Grid& Grid::add(float x, float y, double value) {
        int ix = (int) x;
        int iy = (int) y;
        
        // linear filtering
        float xfrac = x - ix;
        float yfrac = y - iy;
        float ixfrac = 1 - xfrac;
        float iyfrac = 1 - yfrac;
        
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
    
    Grid& Grid::addProjected(Vector<number>& v, Bounds<number>& bounds, double value) {
        Bounds<number>::Raw b = bounds.getRawBounds();
        
        float x = (v.x - b.xmin) / (b.xmax - b.xmin) * size.width;
        float y = (v.y - b.ymin) / (b.ymax - b.ymin) * size.height;
        
        return add(x, y, value);
    }
    
    std::vector<int> Grid::map() {
        // TODO: enable customization of the mapping process with lambdas
        
        // Pre-calculate things like maximum value
        calculate();
        
        int s = size.width * size.height;
        
        std::vector<int> result;
        result.resize(s);
        
        double avgCache = 8 * avgValue;
        
        for (int i = s-1; i>=0; i--) {
            // TODO: result[i] = lambda(values[i]);
//            result[i] = (int)(values[i] / maxValue * 255);
//            result[i] = (values[i] > 255) ? 255 : (int)(values[i]);
//            result[i] = (values[i] > 0) ? 255 : 0;
            result[i] = (values[i] > avgCache) ? 255 : (int)(values[i] / avgCache * 255);
        }
        
        return result;
    }
    
    int Grid::index(int x, int y) {
        return y * size.width + x;
     }
    
    void Grid::calculate() {
        if (calculated) return;
        
        int s = size.width * size.height;
        int filledPixels = s;
        
        double sum = 0;
        for (int i = s - 1; i >= 0; i--) {
            if (maxValue < values[i]) maxValue = values[i];
            
            sum += values[i];
            if (values[i] == 0) filledPixels--;
        }
        avgValue = sum / filledPixels;
        
        calculated = true;
    }
    
    
}
