#include "utils/Bounds.h"
#include "utils/Random.h"

namespace sag {
	template <typename T>
	bool Bounds<T>::contains(const Vector<T> &v) {
		return (v.x >= xmin) &&
			   (v.x <= xmax) &&
			   (v.y >= ymin) &&
			   (v.y <= ymax) &&
			   (v.z >= zmin) &&
			   (v.z <= zmax);
	}

	template <typename T>
	Vector<T> Bounds<T>::getRandomVector(bool if3D) {
		return Vector<T>(Random<T>::get().inRange(xmin, xmax),
						 Random<T>::get().inRange(ymin, ymax),
						 (if3D) ? Random<T>::get().inRange(zmin, zmax) : 0);
	}
}
