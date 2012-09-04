#include "generation/SimpleGenerator.h"
#include <vector>
#include "utils/Particle.h"

namespace sag {
	void SimpleGenerator::run() {
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
        
        int i = 1;
        int offset;
        if (ttl > 0) offset = ttl / particleCount;
        while (running && ((iterations == UNLIMITED_ITERATIONS) || ((i++) < iterations))) {
            for (int j=0; j < particleCount; j++) {
				if (j != 0 && ttl > 0 && i % ttl == j*offset)
					initials[j] = bounds.getRandomVector(if3D);
				else
					initials[j].moveTo( formula->step(initials[j].getPosition()) );
				sendParticle(initials[j]);
				if (!running) break;
			}
        }
        
        running = false;
        renderer->finishReceiving();
	}
}
