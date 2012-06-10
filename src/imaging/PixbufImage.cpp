#include "PixbufImage.h"
#include "utils/types.h"

namespace sag {
    PixbufImage::PixbufImage(unsigned int width, unsigned int height): Image(width, height) {
        // Create the image buffer
        int size = width * height * 3;
        buffer = new unsigned char[size];
        stride = width * 3 * sizeof(unsigned char);
        
        // Create the pixbuf
        pixbuf = gdk_pixbuf_new_from_data(const_cast<const unsigned char*>(buffer), GDK_COLORSPACE_RGB, FALSE, 8, width, height, stride, NULL, nullptr);
    }
    
    PixbufImage::~PixbufImage() {
        g_object_unref(pixbuf);
        delete[] buffer;
    }
    
    void PixbufImage::toFile(std::string filename) {
        // TODO: implement support for other image formats
        
        GError *error = nullptr;
        
        if (!gdk_pixbuf_save(pixbuf, filename.c_str(), "png", &error, NULL)) {
            throw FileIOException(error->message);
        }
    }
    
    void PixbufImage::setPixel(unsigned int x, unsigned int y, char r, char g, char b) {
        int index = y * stride + x * 3;
        
        buffer[index]   = r;
        buffer[index+1] = g;
        buffer[index+2] = b;
    }
}