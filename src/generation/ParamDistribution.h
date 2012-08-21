#ifndef SAG_PARAMDISTRIBUTION_H
#define SAG_PARAMDISTRIBUTION_H

#include "utils/Range.h"
#include "utils/types.h"

namespace sag {
    class ParamDistribution {
    public:
        virtual number min(int param) const = 0;
        virtual number max(int param) const = 0;
        virtual const Range<number> getRange(int param) const;
    };
}

#endif