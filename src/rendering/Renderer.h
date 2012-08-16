#ifndef RENDERER_H
#define RENDERER_H

#include <queue>
#include "utils/types.h"
#include "utils/Bounds.h"
#include "utils/Vector.h"

namespace sag {
	class Renderer {
	public:
        Renderer(): particleCount(-1) {}
        virtual ~Renderer() {}
        
        virtual bool receiveParticle(Vector<number>& p);
        
        void setBounds(Bounds<number>& b);

        void setParticleCount(int pc);

        virtual void render() = 0;
    protected:
        Bounds<number> bounds;
        static const int SIZE_FACTOR = 100;
        int particleCount;
	};
}

#endif
