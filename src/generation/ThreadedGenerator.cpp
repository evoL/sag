#ifndef NO_THREADED_GENERATOR

#include "generation/ThreadedGenerator.h"
#include <vector>
#include "utils/Particle.h"

namespace sag {
	ThreadedGenerator::~ThreadedGenerator() {
		if (threadController.joinable()) threadController.join();
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
		threads[0] = std::thread(&ThreadedGenerator::iterate, this, initials[0], 0);
        
        // The rest are random
		for (int i=1; i<particleCount; i++) {
			initials[i] = bounds.getRandomVector(if3D);
			threads[i] = std::thread(&ThreadedGenerator::iterate, this, initials[i], i);
		}
		
		if (threadController.joinable()) threadController.join();
		threadController = std::thread(&ThreadedGenerator::controlThreads, this);
		
	}
	
	void ThreadedGenerator::iterate(Particle &p, int n) {
		int i = 1;
		int offset = 0;
		if (ttl > 0) offset = ttl / particleCount * n;
        while (running && ((iterations == UNLIMITED_ITERATIONS) || (i < iterations))) {
            if (n != 0 && ttl > 0 && i % ttl == offset) {
            	p = bounds.getRandomVector(if3D);
            }
            p.moveTo( formula->step(p.getPosition()));
            sendParticle(p);
            i++;
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
