#ifndef SAG_GENERATOR_H
#define SAG_GENERATOR_H

#include "utils/types.h"
#include "utils/Bounds.h"
#include "utils/Particle.h"
#include "formulas/Formula.h"
#include "rendering/Renderer.h"
#include <atomic>

namespace sag {
	class Generator {
	public:
		Generator(Formula& f, Renderer& r, int iter, bool if3D=false);
		virtual ~Generator() {}

		virtual void run() = 0;
        
        static const int UNLIMITED_ITERATIONS = -1;
        
        void setParticleCount(int pc);
        void reset();
		void abort();

	protected:
		Formula *formula;
		Bounds<number> bounds;
		int particleCount;
		const bool if3D;
        std::atomic<bool> running;
        int iterations;
		Renderer *renderer;

		void sendParticle(const Particle& p);
		
	private:
		static const int WARMUP_ITERATIONS = 5000;

		void setBounds();
	};
}

#endif
