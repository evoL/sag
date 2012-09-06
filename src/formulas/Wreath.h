#ifndef WREATH_H
#define WREATH_H

#include "formulas/Formula.h"
#include "utils/types.h"

namespace sag {
	class Wreath : public Formula {
	public:
        Wreath(): Formula() {}
        
        Wreath(const std::vector<number>& parameters): Formula(parameters) {}
		
		~Wreath() {}

		CLONEABLE(Wreath)

		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);
        
        virtual const std::string name() const { return "Wreath"; }
        virtual inline int paramCount() const { return 6; }
        virtual const ParamDistribution& getDistribution() const;
	private:
        static constexpr number TWICE_PI = 6.28318530718;

        class Distribution : public ParamDistribution {
		public:
			virtual number min(int param) const;
			virtual number max(int param) const;
        };
	};
}

#endif
