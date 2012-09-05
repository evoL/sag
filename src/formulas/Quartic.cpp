#include "utils/Vector.h"
#include "formulas/Quartic.h"
#include "generation/EqualDistribution.h"

namespace sag {
    const ParamDistribution& Quartic::getDistribution() const {
        static EqualDistribution dstr(-2, 2);
        return dstr;
    }

	Vector<number> Quartic::step(const Vector<number>& prev, const std::vector<number> params) {
		number x = ((((params[0] * prev.x) + params[1]) * prev.x + params[2]) * prev.x + params[3]) * prev.x + params[4] +
				   (((params[5] * prev.x + params[6]) * prev.x + params[7]) * prev.x + params[8])* prev.y +
				   ((params[9] *prev.x + params[10]) * prev.x + params[11]) * prev.y * prev.y +
				   (params[12] * prev.x + params[13]) * prev.y * prev.y * prev.y +
				   params[14] * prev.y * prev.y * prev.y * prev.y;
		number y = ((((params[15] * prev.x) + params[16]) * prev.x + params[17]) * prev.x + params[18]) * prev.x + params[19] +
				   (((params[20] * prev.x + params[21]) * prev.x + params[22]) * prev.x + params[23])* prev.y +
				   ((params[24] *prev.x + params[25]) * prev.x + params[26]) * prev.y * prev.y +
				   (params[27] * prev.x + params[28]) * prev.y * prev.y * prev.y +
				   params[29] * prev.y * prev.y * prev.y * prev.y;

		return Vector<number>(x, y);
	}
}
