#ifndef RENDERER_H
#define RENDERER_H

#if defined(HAS_BOOST) && THREAD_NAMESPACE == boost
#  include <boost/thread.hpp>
#else
#  include <thread>
#  include <mutex>
#  include <condition_variable>
#endif

#include "utils/types.h"
#include "utils/Bounds.h"
#include "utils/Particle.h"
#include "utils/ConcurrentQueue.h"
#include "utils/Color.h"

namespace sag {
    /**
     * @brief The abstract Renderer class.
     *
     * The Renderer is an object that processes received particles
     * in some way. Most often it will display the on an image, but different,
     * less conventional uses are encouraged.
     */
	class Renderer {
	public:
        /**
         * @brief The default constructor
         */
        Renderer():
            expectParticles(false),
            receiving(false)
        {}
        
        virtual ~Renderer() {} ///< The destructor.
        
        /**
         * @brief Adds an particle to the queue to be processed.
         *
         * @param p The reference to the Particle.
         */
        void enqueueParticle(const Particle& p);
        
        /**
         * @brief Sets the bounds to consider while rendering.
         *
         * @param b The bounds.
         */
        void setBounds(Bounds<number>& b);
		
        /**
         * @brief Blocks until the renderer is finished.
         */
		void wait();
        
        /**
         * @brief Immediately aborts the rendering.
         */
        void abort();
		
        /**
         * @brief Notifies the Renderer that no further particles are being generated.
         *
         * This method allows the Renderer to empty its queue and renderer the remaining
         * particle.
         */
		void finishReceiving();

        /**
         * @brief Notifies the Renderer that particles have just begun generating.
         */
        void startReceiving();
		
        /**
         * @brief Receives particles from the queue.
         */
		void receiveParticles();
		
        /**
         * @brief Processes a single received particle.
         *
         * This method allows for storing the particle in a way that is useful
         * for rendering.
         *
         * @param p The particle to process.
         */
        virtual void processParticle(Particle &p) = 0;
        
        /**
         * @brief Clears whatever the Renderer has to clear.
         *
         * The Renderer could, for instance, render an image. This method would then
         * clear that image.
         */
		virtual void clear() = 0;
        
        /**
         * @brief Perform the rendering.
         */
        virtual void render() = 0;

        /**
         * @brief Returns how many particles did the Renderer already receive.
         *
         * @returns The received particle count.
         */
        inline int getReceivedParticleCount() { return receivedParticleCount; }
    
	protected:
        Bounds<number> bounds;
		ConcurrentQueue<Particle> queue;
		THREAD_NAMESPACE::thread receivingThread;
		mutable THREAD_NAMESPACE::mutex receivingMutex;
        THREAD_NAMESPACE::condition_variable waitingCV;
		volatile bool expectParticles;
		volatile bool receiving;
		volatile int receivedParticleCount;
	};
}

#endif
