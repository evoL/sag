#include "rendering/Renderer.h"

#if defined(HAS_BOOST) && THREAD_NAMESPACE == boost
#  include <boost/chrono.hpp>
#else
#  include <chrono>
#endif

namespace sag {
	void Renderer::enqueueParticle(const Particle& p) {
		queue.push(p);
	}
    
    void Renderer::setBounds(Bounds<number>& b) {
        bounds = b;
    }
    
    void Renderer::wait() {
    	if (receiving) {
			THREAD_NAMESPACE::mutex waitingMutex;
			THREAD_NAMESPACE::unique_lock<THREAD_NAMESPACE::mutex> waitingLock(waitingMutex);
			waitingCV.wait(waitingLock);
    	}

	}
    
    void Renderer::abort() {
        receiving = false;
        expectParticles = false;
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
			if (receivingThread.joinable()) receivingThread.join();
			receivingThread = THREAD_NAMESPACE::thread(&Renderer::receiveParticles, this);
		}
	}
	
	void Renderer::receiveParticles() {
		Particle p;
		while (receiving && (expectParticles || !queue.empty())) {
			if (queue.tryPop(p)) {
				receivingMutex.lock();
				processParticle(p);
				receivedParticleCount++;
				receivingMutex.unlock();
			} else {
				THREAD_NAMESPACE::this_thread::sleep_for(THREAD_NAMESPACE::chrono::milliseconds(1));
			}
		}
	}
}
