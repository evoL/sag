#include "rendering/PixbufRenderer.h"

#include <chrono>
#include <thread>

namespace sag {
    void PixbufRenderer::render() {
        if (particleCount < 0) throw "Uninitialized particle count";
        
        int i = particleCount;
        while (i >= 0) {
            if (queue.empty()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                continue;
            }
            
            Particle p = queue.front();
            queue.pop();
            
            grid.add(p.position.x, p.position.y);
            
            --i;
        }

        img.drawGrid(grid);
    }
}