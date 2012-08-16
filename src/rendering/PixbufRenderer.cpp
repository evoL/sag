#include "rendering/PixbufRenderer.h"

#include <iostream>

namespace sag {
    bool PixbufRenderer::receiveParticle(Vector<number>& p) {
        if (!Renderer::receiveParticle(p)) return false;
        
        grid.addProjected(p, bounds);
        return true;
    }
    
    void PixbufRenderer::render() {
        img.drawGrid(grid);
    }
}
