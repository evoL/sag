#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include "utils/types.h"

namespace sag {
	/**
	 * @brief Represents a single vector in 2- or 3-dimensional Euclidean space.
	 */
	template <typename T>
	class Vector {
	public:
		T x, y, z;

		/**
		 * @brief Default constructor. Initializes all coordinates with 0.
		 */
		Vector(): x(0), y(0), z(0) {}

		/**
		 * @brief Constructor.
		 *
		 * @param x The coordinate on the x-axis
		 * @param y The coordinate on the y-axis
		 * @param z (optional) The coordinate on the z-axis. By default set to 0.
		 */
		Vector(T x, T y, T z=0): x(x), y(y), z(z) {}

		/**
		 * @brief Copy constructor
		 *
		 * @param v Vector to be copied.
		 */
		Vector(Vector<T> const &v): x(v.x), y(v.y), z(v.z) {}

		/**
		 * @brief Destructor
		 */
		~Vector() {}

		/**
		 * @brief Operator of assignment.
		 *
		 * @param v Vector to be assigned.
		 *
		 * @returns This vector
		 */
		inline Vector<T>& operator=(const Vector<T>& v) {
			x = v.x;
			y = v.y;
			z = v.z;

			return *this;
		}

		/**
         * @brief Addition operator
         *
         * @param v The vector to be added.
         *
         * @returns A sum of this vector and the passed one.
         */
		inline Vector<T> operator+(const Vector<T>& v) const {
            return Vector<T>(x + v.x, y + v.y, z + v.z);
        }
        
		/**
		 * @brief In-place addition operator
		 *
		 * @param v The vector to be added.
		 *
		 * @returns A sum of this vector and the passed one.
		 */
		inline Vector<T>& operator+=(const Vector<T>& v) {
			x += v.x;
			y += v.y;
			z += v.z;

			return *this;
		}

		/**
		 * @brief Subtraction operator
		 *
		 * @param v The vector to be subtracted.
		 *
		 * @returns A result of subtraction of this vector and the passed one.
		 */
		inline Vector<T> operator-(const Vector<T>& v) const {
            return Vector<T>(x - v.x, y - v.y, z - v.z);
        }
        
		/**
		 * @brief In-place subtraction operator
		 *
		 * @param v The vector to be subtracted.
		 *
		 * @returns A result of subtraction of this vector and the passed one.
		 */
		inline Vector<T>& operator-=(const Vector<T>& v) {
			x -= v.x;
			y -= v.y;
			z -= v.z;

			return *this;
		}

		/**
		 * @brief In-place multiplication operator
		 *
		 * @param val The scalar the vector should be multiplied by.
		 *
		 * @returns A product of this vector and a scalar.
		 */
		inline Vector<T>& operator*=(const T val) {
			x *= val;
			y *= val;
			z *= val;

			return *this;
		}

		/**
		 * @brief In-place division operator
		 *
		 * @param val The scalar the vector should be divided by.
		 *
		 * @returns A quotient of this vector and a scalar.
		 */
		inline Vector<T>& operator/=(const T val) {
			x /= val;
			y /= val;
			z /= val;

			return *this;
		}

		/**
		 * @brief Returns coordinate by its index
		 *
		 * @param id Requested index
		 *
		 * @returns Requested coordinate
		 */
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
        
		/**
		 * @brief Returns the length of the vector
		 *
		 * @returns Length of vector
		 */
		inline number length() const {
			return sqrt(x*x + y*y + z*z);
		}

		/**
		 * @brief Returns the distance between this and the given vector.
		 *
		 * @param v Given vector
		 *
		 * @returns Requested distance
		 */
		inline number distance(const Vector<T>& v) const {
			return Vector<T>(v.x-x, v.y-y, v.z-z).length();
		}
        
        /**
         * @brief Resets the vector with the given parameters
         *
         * @param x The coordinate on the x-axis
		 * @param y The coordinate on the y-axis
		 * @param z (optional) The coordinate on the z-axis. by default set to 0.
		 *
		 * @returns Reset vector
         */
		inline Vector<T>& reset(const T x2, const T y2, const T z2 = 0) {
            x = x2;
            y = y2;
            z = z2;
            
            return *this;
        }
	};
}

#endif
