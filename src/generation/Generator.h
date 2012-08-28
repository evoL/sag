#ifndef SAG_GENERATOR_H
#define SAG_GENERATOR_H

#include "utils/types.h"
#include "utils/Bounds.h"
#include "utils/Particle.h"
#include "formulas/Formula.h"
#include "rendering/Renderer.h"

namespace sag {
	class Generator {
	public:
		Generator(Formula& f, Renderer& r, int iter, bool if3D=false);
		virtual ~Generator() {}

		void run();
        
        static const int UNLIMITED_ITERATIONS = -1;
        
        void setParticleCount(int pc);
        void reset();

	protected:
		Formula *formula;
		Bounds<number> bounds;
		int particleCount;
		const bool if3D;
        int iterations;

		void sendParticle(const Particle& p);
		
		virtual void generate() = 0;
		
	private:
		static const int WARMUP_ITERATIONS = 5000;
		Renderer *renderer;

		void setBounds();
	};
}

#endif
