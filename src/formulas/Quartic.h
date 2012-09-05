#ifndef QUARTIC_H
#define QUARTIC_H

#include "formulas/Formula.h"

namespace sag {
	class Quartic : public Formula {
	public:
        Quartic(): Formula() {}
        
        Quartic(const std::vector<number>& parameters): Formula(parameters) {}
		
		~Quartic() {}

		CLONEABLE(Quartic)

		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);
        
        virtual const std::string name() const { return "Quartic"; }
        virtual inline int paramCount() const { return 30; }
        virtual const ParamDistribution& getDistribution() const;
	};
}

#endif
