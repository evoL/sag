#include "rendering/Renderer.h"
#include <chrono>
#include <thread>

namespace sag {
    void Renderer::enqueueParticle(const Particle& p) {
		queue.push(p);
	}
    
    void Renderer::setBounds(Bounds<number>& b) {
        bounds = b;
    }

    void Renderer::setParticleCount(int pc) {
    	particleCount = pc;
    }
    
    void Renderer::wait() {
    	// TODO: Use std::condition_variable
		while (receiving) std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
    
    void Renderer::finishReceiving() {
		if (expectParticles) {
			expectParticles = false;
			receivingThread.join();
			receiving = false;
		}
	}
    
    void Renderer::startReceiving() {
		if (!expectParticles) {
			expectParticles = true;
			receiving = true;
			receivingThread = std::thread(&Renderer::receiveParticles, this);
		}
	}
	
	void Renderer::receiveParticles() {
		Particle p;
		bool got;
		while (expectParticles || !queue.empty()) {
			got = queue.tryPop(p);
			if (got) {
				receivingMutex.lock();
				processParticle(p);
				receivingMutex.unlock();
			}
		}
	}
}
