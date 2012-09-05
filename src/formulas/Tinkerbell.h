#ifndef TINKERBELL_H
#define TINKERBELL_H

#include "formulas/Formula.h"

namespace sag {
	class Tinkerbell : public Formula {
	public:
        Tinkerbell(): Formula() {
        	startPoint.reset(0.1, 0.1);
        }
        
        Tinkerbell(const std::vector<number>& parameters): Formula(parameters) {}
		
		~Tinkerbell() {}

		CLONEABLE(Tinkerbell)

		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);
        
        virtual const std::string name() const { return "Tinkerbell"; }
        virtual inline int paramCount() const { return 4; }
        virtual const ParamDistribution& getDistribution() const;
	};
}

#endif
