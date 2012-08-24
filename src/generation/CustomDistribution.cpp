#include "generation/CustomDistribution.h"

namespace sag {
	number CustomDistribution::min(int param) const {
		return dstr[param].min();
	}
	number CustomDistribution::max(int param) const {
		return dstr[param].max();
	}
	virtual const Range<number> CustomDistribution::getRange(int param) const {
		return dstr[param];
	}
}
