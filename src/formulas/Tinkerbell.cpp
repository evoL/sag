#include "utils/Vector.h"
#include "formulas/Tinkerbell.h"
#include "generation/EqualDistribution.h"

namespace sag {
    const ParamDistribution& Tinkerbell::getDistribution() const {
        static EqualDistribution dstr(-2, 2);
        return dstr;
    }

	Vector<number> Tinkerbell::step(const Vector<number>& prev, const std::vector<number> params) {
		number x = prev.x * prev.x - prev.y * prev.y + params[0] * prev.x + params[1] * prev.y;
		number y = 2 * prev.x * prev.y + params[2] * prev.x + params[3] * prev.y;

		return Vector<number>(x, y);
	}
}
