#include "PixbufImage.h"
#include "utils/types.h"

namespace sag {
    PixbufImage::PixbufImage(unsigned int width, unsigned int height): Image(width, height) {
        // Create the image buffer
        int size = width * height * 3;
        buffer = new unsigned char[size];
    }
    
    PixbufImage::~PixbufImage() {
        delete[] buffer;
    }
    
    void PixbufImage::toFile(std::string filename) {
        // TODO: implement support for other image formats
        
        // Create the pixbuf
        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_data(const_cast<const unsigned char*>(buffer), GDK_COLORSPACE_RGB, FALSE, 8, width, height, width * 3 * sizeof(unsigned char), NULL, nullptr);
        
        GError *error = nullptr;
        
        if (!gdk_pixbuf_save(pixbuf, filename.c_str(), "png", &error, NULL)) {
            throw FileIOException(error->message);
        }
        
        g_object_unref(pixbuf);
    }
}