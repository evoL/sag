#ifndef RENDERER_H
#define RENDERER_H

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include "utils/types.h"
#include "utils/Bounds.h"
#include "utils/Particle.h"
#include "utils/ConcurrentQueue.h"

namespace sag {
	class Renderer {
	public:
        Renderer(): particleCount(-1), expectParticles(false), receiving(false) {}
        virtual ~Renderer() {}
        
        void enqueueParticle(const Particle& p);
        
        void setBounds(Bounds<number>& b);

        void setParticleCount(int pc);
		
		void wait();
        void abort();
		
		void finishReceiving();

        void startReceiving();
		
		void receiveParticles();
		
        virtual void processParticle(Particle &p) = 0;
		virtual void clear() = 0;
        virtual void render() = 0;

        inline int getReceivedParticleCount() { return receivedParticleCount; }
    
	protected:
        Bounds<number> bounds;
		ConcurrentQueue<Particle> queue;
		std::thread receivingThread;
		mutable std::mutex receivingMutex;
        std::condition_variable waitingCV;
		int particleCount;
		volatile bool expectParticles;
		volatile bool receiving;
		volatile int receivedParticleCount;
	};
}

#endif
