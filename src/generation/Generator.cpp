#include "generation/Generator.h"

#include <vector>
#include "utils/Vector.h"

namespace sag {
	Generator::Generator(Formula& f, Renderer& r, int iter, bool if3D):
        formula(&f),
        particleCount(1),
        if3D(if3D),
        running(false),
        iterations(iter),
        TTL(-1),
        renderer(&r)
    {
        formula->prepare();
        
		setBounds();
        
		renderer->setBounds(bounds);
	}
	
    void Generator::reset() {
        formula->randomize();
        setBounds();
        renderer->setBounds(bounds);
    }
    
    void Generator::abort() {
		running = false;
	}

	void Generator::sendParticle(const Particle& p) {
		renderer->enqueueParticle(p);
	}

	void Generator::setBounds() {
		std::vector<Vector<number>> particles;

		particles.resize(WARMUP_ITERATIONS);
        particles[0] = formula->getStartPoint();

		for (int i=1; i<WARMUP_ITERATIONS; i++)
			particles[i] = formula->step(particles[i-1]);

		bounds = Bounds<number>(particles);
	}
    
    void Generator::setParticleCount(int pc) {
        particleCount = pc;
    }

    void Generator::setTTL(int TTL) {
    	this->TTL = TTL;
    }
}
