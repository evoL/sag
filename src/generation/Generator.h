#ifndef SAG_GENERATOR_H
#define SAG_GENERATOR_H

#include <vector>
#include "formulas/Formula.h"
#include "utils/Bounds.h"
#include "Particle.h"

namespace sag {
    class Generator {
    protected:        
        bool initialized;
        std::vector<Particle> particles;
        Formula *formula;
        Bounds<number> bounds;
        
        void initialize();
        
        /**
         * @brief Performs the "precalc" phase of generation.
         *
         * The "precalc" phase is needed to calculate the visible bounds of the
         * attractor.
         */
        void precalc();
        
    public:
        /**
         * @brief The iteration count used in the "precalc" phase of generation.
         */
        const int PRECALC_ITERATIONS = 5000;
        
        unsigned int particleCount;
        
        Generator(): initialized(false), bounds(1e32, -1e32, 1e32, -1e32), particleCount(1) {}
        
        void setFormula(Formula& f);
        
        const std::vector<Particle>& getParticles() const;
        
        virtual void step() = 0; 
        void reset();
    };
}

#endif