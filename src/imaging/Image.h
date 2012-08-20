#ifndef SAG_IMAGE
#define SAG_IMAGE

#include <string>
#include <vector>

namespace sag {
    class Image {
    protected:
        unsigned int width, height;
    public:
        Image(unsigned int width, unsigned int height): width(width), height(height) {}
        
        virtual void toFile(std::string filename) = 0;
        
        virtual void clear() = 0;
        virtual void resize(unsigned int w, unsigned int h) = 0;
        
        virtual void drawData(const std::vector<int>& values) = 0;
        
        virtual void setPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) = 0;
        
        unsigned int getWidth() { return width; }
        unsigned int getHeight() { return height; }
    };
}

#endif