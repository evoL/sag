#ifndef SAG_GENERATOR_H
#define SAG_GENERATOR_H

#include "utils/types.h"
#include "formulas/Formula.h"
#include "rendering/Renderer.h"
#include "utils/Bounds.h"

namespace sag {
	class Generator {
	public:
		Generator(Formula *f, Renderer *r, int pc, bool if3D=true);

		virtual ~Generator();

		virtual void run() = 0;

	protected:
		Formula *formula;
		Bounds<number> bounds;
		const int particleCount;
		const bool if3D;

		void sendParticle(Vector<number>& p);

	private:
		Renderer *renderer;
		static const int ITERS = 5000;

		void setBounds();
	};
}

#endif
