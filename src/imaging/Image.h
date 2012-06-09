#ifndef SAG_IMAGE
#define SAG_IMAGE

#include <string>

namespace sag {
    class Image {
    protected:
        unsigned int width, height;
    public:
        Image(unsigned int width, unsigned int height): width(width), height(height) {}
        
        virtual void toFile(std::string filename) = 0;
    };
}

#endif