#include "rendering/Renderer.h"

namespace sag {
    void Renderer::enqueueParticle(Particle &p) {
        if (particleCount < 0) throw "Uninitialized particle count";
        if (queue.size() > particleCount * QUEUE_SIZE_FACTOR) return;
        
        queue.push(p);
    }
}