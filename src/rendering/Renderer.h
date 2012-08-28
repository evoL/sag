#ifndef RENDERER_H
#define RENDERER_H

#include <queue>
#include <thread>
#include <mutex>
#include "utils/types.h"
#include "utils/Bounds.h"
#include "utils/Particle.h"
#include "utils/ConcurrentQueue.h"

namespace sag {
	class Renderer {
	public:
        Renderer(): particleCount(-1), expectParticles(false) {}
        virtual ~Renderer() {}
        
        void enqueueParticle(const Particle& p);
        
        void setBounds(Bounds<number>& b);

        void setParticleCount(int pc);
		
		void wait();
		
		void finishReceiving();

        void startReceiving();
		
		void receiveParticles();
		
        virtual void processParticle(Particle &p) = 0;
		virtual void clear() = 0;
        virtual void render() = 0;
    
	protected:
        Bounds<number> bounds;
		ConcurrentQueue<Particle> queue;
		std::thread receivingThread;
		mutable std::mutex receivingMutex;
        int particleCount;
		bool expectParticles;
	};
}

#endif
