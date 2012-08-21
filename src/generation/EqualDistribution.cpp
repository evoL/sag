#include "generation/EqualDistribution.h"

namespace sag {
    number EqualDistribution::min(int param) const {
        return range.min();
    }
    
    number EqualDistribution::max(int param) const {
        return range.max();
    }
    
    const Range<number> EqualDistribution::getRange(int param) const {
        return range;
    }
}