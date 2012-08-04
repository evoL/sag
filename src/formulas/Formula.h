#ifndef FORMULA_H
#define FORMULA_H

#include <vector>
#include "utils/types.h"
#include "utils/Vector.h"

namespace sag {
	class Formula {
	public:
		const bool if3D;
		const int paramCount;

		Formula();

		Formula(const std::vector<number>& parameters): parameters(parameters) {}

		virtual ~Formula() {}

		virtual Vector<number> step(const Vector<number>& prev);
	protected:
		const int MAXITER = 5000;
		std::vector<number> parameters;

		std::vector<number>& randomParameters();
	};
}

#endif
