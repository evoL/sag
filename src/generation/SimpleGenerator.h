#ifndef SAG_SIMPLE_GENERATOR_H
#define SAG_SIMPLE_GENERATOR_H

#include "Generator.h"

namespace sag {
    class SimpleGenerator : public Generator {
    public:
        virtual void step();
    };
}

#endif