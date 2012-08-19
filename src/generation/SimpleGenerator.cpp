#include "generation/SimpleGenerator.h"
#include <vector>
#include "utils/Particle.h"
#include "utils/types.h"

namespace sag {
	void SimpleGenerator::run() {
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
        
        int i = iterations;
        while ( (iterations == UNLIMITED_ITERATIONS) || (i >= 0)) {
            for (int j=0; j < particleCount; j++) {
				initials[j].moveTo( formula->step(initials[j].getPosition()) );
				sendParticle(initials[j]);
			}
            --i;
        }
	}
}
