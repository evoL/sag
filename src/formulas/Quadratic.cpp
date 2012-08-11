#include "utils/Vector.h"
#include "formulas/Quadratic.h"
#include "generation/EqualDistribution.h"

namespace sag {
    const ParamDistribution* Quadratic::getDistribution() const {
        static ParamDistribution* dstr = new EqualDistribution(-2, 2);
        return dstr;
    }

	Vector<number> Quadratic::step(const Vector<number>& prev, const std::vector<number> params) {
		number x = params[0] + (params[1] + params[2] * prev.x + params[3] * prev.y) * prev.x + (params[4] + params[5] * prev.y) * prev.y;
		number y = params[6] + (params[7] + params[8] * prev.x + params[9] * prev.y) * prev.x + (params[10] + params[11] * prev.y) * prev.y;

		return Vector<number>(x, y);
	}
}
