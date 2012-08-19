#include "rendering/PixbufRenderer.h"

#include <iostream>

namespace sag {
    bool PixbufRenderer::receiveParticle(const Particle& p) {
        if (!Renderer::receiveParticle(p)) return false;
        
        positionGrid.addProjected(p.getPosition(), bounds);
        velocityGrid.addProjected(p.getPosition(), bounds, p.getVelocity().length());
        return true;
    }
    
    void PixbufRenderer::render() {
        img.drawGrid(positionGrid);
        positionGrid.clear();
    }
}
