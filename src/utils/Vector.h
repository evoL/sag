#ifndef VECTOR_H
#define VECTOR_H

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
	};
}

#endif
