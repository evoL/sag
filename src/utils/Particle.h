#ifndef SAG_PARTICLE_H
#define SAG_PARTICLE_H

#include "utils/types.h"
#include "utils/Vector.h"

namespace sag {
	/**
	 * @brief Represents single particle in 2- or 3-dimensional Euclidean space.
	 */
	class Particle {
	public:
		/**
		 * @brief Default constructor.
		 */
		Particle() {}

		/**
		 * @brief Constructor. Sets the particle in the given position.
		 *
		 * @param position The position of the particle.
		 */
		Particle(const Vector<number>& v): position(v) {}
        
        /**
         * @brief Destructor
         */
		~Particle() {}
        
        /**
         * @brief Returns the position of the particle.
         *
         * @returns Position
         */
		inline const Vector<number>& getPosition() const { return position; }

		/**
		 * @brief Returns the velocity of the particle.
		 *
		 * @returns Velocity
		 */
        inline const Vector<number>& getVelocity() const { return velocity; }
        
        /**
		 * @brief Returns the acceleration of the particle.
		 *
		 * @returns Acceleration
		 */
        inline const Vector<number>& getAcceleration() const { return acceleration; }
        
        /**
         * @brief Moves the particle to the given position and calculates its velocity.
         *
         * @param position New position
         */
        Particle& moveTo(Vector<number> pos);
        
        /**
         * @brief Sets new position of the particle and zeroes its velocity.
         *
         * @param New position
         *
         * @return This particle
         */
        inline Particle& operator=(const Vector<number>& v) {
            position = v;
            velocity.reset(0, 0, 0);
            acceleration.reset(0, 0, 0);
            
            return *this;
        }
    private:
        Vector<number> position;
        Vector<number> velocity;
        Vector<number> acceleration;
	};
}

#endif
