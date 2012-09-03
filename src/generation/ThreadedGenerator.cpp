#ifndef NO_THREADED_GENERATOR

#include "generation/ThreadedGenerator.h"
#include <vector>
#include "utils/Particle.h"

namespace sag {
	ThreadedGenerator::~ThreadedGenerator() {
		threadController.join();
	}

	void ThreadedGenerator::run() {
        running = true;
		renderer->startReceiving();
		
		threads.clear();
		
		std::vector<Particle> initials;
		
		threads.resize(particleCount);
		initials.resize(particleCount);

        // The initial point is always the starting point
        initials[0] = formula->getStartPoint();
        sendParticle(initials[0]);
		threads[0] = std::thread(&ThreadedGenerator::iterate, this, initials[0]);
        
        // The rest are random
		for (int i=1; i<particleCount; i++) {
			initials[i] = bounds.getRandomVector(if3D);
			sendParticle(initials[i]);
			threads[i] = std::thread(&ThreadedGenerator::iterate, this, initials[i]);
		}
		
		threadController = std::thread(&ThreadedGenerator::controlThreads, this);
		
	}
	
	void ThreadedGenerator::iterate(Particle &p) {
		int i = iterations;
        while (running && ((iterations == UNLIMITED_ITERATIONS) || (i > 1))) {
            p.moveTo( formula->step(p.getPosition()) );
            sendParticle(p);
            --i;
        }
	}
	
	void ThreadedGenerator::controlThreads() {
		for (auto &t : threads) {
			t.join();
		}
		running = false;
		renderer->finishReceiving();
	}
}

#endif
