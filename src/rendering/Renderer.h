#ifndef RENDERER_H
#define RENDERER_H

#include <queue>
#include "utils/types.h"
#include "utils/Bounds.h"
#include "utils/Vector.h"

namespace sag {
	class Renderer {
	public:
        virtual ~Renderer() {}
        
        bool enqueueParticle(Vector<number>& p);
        
        void setBounds(Bounds<number>& b);

        void setParticleCount(int pc);

        virtual void render() = 0;
    protected:
        std::queue<Vector<number>> queue;
        Bounds<number> bounds;
        static const int QUEUE_SIZE_FACTOR = 100;
        int particleCount;
	};
}

#endif
