#ifndef FORMULA_H
#define FORMULA_H

#include <vector>
#include "utils/types.h"
#include "utils/Vector.h"

namespace sag {
	class Formula {
	public:
		static const bool if3D = false;
		static const int paramCount = 0;

		Formula();

		Formula(const std::vector<number>& parameters): parameters(parameters) {}

		virtual ~Formula() {}

		virtual Vector<number> step(const Vector<number>& prev) = 0;
	protected:
		static const int MAXITER = 5000;
		std::vector<number> parameters;
		static std::vector<number> minParam;
		static std::vector<number> maxParam;

	private:
		void randomParameters();

		bool verifyParams(const std::vector<number>& params);
	};
}

#endif
