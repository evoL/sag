#include "rendering/Renderer.h"

namespace sag {
    bool Renderer::receiveParticle(const Particle& p) {
        if (particleCount < 0) throw "Uninitialized particle count";
        return true;
    }
    
    void Renderer::setBounds(Bounds<number>& b) {
        bounds = b;
    }

    void Renderer::setParticleCount(int pc) {
    	particleCount = pc;
    }
}
