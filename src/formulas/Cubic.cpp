#include "utils/Vector.h"
#include "formulas/Cubic.h"
#include "generation/EqualDistribution.h"

namespace sag {
    const ParamDistribution& Cubic::getDistribution() const {
        static EqualDistribution dstr(-2, 2);
        return dstr;
    }

	Vector<number> Cubic::step(const Vector<number>& prev, const std::vector<number> params) {
		number x = (((params[0] * prev.x) + params[1]) * prev.x + params[2])*prev.x + params[3] +
				   ((params[4] * prev.x + params[5])*prev.x + params[6]) * prev.y +
				   (params[7] *prev.x + params[8]) * prev.y * prev.y +
				   params[9] * prev.y * prev.y * prev.y;
		number y = (((params[10] * prev.x) + params[11]) * prev.x + params[12])*prev.x + params[13] +
				   ((params[14] * prev.x + params[15])*prev.x + params[16]) * prev.y +
				   (params[17] *prev.x + params[18]) * prev.y * prev.y +
				   params[19] * prev.y * prev.y * prev.y;

		return Vector<number>(x, y);
	}
}
