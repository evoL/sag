#ifndef QUADRATIC_H
#define QUADRATIC_H

#include "formulas/Formula.h"

namespace sag {
	class Quadratic : public Formula {
	public:
		~Quadratic() {}

		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);
        
        virtual inline int paramCount() const { return 12; }
        virtual const ParamDistribution& getDistribution() const;
	};
}

#endif
