#ifndef FORMULA_H
#define FORMULA_H

#include <vector>
#include "utils/types.h"
#include "utils/Vector.h"

namespace sag {
	class Formula {
	public:
		const bool if3D = false;
		const int paramCount = 0;

		Formula();

		Formula(const std::vector<number>& parameters): parameters(parameters) {}

		virtual ~Formula() {}

		virtual Vector<number> step(const Vector<number>& prev) = 0;
	protected:
		const int MAXITER = 5000;
		std::vector<number> parameters;
		const std::vector<number> minParam = std::vector<number>();
		const std::vector<number> maxParam = std::vector<number>();

	private:
		void randomParameters();

		bool verifyParams(const std::vector<number>& params);
	};
}

#endif
