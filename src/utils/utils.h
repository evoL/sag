#ifndef SAG_UTILS_H
#define SAG_UTILS_H

#include <cstdlib>
#include "types.h"

/**
 * @brief Returns a random number between min and max.
 *
 * @param min The beginning of the range.
 * @param max The end of the range.
 */
inline number randRange(number min, number max) {
    return ((number)rand() / RAND_MAX) * (max - min) + min;
}

#endif