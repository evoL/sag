#ifndef SAG_BLUT_H
#define SAG_BLUT_H

#include "formulas/Formula.h"

namespace sag {
    class Blut : public Formula {
    public:        
        ~Blut() {}
        
		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);
        
        virtual inline int paramCount() const { return 9; }
        virtual const ParamDistribution& getDistribution() const;
    private:
        class Distribution : public ParamDistribution {
        public:
            virtual number min(int param) const;
            virtual number max(int param) const;
        };
    };
}

#endif