#include "formulas/DeJong.h"

#include "generation/EqualDistribution.h"
#include <cmath>

namespace sag {
    const ParamDistribution* DeJong::getDistribution() const {
        static ParamDistribution* dstr = new EqualDistribution(-2, 2);
        return dstr;
    }
    
	Vector<number> DeJong::step(const Vector<number>& prev, const std::vector<number> params) {
        number x = sin(params[0] * prev.y) - cos(params[1] * prev.x);
        number y = sin(params[2] * prev.x) - cos(params[3] * prev.y);
        
		return Vector<number>(x, y);
	}
}
