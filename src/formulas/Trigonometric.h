#ifndef TRIGONOMETRIC_H
#define TRIGONOMETRIC_H

#include "formulas/Formula.h"

namespace sag {
	class Trigonometric : public Formula {
	public:
        Trigonometric(): Formula() {}
        
        Trigonometric(const std::vector<number>& parameters): Formula(parameters) {}
		
		~Trigonometric() {}

		CLONEABLE(Trigonometric)

		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);
        
        virtual const std::string name() const { return "Trigonometric"; }
        virtual inline int paramCount() const { return 8; }
        virtual const ParamDistribution& getDistribution() const;
	};
}

#endif
