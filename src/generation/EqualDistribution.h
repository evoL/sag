#ifndef SAG_EQUALDISTRIBUTION_H
#define SAG_EQUALDISTRIBUTION_H

#include "generation/ParamDistribution.h"
#include "utils/Range.h"
#include "utils/types.h"

namespace sag {
    /**
     * @brief A ParamDistribution where every parameter has the same bounds.
     */
    class EqualDistribution : public ParamDistribution {
    public:
        /**
         * @brief Constructs the distribution using a Range.
         *
         * @param range A range.
         */
        EqualDistribution(Range<number>& range): range(range) {}
        
        /**
         * @brief Constructs the distribution with its bounds specified.
         *
         * @number from The lower bound.
         * @number to The upper bound.
         */
        EqualDistribution(number from, number to): range(from, to) {}
        
        virtual ~EqualDistribution() {}

        virtual number min(int param) const;
        virtual number max(int param) const;
        virtual const Range<number> getRange(int param) const;
        
    private:
        Range<number> range;
    };
}

#endif
