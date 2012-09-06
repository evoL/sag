#include "utils/Vector.h"
#include "formulas/Wreath.h"
#include <cmath>

namespace sag {
	number Wreath::Distribution::min(int param) const {
        if (param == 5) return 2;
        return -1.2;
    }
    number Wreath::Distribution::max(int param) const {
        if (param == 5) return 21;
        return 1.2;
    }

    const ParamDistribution& Wreath::getDistribution() const {
        static Distribution dstr;
        return dstr;
    }

	Vector<number> Wreath::step(const Vector<number>& prev, const std::vector<number> params) {
		number cc = cos(TWICE_PI/(int)params[5]);
		number sc = sin(TWICE_PI/(int)params[5]);
		number temp = prev.x + params[1] * sin(params[2] * prev.y + params[3]);

		number x = 10 * params[0] + temp * cc + prev.y * sc;
		number y = 10 * params[4] - temp * sc + prev.y * cc;

		return Vector<number>(x, y);
	}
}
