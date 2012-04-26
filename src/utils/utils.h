#ifndef SAG_UTILS_H
#define SAG_UTILS_H

#include <cstdlib>

/**
 * @brief Returns a random number between min and max.
 *
 * @param min The beginning of the range.
 * @param max The end of the range.
 */
inline float randRange(float min, float max) {
    return ((float)rand() / RAND_MAX) * (max - min) + min;
}

#endif