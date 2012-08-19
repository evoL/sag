#include "rendering/PixbufRenderer.h"

#include <vector>

namespace sag {
    bool PixbufRenderer::receiveParticle(const Particle& p) {
        if (!Renderer::receiveParticle(p)) return false;
        
        positionGrid.addProjected(p.getPosition(), bounds);
        velocityGrid.addProjected(p.getPosition(), bounds, p.getVelocity().length());
        return true;
    }
    
    void PixbufRenderer::render() {
        std::vector<int> shapeData = positionGrid.map();
        
        // Merge the data into one vector
        std::vector<int> data(img.getWidth()*img.getHeight()*3);
        
        int idx = 0;
        for (auto it = shapeData.begin(); it < shapeData.end(); it++) {
            data[idx++] = *it;
            data[idx++] = *it;
            data[idx++] = *it;
        }
        
        img.drawData(data);
        positionGrid.clear();
    }
}
