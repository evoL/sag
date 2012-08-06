#ifndef PARTICLE_H
#define PARTICLE_H

#include "utils/types.h"
#include "utils/Vector.h"

namespace sag {
	class Particle {
	public:
		Vector<number> position;

		Particle(): position(Vector<number>(0, 0, 0)) {}

		Particle(const Vector<number>& v): position(v) {}

		~Particle() {}
	};
}

#endif
