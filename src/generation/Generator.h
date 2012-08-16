#ifndef SAG_GENERATOR_H
#define SAG_GENERATOR_H

#include "utils/types.h"
#include "formulas/Formula.h"
#include "rendering/Renderer.h"
#include "utils/Bounds.h"

namespace sag {
	class Generator {
	public:
		Generator(Formula& f, Renderer& r, int iter, bool if3D=true);
		virtual ~Generator() {}

		virtual void run() = 0;
        
        static const int UNLIMITED_ITERATIONS = -1;
        
        void setParticleCount(int pc);
        void reset();

	protected:
		Formula *formula;
		Bounds<number> bounds;
		int particleCount;
		const bool if3D;
        int iterations;

		void sendParticle(Vector<number>& p);

	private:
		Renderer *renderer;
		static const int WARMUP_ITERATIONS = 5000;

		void setBounds();
	};
}

#endif
