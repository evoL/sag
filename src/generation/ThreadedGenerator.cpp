#include "generation/ThreadedGenerator.h"
#include <vector>
#include "utils/Particle.h"

namespace sag {
	void ThreadedGenerator::run() {
		renderer->startReceiving();
		
		threads.clear();
		
		std::vector<Particle> initials;
		
		threads.resize(particleCount);
		initials.resize(particleCount);

        // The initial point is always the starting point
        initials[0] = formula->getStartPoint();
        sendParticle(initials[0]);
		threads.push_back(std::thread(&ThreadedGenerator::iterate, this, initials[0]));
        
        // The rest are random
		for (int i=1; i<particleCount; i++) {
			initials[i] = bounds.getRandomVector(if3D);
			sendParticle(initials[i]);
			threads.push_back(std::thread(&ThreadedGenerator::iterate, this, initials[i]));
		}
		
		threadController = std::thread(&ThreadedGenerator::controlThreads, this);
		
	}
	
	void ThreadedGenerator::iterate(Particle &p) {
		int i = iterations;
        while ((!aborting) && ((iterations == UNLIMITED_ITERATIONS) || (i >= 0))) {
            for (int j=0; j < particleCount; j++) {
				p.moveTo( formula->step(p.getPosition()) );
				sendParticle(p);
				if (aborting) break;
			}
            --i;
        }
	}
	
	void ThreadedGenerator::controlThreads() {
		for (auto &t : threads) {
			t.join();
		}
		renderer->finishReceiving();
		aborting = false;
	}
}
