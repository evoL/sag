#ifndef SAG_PARAMDISTRIBUTION_H
#define SAG_PARAMDISTRIBUTION_H

#include "utils/Range.h"
#include "utils/types.h"

namespace sag {
    /**
     * @brief Determines the ranges of formula parameters.
     */
    class ParamDistribution {
    public:
    	virtual ~ParamDistribution() {}

        /**
         * @brief Gets the lower bound of the specified parameter.
         *
         * @param param The parameter index
         *
         * @returns The lower bound of the parameter.
         */
        virtual number min(int param) const = 0;
        
        /**
         * @brief Gets the upper bound of the specified parameter.
         *
         * @param param The parameter index
         *
         * @returns The upper bound of the parameter.
         */
        virtual number max(int param) const = 0;
        
        /**
         * @brief Gets the Range object for the parameter.
         *
         * @param param The parameter index
         *
         * @returns A Range.
         */
        virtual const Range<number> getRange(int param) const;
    };
}

#endif
