#ifndef BOUNDS_H
#define BOUNDS_H

#include <vector>
#include "utils/Vector.h"
#include "utils/Random.h"
namespace sag {
	/**
	 * @brief Represents boundaries in 2- or 3-dimensional Euclidean space
	 *
	 * Boundaries are specified by center and radius.
	 */
	template <typename T>
	class Bounds {
	public:
        /**
         * @brief Raw boundaries
         */
		class Raw {
        public:
            T xmin, xmax, ymin, ymax, zmin, zmax;
            
            Raw(): xmin(-1), xmax(1), ymin(-1), ymax(1), zmin(-1), zmax(1) {}
            Raw(T xmin, T xmax, T ymin, T ymax, T zmin, T zmax):
                xmin(xmin), xmax(xmax),
                ymin(ymin), ymax(ymax),
                zmin(zmin), zmax(zmax) {}
        };
        
		/**
		 * @brief Default constructor.
		 *
		 * Center is set as (0.0, 0.0, 0.0). Radius is set as 1.
		 */
		Bounds(): center(Vector<T>()), radius(1),
                  raw(-1, 1, -1, 1, -1, 1) {}
        
		/**
		 * @brief Constructor
		 *
		 * Center is set as (0.0, 0.0, 0.0). Radius is set by given value.
		 *
		 * @param radius Given radius
		 */
		Bounds(T radius):
				  center(Vector<T>()), radius(radius),
                  raw(-radius, radius, -radius, radius, -radius, radius) {}

		/** @brief Constructor
		 *
		 * @param center The center of the boundaries.
		 * @param radius The radius of the boundaries.
		 */
		Bounds(const Vector<T>& center, T radius):
				  center(center), radius(radius),
                  raw(
                      center.x - radius, center.x + radius,
                      center.y - radius, center.y + radius,
                      center.z - radius, center.z + radius
                  ) {}
        
		/**
		 * @brief Constructor
		 *
		 * Boundaries are based on given set of particles.
		 * Boundaries should contain all of the particles.
		 *
		 * @param particles Particles to be processed.
		 */
		Bounds(std::vector<Vector<T>>& particles);

		/**
		 * @brief Destructor
		 */
		~Bounds() {}
		
		/**
		 * @brief Returns the center of the boundaries.
		 *
		 * @returns The center of the boundaries.
		 */
		inline Vector<T> getCenter() const { return center; }

		/**
		 * @brief Returns the radius of the boundaries.
		 *
		 * @returns The radius of the boundaries.
		 */
		inline T getRadius() const { return radius; }

		/**
		 * @brief Checks if boundaries contain given vector.
		 *
		 * @param The vector to be checked
		 *
		 * @returns True if boundaries contain given vector.
		 */
		bool contains(const Vector<T> &v);

		/**
		 * @brief Generates random vector within boundaries.
		 *
		 * @params if3D (optional) If true, generates vector in 3D. By default set to false.
		 * @params rnd (optional) Random engine. by default set to global random engine.
		 *
		 * @returns Requested vector
		 */
		Vector<T> getRandomVector(bool if3D = false, Random<T>& rnd = Random<T>::getGlobal());
        
        /**
         * @brief Returns raw boundaries
         *
         * @returns Raw boundaries
         */
		Raw getRawBounds() const;

	private:
		Vector<T> center;
		T radius;
        Raw raw;
	};
}

#endif
