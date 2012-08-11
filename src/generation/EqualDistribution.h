#ifndef SAG_EQUALDISTRIBUTION_H
#define SAG_EQUALDISTRIBUTION_H

#include "generation/ParamDistribution.h"
#include "utils/Range.h"
#include "utils/types.h"

namespace sag {
    class EqualDistribution : public ParamDistribution {
    public:
        EqualDistribution(Range<number>& range): range(range) {}
        EqualDistribution(number from, number to): range(from, to) {}
        
        virtual number min(int param);
        virtual number max(int param);
        virtual const Range<number>& getRange(int param) const;
        
    private:
        Range<number> range;
    };
}

#endif