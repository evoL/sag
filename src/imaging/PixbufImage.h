#ifndef SAG_PIXBUF_IMAGE_H
#define SAG_PIXBUF_IMAGE_H

#include <gdkmm/pixbuf.h>
#include "Image.h"
#include "utils/Grid.h"

namespace sag {
    class PixbufImage : public Image {        
        unsigned char *buffer;
        Glib::RefPtr<Gdk::Pixbuf> pixbuf;
        int stride;
        
    public:
        PixbufImage(unsigned int width, unsigned int height);
        virtual ~PixbufImage();
        
        virtual void toFile(std::string filename);
        
        virtual void clear();
        virtual void resize(unsigned int w, unsigned int h);
        
        virtual void drawData(const std::vector<int>& values);
        
        virtual void setPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
        
        const Glib::RefPtr<Gdk::Pixbuf> getPixbuf() { return pixbuf; }
    };
}

#endif
