#ifndef SAG_PIXBUFRENDERER_H
#define SAG_PIXBUFRENDERER_H

#include <gdkmm/pixbuf.h>
#include "imaging/PixbufImage.h"
#include "rendering/Renderer.h"
#include "utils/Particle.h"
#include "utils/Grid.h"
#include "utils/Color.h"

namespace sag {
    /**
     * @brief Renders an image to a Gdk::Pixbuf.
     *
     * This is an accumulation renderer. That means that it stores how many particles
     * it received on a Grid. That information is then used to draw "trails" of particles.
     *
     * It features coloring based on the velocity and acceleration of the particles,
     * allowing for color shifts and creating that distinctive glowing effect.
     *
     * It also allows to use antialiasing and compositing the blurred image to enhance
     * the visual quality of the picture.
     */
    class PixbufRenderer : public Renderer {
    public:
        /**
         * @brief Constructs a default PixbufRenderer.
         */
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
        
        /**
         * @brief Constructs a PixbufRenderer of specified size.
         *
         * @param w Width of the image
         * @param h Height of the image
         */
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
        
        /**
         * @brief Adds a particle to the grids.
         *
         * @param p The particle.
         */
        void processParticle(Particle &p);
        
        /**
         * @brief Clears the image and grids.
         */
		void clear();
        
        /**
         * @brief Draws the data from the grids to the image.
         */
		void render();
        
        /**
         * @brief Returns the pixbuf.
         *
         * @returns A Glib::RefPtr to the pixbuf.
         */
        const Glib::RefPtr<Gdk::Pixbuf> getOutput() {
            return img.getPixbuf();
        }
        
        /**
         * @brief Saves the image to a file.
         *
         * @param filename The file name
         */
        void saveImage(std::string filename);
        
        /**
         * @brief Sets the base color of the attractor.
         *
         * @param c A color.
         */
        void setColor(Color& c) { color = c; }
        
        /**
         * @brief Gets the base color.
         *
         * @returns The base color.
         */
        inline const Color& getColor() const { return color; }
        
        /**
         * @brief Sets how much the color is allowed to shift.
         *
         * @param l The color shift level in range of 0 to 1.
         */
        void setColorShiftLevel(double l) { colorShiftLevel = l; }
        
        /**
         * @brief Gets the color shift level.
         *
         * @returns The color shift level in range of 0 to 1.
         */
        inline const double getColorShiftLevel() const { return colorShiftLevel; }
        
        /**
         * @brief Sets whether the renderer should composite the result with a blurred image.
         *
         * @param b True, when you want to enable compositing. Otherwise false.
         */
        void setBlur(bool b) { blur = b; }
        
        /**
         * @brief Sets whether lines should be antialiased (smooth).
         *
         * @param aa True if you like smooth lines. False if you like jagged lines.
         */
        void setAntialias(bool aa);
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
