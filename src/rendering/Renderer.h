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
#include "utils/Color.h"

namespace sag {
	class Renderer {
	public:
        Renderer():
            expectParticles(false),
            receiving(false),
            color(255, 0, 0),
            colorShiftLevel(0.25),
            blur(true)
        {}
        
        virtual ~Renderer() {}
        
        void enqueueParticle(const Particle& p);
        
        void setBounds(Bounds<number>& b);
		
		void wait();
        void abort();
		
		void finishReceiving();

        void startReceiving();
		
		void receiveParticles();
		
        virtual void processParticle(Particle &p) = 0;
		virtual void clear() = 0;
        virtual void render() = 0;

        inline int getReceivedParticleCount() { return receivedParticleCount; }
        
        void setColor(Color& c) { color = c; }
        inline const Color& getColor() const { return color; }
        
        void setColorShiftLevel(double l) { colorShiftLevel = l; }
        inline const double getColorShiftLevel() const { return colorShiftLevel; }
        
        void setBlur(bool b) { blur = b; }
    
	protected:
        Bounds<number> bounds;
		ConcurrentQueue<Particle> queue;
		std::thread receivingThread;
		mutable std::mutex receivingMutex;
        std::condition_variable waitingCV;
		volatile bool expectParticles;
		volatile bool receiving;
		volatile int receivedParticleCount;
        
        Color color;
        double colorShiftLevel;
        bool blur;
	};
}

#endif
