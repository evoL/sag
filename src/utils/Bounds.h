#ifndef BOUNDS_H
#define BOUNDS_H

#include <vector>
#include "utils/Vector.h"

namespace sag {
	template <typename T>
	class Bounds {
	public:
		Bounds(): center(Vector<T>()), radius(1),
				  xmin(-1), xmax(1),
				  ymin(-1), ymax(1),
				  zmin(-1), zmax(1) {}

		Bounds(T radius):
				  center(Vector<T>()), radius(radius),
				  xmin(-radius), xmax(radius),
				  ymin(-radius), ymax(radius),
				  zmin(-radius), zmax(radius) {}

		Bounds(const Vector<T>& center, T radius):
				  center(center), radius(radius),
				  xmin(center.x - radius), xmax(center.x + radius),
				  ymin(center.y - radius), ymax(center.y + radius),
				  zmin(center.z - radius), zmax(center.z + radius) {}

		Bounds(std::vector<Vector<T>>& particles);

		~Bounds() {}

		inline Vector<T>& getCenter() const { return *center; }

		inline T getRadius() const { return radius; }

		bool contains(const Vector<T> &v);

		Vector<T> getRandomVector(bool if3D=true);

	private:
		Vector<T> center;
		T radius;
		T xmin, xmax, ymin, ymax, zmin, zmax;
	};
}

#endif
