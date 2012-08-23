#ifndef FORMULA_H
#define FORMULA_H

#include <vector>
#include <string>
#include "utils/types.h"
#include "utils/Vector.h"
#include "generation/ParamDistribution.h"

namespace sag {
	class Formula {
	public:
		Formula() {}
		Formula(const std::vector<number>& parameters):
            parameters(parameters) {}

		virtual ~Formula() {}

        void prepare();
        void reset();
        
		Vector<number> step(const Vector<number>& prev);
        virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params) = 0;
        
        inline Vector<number> getStartPoint() const { return startPoint; }
        inline const std::vector<number>& getParameters() const { return parameters; }
        
        virtual const std::string name() const = 0;
        virtual inline bool is3D() const { return false; }
        virtual inline int paramCount() const { return 0; }
        virtual const ParamDistribution& getDistribution() const = 0;
        
	protected:
		static const int MAXITER = 5000;
		std::vector<number> parameters;
        Vector<number> startPoint;
        
		bool verifyParams(const std::vector<number>& params);
	};
}

#endif
