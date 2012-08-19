#ifndef SAG_PARTICLE_H
#define SAG_PARTICLE_H

#include "utils/types.h"
#include "utils/Vector.h"

namespace sag {
	class Particle {
	public:
		Particle() {}
		Particle(const Vector<number>& v): position(v) {}
        
        ~Particle() {}
        
        inline const Vector<number>& getPosition() const { return position; }
        inline const Vector<number>& getVelocity() const { return velocity; }
        
        Particle& moveTo(Vector<number> pos);
        
        inline Particle& operator=(const Vector<number>& v) {
            position = v;
            velocity.reset(0, 0, 0);
            
            return *this;
        }
    private:
        Vector<number> position;
        Vector<number> velocity;
	};
}

#endif
