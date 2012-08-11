#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include "utils/types.h"

namespace sag {
	template <typename T>
	class Vector {
	public:
		T x, y, z;

		Vector(): x(0), y(0), z(0) {}

		Vector(T x, T y, T z=0): x(x), y(y), z(z) {}

		Vector(Vector<T> const &v): x(v.x), y(v.y), z(v.z) {}

		~Vector() {}

		inline Vector<T>& operator=(const Vector<T>& v) {
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		inline Vector<T>& operator+=(const Vector<T>& v) {
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		inline Vector<T>& operator-=(const Vector<T>& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		inline Vector<T>& operator*=(const T val) {
			x *= val;
			y *= val;
			z *= val;

			return *this;
		}

		inline Vector<T>& operator/=(const T val) {
			x /= val;
			y /= val;
			z /= val;

			return *this;
		}
		inline number length() {
			return sqrt(x*x + y*y + z*z);
		}

		inline number distance(const Vector<T>& v) {
			return Vector<T>(v.x-x, v.y-y, v.z-z).length();
		}
	};
}

#endif
