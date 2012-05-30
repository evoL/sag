#ifndef SAG_TYPES_H
#define SAG_TYPES_H

#include <stdexcept>

/**
 * @brief The floating-point number type, on which all computations are made.
 */
typedef float number;

namespace sag {
    class ParameterLengthException : public std::length_error {
    public:
        ParameterLengthException(const char msg[]): std::length_error(msg) {}
    };
}

#endif