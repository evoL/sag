#include <vector>
#include "utils/Random.h"
#include "utils/Bounds.h"

namespace sag {
	template <typename T>
	Bounds<T>::Bounds(std::vector<Vector<T>>& particles) {
		if (particles.empty()) {
			center = Vector<T>();
			radius = 1;
			xmin = ymin = zmin = -1;
			xmax = ymax = zmax = 1;
			return;
		}

		Vector<T> avg;
		for (std::vector<Vector<T>>::iterator it = particles.begin(); it<particles.end(); it++)
			avg += *it;

		avg /= particles.size();
		center = avg;

		number distance, maxDistance = 0;
		for (std::vector<Vector<T>>::iterator it = particles.begin(); it<particles.end(); it++) {
			distance = center.distance(*it);
			if (distance > maxDistance) maxDistance = distance;
		}

		radius = (T)maxDistance;
		xmin = center.x - radius;
		xmax = center.x + radius;
		ymin = center.y - radius;
		ymax = center.y + radius;
		zmin = center.z - radius;
		zmax = center.z + radius;
	}

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
