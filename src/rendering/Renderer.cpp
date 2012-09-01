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
    	if (receiving) {
			std::mutex waitingMutex;
			std::unique_lock<std::mutex> waitingLock(waitingMutex);
			waitingCV.wait(waitingLock);
    	}

	}
    
    void Renderer::finishReceiving() {
		if (expectParticles) {
			expectParticles = false;
			receivingThread.join();
		}
		waitingCV.notify_one();
		receiving = false;
	}
    
    void Renderer::startReceiving() {
		if (!expectParticles) {
			expectParticles = true;
			receiving = true;
			receivedParticleCount = 0;
			receivingThread = std::thread(&Renderer::receiveParticles, this);
		}
	}
	
	void Renderer::receiveParticles() {
		Particle p;
		while (expectParticles || !queue.empty()) {
			if (queue.tryPop(p)) {
				receivingMutex.lock();
				processParticle(p);
				receivedParticleCount++;
				receivingMutex.unlock();
			} else {
				std::this_thread::sleep_for(std::chrono::milliseconds(10));
			}
		}
	}
}
