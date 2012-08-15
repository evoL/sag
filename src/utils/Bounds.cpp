#include <vector>
#include "utils/Random.h"
#include "utils/Bounds.h"

namespace sag {
	template <typename T>
	Bounds<T>::Bounds(std::vector<Vector<T>>& particles) {
		if (particles.empty()) {
			center = Vector<T>();
			radius = 1;
			raw.xmin = raw.ymin = raw.zmin = -1;
			raw.xmax = raw.ymax = raw.zmax = 1;
			return;
		}

		Vector<T> avg;
		for (auto it = particles.begin(); it<particles.end(); it++)
			avg += *it;

		avg /= particles.size();
		center = avg;

		number distance, maxDistance = 0;
		for (auto it = particles.begin(); it<particles.end(); it++) {
			distance = center.distance(*it);
			if (distance > maxDistance) maxDistance = distance;
		}

		radius = (T)maxDistance;
		raw.xmin = center.x - radius;
		raw.xmax = center.x + radius;
		raw.ymin = center.y - radius;
		raw.ymax = center.y + radius;
		raw.zmin = center.z - radius;
		raw.zmax = center.z + radius;
	}

	template <typename T>
	bool Bounds<T>::contains(const Vector<T> &v) {
		return (v.x >= raw.xmin) &&
			   (v.x <= raw.xmax) &&
			   (v.y >= raw.ymin) &&
			   (v.y <= raw.ymax) &&
			   (v.z >= raw.zmin) &&
			   (v.z <= raw.zmax);
	}

	template <typename T>
	Vector<T> Bounds<T>::getRandomVector(bool if3D) {
		return Vector<T>(Random<T>::get().inRange(raw.xmin, raw.xmax),
						 Random<T>::get().inRange(raw.ymin, raw.ymax),
						 (if3D) ? Random<T>::get().inRange(raw.zmin, raw.zmax) : 0);
	}
    
    template <typename T>
    typename Bounds<T>::Raw Bounds<T>::getRawBounds() { return raw; }
    
    template Bounds<number>::Bounds(std::vector<Vector<number>>& particles);
    template Vector<number> Bounds<number>::getRandomVector(bool);
    template Bounds<number>::Raw Bounds<number>::getRawBounds();
}
