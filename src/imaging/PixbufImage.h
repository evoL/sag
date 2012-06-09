#ifndef SAG_PIXBUF_IMAGE_H
#define SAG_PIXBUF_IMAGE_H

#include <gdk-pixbuf/gdk-pixbuf.h>
#include "Image.h"

namespace sag {
    class PixbufImage : public Image {
        GdkPixbuf *pixbuf;
    public:
        PixbufImage(unsigned int width, unsigned int height);
        
        virtual void toFile(std::string filename);
    };
}

#endif