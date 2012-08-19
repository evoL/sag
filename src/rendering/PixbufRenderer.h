#ifndef SAG_PIXBUFRENDERER_H
#define SAG_PIXBUFRENDERER_H

#include <gdkmm/pixbuf.h>
#include "imaging/PixbufImage.h"
#include "rendering/Renderer.h"
#include "utils/Particle.h"
#include "utils/Grid.h"

namespace sag {
    class PixbufRenderer : public Renderer {
    public:
        PixbufRenderer(int w, int h):
            Renderer(),
            positionGrid(w, h),
            velocityGrid(w, h),
            img(w, h) {}
        
        virtual bool receiveParticle(const Particle& p);
        
        void render();
        
        const Glib::RefPtr<Gdk::Pixbuf> getOutput() {
            return img.getPixbuf();
        }
    private:
        Grid positionGrid;
        Grid velocityGrid;
        PixbufImage img;
    };
}

#endif
