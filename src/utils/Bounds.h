#ifndef BOUNDS_H
#define BOUNDS_H

#include <vector>
#include "utils/Vector.h"
#include "utils/Random.h"

namespace sag {
	template <typename T>
	class Bounds {
	public:
        class Raw {
        public:
            T xmin, xmax, ymin, ymax, zmin, zmax;
            
            Raw(): xmin(-1), xmax(1), ymin(-1), ymax(1), zmin(-1), zmax(1) {}
            Raw(T xmin, T xmax, T ymin, T ymax, T zmin, T zmax):
                xmin(xmin), xmax(xmax),
                ymin(ymin), ymax(ymax),
                zmin(zmin), zmax(zmax) {}
        };
        
		Bounds(): center(Vector<T>()), radius(1),
                  raw(-1, 1, -1, 1, -1, 1) {}
        
		Bounds(T radius):
				  center(Vector<T>()), radius(radius),
                  raw(-radius, radius, -radius, radius, -radius, radius) {}

		Bounds(const Vector<T>& center, T radius):
				  center(center), radius(radius),
                  raw(
                      center.x - radius, center.x + radius,
                      center.y - radius, center.y + radius,
                      center.z - radius, center.z + radius
                  ) {}
        
		Bounds(std::vector<Vector<T>>& particles);

		~Bounds() {}

		inline Vector<T>& getCenter() const { return *center; }

		inline T getRadius() const { return radius; }

		bool contains(const Vector<T> &v);

		Vector<T> getRandomVector(bool if3D = true, Random<T>& rnd = Random<T>::getGlobal());
        
        Raw getRawBounds() const;

	private:
		Vector<T> center;
		T radius;
        Raw raw;
	};
}

#endif
