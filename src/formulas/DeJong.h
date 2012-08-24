#ifndef SAG_DEJONG_H
#define SAG_DEJONG_H

#include "formulas/Formula.h"

namespace sag {
    class DeJong : public Formula {
        ~DeJong() {}
        
        CLONEABLE(DeJong)

		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);
        
        virtual const std::string name() const { return "DeJong"; }
        virtual inline int paramCount() const { return 4; }
        virtual const ParamDistribution& getDistribution() const;
    };
}

#endif
