#ifndef CUSTOMDISTRIBUTION_H
#define CUSTOMDISTRIBUTION_H

#include "generation/ParamDistribution.h"
#include <vector>
#include "utils/Range.h"
#include "utils/types.h"

namespace sag {
    /**
     * @brief A ParamDistribution where each parameter has its own range.
     */
	class CustomDistribution : public ParamDistribution {
	public:
        /**
         * @brief Constructs a default distribution
         */
        CustomDistribution() {}
        
        /**
         * @brief Constructs a distribution using a std::vector of Ranges.
         *
         * @param dstr The vector.
         */
		CustomDistribution(std::vector<Range<number>> dstr): dstr(dstr) {}

		virtual ~CustomDistribution() {}

		virtual number min(int param) const;
		virtual number max(int param) const;
		virtual const Range<number> getRange(int param) const;

        /**
         * @brief Returns the parameter count covered by the distribution.
         *
         * @returns The parameter count.
         */
		inline int paramCount() { return dstr.size(); }

	private:
		std::vector<Range<number>> dstr;
	};
}

#endif
