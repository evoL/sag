#include "utils/Vector.h"
#include "formulas/Trig.h"
#include "generation/EqualDistribution.h"
#include <cmath>

namespace sag {
    const ParamDistribution& Trig::getDistribution() const {
        static EqualDistribution dstr(-2.5, 2.5);
        return dstr;
    }

	Vector<number> Trig::step(const Vector<number>& prev, const std::vector<number> params) {
		number x = params[0] * sin(params[1] * prev.y) + params[2] * cos(params[3] * prev.x) +
				   params[4] * sin(params[5] * prev.x) + params[6] * cos(params[7] * prev.y);

		number y = params[8] * sin(params[9] * prev.y) + params[10] * cos(params[11] * prev.x) +
				   params[12] * sin(params[13] * prev.x) + params[14] * cos(params[15] * prev.y);

		return Vector<number>(x, y);
	}
}
