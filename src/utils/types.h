#ifndef TYPES_H
#define TYPES_H

#include <stdexcept>

typedef float number;

namespace sag {
    class FileIOException : public std::runtime_error {
    public:
        FileIOException(const char msg[]): std::runtime_error(msg) {}
    };
}

#endif
