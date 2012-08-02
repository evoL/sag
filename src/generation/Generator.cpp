#include "Generator.h"

namespace sag {
    void Generator::setFormula(Formula &f) {
        formula = &f;
    }
    
    const std::vector<Particle>& Generator::getParticles() const {
        return particles;
    }
    
    void Generator::reset() {
        initialized = false;
    }
    
    void Generator::initialize() {
        if (initialized) return;
        
        // Prepare the formula
        formula->prepare();
        
        // Precalculate some things
        precalc();
        
        // Prepare the particles
        particles.resize(particleCount);
        for (auto p = particles.begin(); p < particles.end(); p++) {
            p->position = bounds.getRandomVector();
        }
        
        initialized = true;
    }
    
    void Generator::precalc() {
        // Get the initial vector
        Bounds<number> b(-1, 1, -1, 1);
        Vector<number> v = b.getRandomVector();
        
        for (int i = PRECALC_ITERATIONS; i >= 0; --i) {
            // Calculate the bounds of the attractor
            if (bounds.xmin > v.x) bounds.xmin = v.x;
            if (bounds.xmax < v.x) bounds.xmax = v.x;
            if (bounds.ymin > v.y) bounds.ymin = v.y;
            if (bounds.ymax < v.y) bounds.ymax = v.y;
            
            v = formula->step(v);
        }
    }
}