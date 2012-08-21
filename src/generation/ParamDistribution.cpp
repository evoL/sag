#include "generation/ParamDistribution.h"

namespace sag {
    const Range<number> ParamDistribution::getRange(int param) const {
        return Range<number>(min(param), max(param));
    }
}