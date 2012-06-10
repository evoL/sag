#ifndef SAG_QUADRATIC_H
#define SAG_QUADRATIC_H

#include <vector>
#include "Formula.h"
#include "utils/types.h"
#include "utils/Vector.h"

namespace sag {
    
    /**
     * @brief The Quadratic formula
     */
    class Quadratic : public Formula {
    public:
        Quadratic() { paramCount = 12; }
        
        virtual Vector<number> step(Vector<number>& src);
    };
}

#endif