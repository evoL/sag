#ifndef SAG_PIXBUF_IMAGE_H
#define SAG_PIXBUF_IMAGE_H

#include <gdk-pixbuf/gdk-pixbuf.h>
#include "Image.h"
#include "generation/Grid.h"

namespace sag {
    class PixbufImage : public Image {        
        unsigned char *buffer;
        GdkPixbuf *pixbuf;
        int stride;
        
    public:
        PixbufImage(unsigned int width, unsigned int height);
        ~PixbufImage();
        
        virtual void toFile(std::string filename);
        
        virtual void drawGrid(Grid& g);
        
        virtual void setPixel(unsigned int x, unsigned int y, char r, char g, char b);
    };
}

#endif