#ifndef TRIG_H
#define TRIG_H

#include "formulas/Formula.h"

namespace sag {
	class Trig : public Formula {
	public:
        Trig(): Formula() {}
        
        Trig(const std::vector<number>& parameters): Formula(parameters) {}
		
		~Trig() {}

		CLONEABLE(Trig)

		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);
        
        virtual const std::string name() const { return "Trig"; }
        virtual inline int paramCount() const { return 16; }
        virtual const ParamDistribution& getDistribution() const;
	};
}

#endif
