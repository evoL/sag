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

        inline Vector<T> operator+(const Vector<T>& v) const {
            return Vector<T>(x + v.x, y + v.y, z + v.z);
        }
        
		inline Vector<T>& operator+=(const Vector<T>& v) {
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}
        
        inline Vector<T> operator-(const Vector<T>& v) const {
            return Vector<T>(x - v.x, y - v.y, z - v.z);
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

		inline const T& operator[](int id) const {
			switch (id) {
			case 0:
				return x;
			case 1:
				return y;
			case 2:
				return z;
			default:
				throw "Illegal access to Vector";
			}
		}
        
		inline number length() const {
			return sqrt(x*x + y*y + z*z);
		}

		inline number distance(const Vector<T>& v) const {
			return Vector<T>(v.x-x, v.y-y, v.z-z).length();
		}
        
        inline Vector<T>& reset(const T x2, const T y2, const T z2 = 0) {
            x = x2;
            y = y2;
            z = z2;
            
            return *this;
        }
	};
}

#endif
