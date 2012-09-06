#ifndef SAG_PIXBUF_IMAGE_H
#define SAG_PIXBUF_IMAGE_H

#include <gdkmm/pixbuf.h>
#include "Image.h"
#include "utils/Grid.h"

namespace sag {
    /**
     * @brief Represents an Image using a Gdk::Pixbuf.
     */
    class PixbufImage : public Image {        
        unsigned char *buffer;
        Glib::RefPtr<Gdk::Pixbuf> pixbuf;
        int stride;
        
    public:
        PixbufImage(unsigned int width, unsigned int height);
        virtual ~PixbufImage();
        
        virtual void toFile(std::string filename);
        
        virtual void clear();
        
        virtual void blur(int radius);
        
        virtual void drawData(const std::vector<int>& values);
        
        virtual void compositeData(const std::vector<int>& values, CompositeType type);
        
        virtual void setPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b);
        
        /**
         * @brief Returns the pixbuf.
         *
         * @returns A Glib::RefPtr to the pixbuf.
         */
        const Glib::RefPtr<Gdk::Pixbuf> getPixbuf() { return pixbuf; }
    };
}

#endif
