#include "PixbufImage.h"
#include "utils/types.h"

#include <vector>

namespace sag {
    PixbufImage::PixbufImage(unsigned int width, unsigned int height): Image(width, height) {
        // Create the image buffer
        int size = width * height * 3;
        buffer = new unsigned char[size];
        stride = width * 3 * sizeof(unsigned char);
        
        // Create the pixbuf
        pixbuf = Gdk::Pixbuf::create_from_data(const_cast<const unsigned char*>(buffer), Gdk::COLORSPACE_RGB, false, 8, width, height, stride);
    }
    
    PixbufImage::~PixbufImage() {
        pixbuf.reset();
        delete[] buffer;
    }
    
    void PixbufImage::toFile(std::string filename) {
        // TODO: implement support for other image formats
        
        pixbuf->save(filename, "png");
    }
    
    void PixbufImage::clear() {
        for (int i=width*height*3-1; i>=0; --i) {
            buffer[i] = 0;
        }
    }
    
    void PixbufImage::resize(unsigned int w, unsigned int h) {
        // TODO: perform an actual resize
        
        pixbuf.reset();
        delete[] buffer;
        
        width = w;
        height = h;
        
        int size = w * h * 3;
        
        buffer = new unsigned char[size];
        for (int i=size-1; i>=0; --i) buffer[i] = 0;
        
        stride = width * 3 * sizeof(unsigned char);
        
        pixbuf = Gdk::Pixbuf::create_from_data(const_cast<const unsigned char*>(buffer), Gdk::COLORSPACE_RGB, false, 8, width, height, stride);
    }
    
    void PixbufImage::drawData(const std::vector<int>& values) {
        int idx = 0;
        for (auto it = values.begin(); it < values.end(); it++) {
            buffer[idx++] = *it;
        }
    }
    
    void PixbufImage::setPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
        int index = y * stride + x * 3;
        
        buffer[index]   = r;
        buffer[index+1] = g;
        buffer[index+2] = b;
    }
}
