#include "rendering/PixbufRenderer.h"

#include <iostream>

namespace sag {
    void PixbufRenderer::render() {
        if (particleCount < 0) throw "Uninitialized particle count";
        
        while (!queue.empty()) {
            Vector<number> p = queue.front();
            queue.pop();
            
            grid.addProjected(p, bounds);
        }

        img.drawGrid(grid);
    }
}
