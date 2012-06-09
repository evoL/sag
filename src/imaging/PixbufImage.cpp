#include "PixbufImage.h"
#include "utils/types.h"

namespace sag {
    PixbufImage::PixbufImage(unsigned int width, unsigned int height): Image(width, height) {
        pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, width, height);
    }
    
    void PixbufImage::toFile(std::string filename) {
        // TODO: implement support for other image formats

        GError *error = nullptr;
        
        if (!gdk_pixbuf_save(pixbuf, filename.c_str(), "png", &error, NULL)) {
            throw FileIOException(error->message);
        }
    }
}