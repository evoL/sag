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
		while (expectParticles) std::this_thread::sleep_for(std::chrono::milliseconds(30));
	}
    
    void Renderer::finishReceiving() {
		if (expectParticles) {
			expectParticles = false;
			receivingThread.join();
		}
	}
    
    void Renderer::startReceiving() {
		if (!expectParticles) {
			expectParticles = true;
			receivingThread = std::thread(&Renderer::receiveParticles, this);
		}
	}
	
	void Renderer::receiveParticles() {
		Particle p;
		while (expectParticles) {
			queue.waitAndPop(p);
			receivingMutex.lock();
			processParticle(p);
			receivingMutex.unlock();
		}
	}
}
