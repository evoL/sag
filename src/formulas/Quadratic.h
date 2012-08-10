#ifndef QUADRATIC_H
#define QUADRATIC_H

#include "formulas/Formula.h"

namespace sag {
	class Quadratic : public Formula {
	public:
		static const bool if3D = false;
		static const int paramCount = 12;
		static std::vector<number> minParam;
		static std::vector<number> maxParam;

		~Quadratic() {}

		Vector<number> step(const Vector<number>&prev);
	};
}

#endif
