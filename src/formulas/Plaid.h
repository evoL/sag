#ifndef PLAID_H
#define PLAID_H

#include "formulas/Formula.h"

namespace sag {
	class Plaid : public Formula {
	public:
        Plaid(): Formula() {}
        
        Plaid(const std::vector<number>& parameters): Formula(parameters) {}
		
		~Plaid() {}

		CLONEABLE(Plaid)

		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);
        
        virtual const std::string name() const { return "Plaid"; }
        virtual inline int paramCount() const { return 12; }
        virtual const ParamDistribution& getDistribution() const;
	};
}

#endif
