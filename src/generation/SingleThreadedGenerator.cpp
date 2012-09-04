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
        sendParticle(initials[0]);
        
        // The rest are random
		for (int i=1; i<particleCount; i++) {
			initials[i] = bounds.getRandomVector(if3D);
			sendParticle(initials[i]);
		}
		
		if (thread.joinable()) thread.join();
		thread = std::thread(&SingleThreadedGenerator::iterate, this, initials);
	}
	
	void SingleThreadedGenerator::iterate(std::vector<Particle> v) {
		int i = 1;
		int offset;
		if (TTL > 0) offset = TTL / particleCount;
        while (running && ((iterations == UNLIMITED_ITERATIONS) || ((i++) < iterations))) {
        	for (int j=0; j < particleCount; j++) {
        		if (j != 0 && TTL > 0 && i % TTL == j*offset)
        			v[j].moveTo(bounds.getRandomVector(if3D));
        		else
        			v[j].moveTo( formula->step(v[j].getPosition()) );
				sendParticle(v[j]);
				if (!running) break;
			}
        }
        
        running = false;
        renderer->finishReceiving();
	}
}
