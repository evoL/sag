#include "generation/SimpleGenerator.h"
#include <vector>
#include "utils/Vector.h"
#include "utils/types.h"

namespace sag {
	void SimpleGenerator::run() {
		std::vector<Vector<number>> initials;

		initials.reserve(particleCount);

		for (int i=0; i<particleCount; i++) {
			initials[i] = bounds.getRandomVector(if3D);
			sendParticle(initials[i]);
		}

		for (int i=1; i<ITERS; i++) {
			for (int j=0; j < particleCount; j++) {
				initials[j] = formula->step(initials[j]);
				sendParticle(initials[j]);
			}
		}


	}
}
