#ifndef CUSTOMDISTRIBUTION_H
#define CUSTOMDISTRIBUTION_H

#include "generation/ParamDistribution.h"
#include <vector>
#include "utils/Range.h"
#include "utils/types.h"

namespace sag {
	class CustomDistribution : public ParamDistribution {
	public:
		CustomDistribution(std::vector<Range<number>> dstr): dstr(dstr) {}

		virtual ~CustomDistribution() {}

		virtual number min(int param) const;
		virtual number max(int param) const;
		virtual const Range<number> getRange(int param) const;

		inline int paramCount() { return dstr.size(); }

	private:
		const std::vector<Range<number>> dstr;
	};
}

#endif
