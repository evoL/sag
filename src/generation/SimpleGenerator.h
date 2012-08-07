#ifndef SAG_SIMPLE_GENERATOR_H
#define SAG_SIMPLE_GENERATOR_H

#include "generation/Generator.h"

namespace sag {
	class SimpleGenerator : public Generator {
	public:
		void run();
	private:
		static const int ITERS = 10000;
	};
}

#endif
