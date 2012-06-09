#include "SimpleGenerator.h"

namespace sag {
    void SimpleGenerator::step() {
        this->initialize();
        
        for (auto p = this->particles.begin(); p < this->particles.end(); p++) {
            p->position = this->formula->step(p->position);
        }
    }
}