#ifndef SAG_PIXBUFRENDERER_H
#define SAG_PIXBUFRENDERER_H

#include <gdkmm/pixbuf.h>
#include "imaging/PixbufImage.h"
#include "rendering/Renderer.h"
#include "utils/Particle.h"
#include "utils/Grid.h"
#include "utils/Color.h"

namespace sag {
    class PixbufRenderer : public Renderer {
    public:
        PixbufRenderer():
            Renderer(),
            positionGrid(512, 512),
            velocityGrid(512, 512),
            accelerationGrid(512, 512),
            img(512, 512),
            color(255, 0, 0),
            colorShiftLevel(0.25),
            blur(true)
        {}
        
        PixbufRenderer(int w, int h):
            Renderer(),
            positionGrid(w, h),
            velocityGrid(w, h),
            accelerationGrid(w, h),
            img(w, h),
            color(255, 0, 0),
            colorShiftLevel(0.25),
            blur(true)
        {}
        
        void processParticle(Particle &p);
        
		void clear();
		void render();
        
        const Glib::RefPtr<Gdk::Pixbuf> getOutput() {
            return img.getPixbuf();
        }
        
        void setColor(Color& c) { color = c; }
        inline const Color& getColor() const { return color; }
        
        void setColorShiftLevel(double l) { colorShiftLevel = l; }
        inline const double getColorShiftLevel() const { return colorShiftLevel; }
        
        void setBlur(bool b) { blur = b; }
    private:
        Grid positionGrid;
        Grid velocityGrid;
        Grid accelerationGrid;
        PixbufImage img;
		
		void getParticles();
        
        Color color;
        double colorShiftLevel;
        bool blur;
    };
}

#endif
