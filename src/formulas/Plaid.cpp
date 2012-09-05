#include "utils/Vector.h"
#include "formulas/Plaid.h"
#include "generation/EqualDistribution.h"

namespace sag {
    const ParamDistribution& Plaid::getDistribution() const {
        static EqualDistribution dstr(-2, 2);
        return dstr;
    }

	Vector<number> Plaid::step(const Vector<number>& prev, const std::vector<number> params) {
		number x = ((((params[0] * prev.y + params[1]) * prev.y + params[2]) * prev.y + params[3]) * prev.y + params[4]) * prev.y + params[5];
		number y = ((((params[6] * prev.x + params[7]) * prev.x + params[8]) * prev.x + params[9]) * prev.x + params[10]) * prev.x + params[11];

		return Vector<number>(x, y);
	}
}
