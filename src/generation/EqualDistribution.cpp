#include "generation/EqualDistribution.h"

namespace sag {
    number EqualDistribution::min(int param) {
        return range.min();
    }
    
    number EqualDistribution::max(int param) {
        return range.max();
    }
    
    const Range<number>& EqualDistribution::getRange(int param) const {
        return range;
    }
}