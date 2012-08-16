#ifndef SAG_SIMPLE_GENERATOR_H
#define SAG_SIMPLE_GENERATOR_H

#include "generation/Generator.h"

namespace sag {
	class SimpleGenerator : public Generator {
	public:
        SimpleGenerator(Formula& f, Renderer& r, int iter, bool if3D=true): Generator(f, r, iter, if3D) {}
		~SimpleGenerator() {}

		void run();
	};
}

#endif
