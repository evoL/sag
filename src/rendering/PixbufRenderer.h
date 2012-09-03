#ifndef SAG_PIXBUFRENDERER_H
#define SAG_PIXBUFRENDERER_H

#include <gdkmm/pixbuf.h>
#include <string>
#include "imaging/PixbufImage.h"
#include "rendering/Renderer.h"
#include "utils/Particle.h"
#include "utils/Grid.h"
#include <string>

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
        
        std::string serialize() const;
        
        void processParticle(Particle &p);
        
		void clear();
		void render();
        
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
