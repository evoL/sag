#include "rendering/PixbufRenderer.h"

#include <vector>
#include "utils/Color.h"

namespace sag {
	void PixbufRenderer::processParticle(Particle& p) {
		positionGrid.addProjected(p.getPosition(), bounds);
		velocityGrid.addProjected(p.getPosition(), bounds, p.getVelocity().length());
        accelerationGrid.addProjected(p.getPosition(), bounds, p.getAcceleration().length());
	}
	
	void PixbufRenderer::render() {
		receivingMutex.lock();
		std::vector<int> shapeData = positionGrid.map();
        std::vector<int> lightData = velocityGrid.map( [](double val, const Grid::Info& info) -> int {
            return 255 - (val - info.minValue) / (info.maxValue - info.minValue) * 255;
        } );
        std::vector<int> colorData = accelerationGrid.map();
		receivingMutex.unlock();
        
        // Merge the data into one vector
        std::vector<int> data(img.getWidth()*img.getHeight()*3);
        
        int idx = 0;
        int imgidx = 0;
        for (auto it = shapeData.begin(); it < shapeData.end(); it++) {
            Color c = color;
            double hue = c.hue() + (colorData[idx]/255.0) * colorShiftLevel;
            c.hue((hue > 1.0) ? (hue - 1) : hue);
            c.saturation(c.saturation() * ((lightData[idx])/255.0));
            c.lightness((*it)/255.0);
            
            data[imgidx]   = c.red();
            data[imgidx+1] = c.green();
            data[imgidx+2] = c.blue();
            
//            data[imgidx] = colorData[idx];
//            data[imgidx+1] = colorData[idx];
//            data[imgidx+2] = colorData[idx];
            
            idx++;
            imgidx += 3;
        }
        
        img.drawData(data);
    }
    
    void PixbufRenderer::clear() {
        positionGrid.clear();
        velocityGrid.clear();
        accelerationGrid.clear();
        img.clear();
		queue.clear();
    }
}
