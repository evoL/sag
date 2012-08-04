#ifndef QUADRATIC_H
#define QUADRATIC_H

#include "formulas/Formula.h"

namespace sag {
	class Quadratic : public Formula {
	public:
		const bool if3D = false;
		const int paramCount = 12;

		~Quadratic() {}

		Vector<number> step(const Vector<number>&prev);
	};
}

#endif
