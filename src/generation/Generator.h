#ifndef SAG_GENERATOR_H
#define SAG_GENERATOR_H

#include <vector>
#include "formulas/Formula.h"
#include "Particle.h"

namespace sag {
    class Generator {
    protected:        
        bool initialized;
        std::vector<Particle> particles;
        Formula *formula;
        Bounds<number> bounds;
        
        void initialize();
    public:
        Generator(): initialized(false), particleCount(1) {}
        
        unsigned int particleCount;
        
        void setFormula(Formula& f);
        void setBounds(Bounds<number>& b);
        
        const std::vector<Particle>& getParticles() const;
        
        virtual void step() = 0; 
        void reset();
    };
}

#endif