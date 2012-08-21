#include "formulas/Blut.h"
#include <cmath>

namespace sag {    
    number Blut::Distribution::min(int param) const {
        if (param == 8) return 0;
        return -2;
    }
    number Blut::Distribution::max(int param) const {
        if (param == 8) return 1;
        return 2;
    }
    
    const ParamDistribution& Blut::getDistribution() const {
        static Distribution dstr;
        return dstr;
    }
    
	Vector<number> Blut::step(const Vector<number>& prev, const std::vector<number> params) {
        
        number x = params[8] * (sin(params[0] * prev.y) + params[2] * cos(params[0] * prev.x)) + (1 - params[8]) * (prev.y + params[4] * (prev.x >= 0 ? 1 : -1) * sqrt(abs(params[5] * prev.x - params[6])));
        number y = params[8] * (sin(params[1] * prev.x) + params[3] * cos(params[1] * prev.y)) + (1 - params[8]) * (params[7] - prev.x);
        
		return Vector<number>(x, y);
	}
}