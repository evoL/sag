#ifndef SAG_IMAGE
#define SAG_IMAGE

#include <string>
#include "generation/Grid.h"

namespace sag {
    class Image {
    protected:
        unsigned int width, height;
    public:
        Image(unsigned int width, unsigned int height): width(width), height(height) {}
        
        virtual void toFile(std::string filename) = 0;
        
        virtual void drawGrid(Grid& g) = 0;
        
        virtual void setPixel(unsigned int x, unsigned int y, char r, char g, char b) = 0;
    };
}

#endif