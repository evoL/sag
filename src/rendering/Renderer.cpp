#include "rendering/Renderer.h"

namespace sag {
    bool Renderer::enqueueParticle(Particle &p) {
        if (particleCount < 0) throw "Uninitialized particle count";
        if (queue.size() > particleCount * QUEUE_SIZE_FACTOR) return false;
        
        queue.push(p);
        return true;
    }
    
    void Renderer::setBounds(Bounds<number>& b) {
        bounds = &b;
    }
    
    void Renderer::setParticleCount(int count) {
        particleCount = count;
    }
}
