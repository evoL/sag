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
        delete[] buffer;
    }
    
    void PixbufImage::toFile(std::string filename) {
        // TODO: implement support for other image formats
        
        pixbuf->save(filename, "png");
    }
    
    void PixbufImage::drawGrid(Grid& g) {
        std::vector<int> values = g.map();
        
        int idx = 0;
        for (auto it = values.begin(); it < values.end(); it++) {
            buffer[idx]   = *it;
            buffer[idx+1] = *it;
            buffer[idx+2] = *it;
            
            idx += 3;
        }
    }
    
    void PixbufImage::setPixel(unsigned int x, unsigned int y, char r, char g, char b) {
        int index = y * stride + x * 3;
        
        buffer[index]   = r;
        buffer[index+1] = g;
        buffer[index+2] = b;
    }
}
