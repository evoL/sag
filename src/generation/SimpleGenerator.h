#ifndef SAG_SIMPLE_GENERATOR_H
#define SAG_SIMPLE_GENERATOR_H

#include "generation/Generator.h"
#include <string>

namespace sag {
	class SimpleGenerator : public Generator {
	public:
        SimpleGenerator(Formula& f, Renderer& r, int iter, bool if3D=false): Generator(f, r, iter, if3D) {}
		~SimpleGenerator() {}
		
		std::string serialize() const;
		
		void run();
	};
}

#endif
