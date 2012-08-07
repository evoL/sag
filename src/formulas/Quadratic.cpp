#include "utils/Vector.h"
#include "formulas/Quadratic.h"


namespace sag {
	Vector<number> Quadratic::step(const Vector<number>& prev) {
		number x = parameters[0] + (parameters[1] + parameters[2] * prev.x + parameters[3] * prev.y) * prev.x + (parameters[4] + parameters[5] * prev.y) * prev.y;
		number y = parameters[6] + (parameters[7] + parameters[8] * prev.x + parameters[9] * prev.y) * prev.x + (parameters[10] + parameters[11] * prev.y) * prev.y;

		return Vector<number>(x, y);
	}
}
