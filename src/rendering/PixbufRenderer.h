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
        PixbufRenderer():
            Renderer(),
            positionGrid(512, 512),
            velocityGrid(512, 512),
            img(512, 512) {}
        
        PixbufRenderer(int w, int h):
            Renderer(),
            positionGrid(w, h),
            velocityGrid(w, h),
            img(w, h) {}
        
        void processParticle(Particle &p);
        
        void render();
        void clear();
        void resize(int w, int h);
        
        const Glib::RefPtr<Gdk::Pixbuf> getOutput() {
            return img.getPixbuf();
        }
    private:
        Grid positionGrid;
        Grid velocityGrid;
        PixbufImage img;
		
		void getParticles();
    };
}

#endif
