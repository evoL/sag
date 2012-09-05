#ifndef CUBIC_H
#define CUBIC_H

#include "formulas/Formula.h"

namespace sag {
	class Cubic : public Formula {
	public:
        Cubic(): Formula() {}
        
        Cubic(const std::vector<number>& parameters): Formula(parameters) {}
		
		~Cubic() {}

		CLONEABLE(Cubic)

		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);
        
        virtual const std::string name() const { return "Cubic"; }
        virtual inline int paramCount() const { return 20; }
        virtual const ParamDistribution& getDistribution() const;
	};
}

#endif
