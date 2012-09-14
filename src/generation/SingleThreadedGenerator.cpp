#include "generation/SingleThreadedGenerator.h"


namespace sag {
    SingleThreadedGenerator::~SingleThreadedGenerator() {
    	if (thread.joinable()) thread.join();
    }
    
	void SingleThreadedGenerator::run() {
        running = true;
		renderer->startReceiving();
		
		std::vector<Particle> initials;
		initials.resize(particleCount);
        
        // The initial point is always the starting point
        initials[0] = formula->getStartPoint();
        
        // The rest are random
		for (int i=1; i<particleCount; i++) {
			initials[i] = bounds.getRandomVector(if3D);
		}
		
		if (thread.joinable()) thread.join();
		thread = THREAD_NAMESPACE::thread(&SingleThreadedGenerator::iterate, this, initials);
	}
	
	void SingleThreadedGenerator::iterate(std::vector<Particle> v) {
		int i = 0;
		int offset = 0;
		if (ttl > 0) offset = ttl / particleCount;
        while (running && ((iterations == UNLIMITED_ITERATIONS) || (i < iterations))) {
        	for (int j=0; j < particleCount; j++) {
        		if (j != 0 && ttl > 0 && i % ttl == j*offset) {
        			v[j] = bounds.getRandomVector(if3D);
        		}
                v[j].moveTo( formula->step(v[j].getPosition()) );
				sendParticle(v[j]);
				if (!running) break;
			}
            i++;
        }
        
        running = false;
        renderer->finishReceiving();
	}
}
