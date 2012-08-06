#ifndef RENDERER_H
#define RENDERER_H

#include <queue>
#include "utils/Particle.h"

namespace sag {
	class Renderer {
	public:
        static const int QUEUE_SIZE_FACTOR = 3;
        int particleCount = -1;
        
        Renderer() {}
		virtual ~Renderer() {}
        
        void enqueueParticle(Particle& p);

        virtual void render() = 0;
    protected:
        std::queue<Particle> queue;
	};
}

#endif
