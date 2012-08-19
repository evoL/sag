#include "rendering/PixbufRenderer.h"

#include <vector>
#include "utils/Color.h"

namespace sag {
    bool PixbufRenderer::receiveParticle(const Particle& p) {
        if (!Renderer::receiveParticle(p)) return false;
        
        positionGrid.addProjected(p.getPosition(), bounds);
        velocityGrid.addProjected(p.getPosition(), bounds, p.getVelocity().length());
        return true;
    }
    
    void PixbufRenderer::render() {
        std::vector<int> shapeData = positionGrid.map();
        std::vector<int> colorData = velocityGrid.map( [](double val, const Grid::Info& info) -> int {
            return 255 - (val - info.minValue) / (info.maxValue - info.minValue) * 255;
        } );
        
        
        // Merge the data into one vector
        std::vector<int> data(img.getWidth()*img.getHeight()*3);
        
        int idx = 0;
        int imgidx = 0;
        for (auto it = shapeData.begin(); it < shapeData.end(); it++) {
            Color c = Color::fromHSL(0.08, (double)(colorData[idx])/255, (double)(*it)/255);
            
            data[imgidx]   = c.r;
            data[imgidx+1] = c.g;
            data[imgidx+2] = c.b;
            
//            data[imgidx] = colorData[idx];
//            data[imgidx+1] = colorData[idx];
//            data[imgidx+2] = colorData[idx];
            
            idx++;
            imgidx += 3;
        }
        
        img.drawData(data);
        
        positionGrid.clear();
        velocityGrid.clear();
    }
}
