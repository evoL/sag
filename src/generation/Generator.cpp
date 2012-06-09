#include "Generator.h"

namespace sag {
    void Generator::setFormula(Formula &f) {
        formula = &f;
    }
    
    void Generator::setBounds(Bounds &b) {
        bounds = b;
    }
    
    const std::vector<Particle>& Generator::getParticles() const {
        return particles;
    }
    
    void Generator::reset() {
        initialized = false;
    }
    
    void Generator::initialize() {
        if (initialized) return;
        
        // Prepare the particles
        particles.resize(particleCount);
        for (auto p = particles.begin(); p < particles.end(); p++) {
            p->position.randomize(bounds);
        }
        
        // Prepare the formula
        formula->prepare();
        
        initialized = true;
    }
}