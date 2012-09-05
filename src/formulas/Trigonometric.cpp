#include "utils/Vector.h"
#include "formulas/Trigonometric.h"
#include "generation/EqualDistribution.h"
#include <cmath>

namespace sag {
    const ParamDistribution& Trigonometric::getDistribution() const {
        static EqualDistribution dstr(-2, 2);
        return dstr;
    }

	Vector<number> Trigonometric::step(const Vector<number>& prev, const std::vector<number> params) {
		number x = params[0] * sin(params[1] * prev.y) + params[2] * cos(params[3] * prev.x);
		number y = params[4] * sin(params[5] * prev.x) + params[6] * cos(params[7] * prev.y);

		return Vector<number>(x, y);
	}
}
