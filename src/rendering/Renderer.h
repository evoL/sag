#ifndef RENDERER_H
#define RENDERER_H

#include <queue>
#include "utils/types.h"
#include "utils/Bounds.h"
#include "utils/Particle.h"

namespace sag {
	class Renderer {
	public:
        Renderer() {}
		virtual ~Renderer() {}
        
        bool enqueueParticle(Particle& p);
        
        void setBounds(Bounds<number>& b);
        void setParticleCount(int count);

        virtual void render() = 0;
    protected:
        std::queue<Particle> queue;
        Bounds<number>* bounds;
        
        static const int QUEUE_SIZE_FACTOR = 3;
        int particleCount = -1;
	};
}

#endif
