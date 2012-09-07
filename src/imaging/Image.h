#ifndef SAG_IMAGE
#define SAG_IMAGE

#include <string>
#include <vector>

namespace sag {
    /**
     * @brief Provides facilities to work with images.
     */
    class Image {
    protected:
        unsigned int width, height;
    public:
        /**
         * @brief Image compositing types.
         */
        enum CompositeType {
            COMPOSITE_ADD
        };
        
        /**
         * @brief Constructs an image of specified size.
         *
         * @param width The desired width of the image.
         * @param height The desired height of the image.
         */
        Image(unsigned int width, unsigned int height): width(width), height(height) {}
        
        /**
         * @brief Saves the image to a file.
         *
         * @param filename The file name.
         */
        virtual void toFile(std::string filename) = 0;
        
        /**
         * @brief Clears the image.
         */
        virtual void clear() = 0;
        
        /**
         * @brief Blurs the image.
         *
         * @param radius The blur radius.
         */
        virtual void blur(int radius) = 0;
        
        /**
         * @brief Replaces the image with the data.
         *
         * @param The data to be replaced with.
         */
        virtual void drawData(const std::vector<int>& values) = 0;
        
        /**
         * @brief Composes the data on the image.
         *
         * @param values The data to compose.
         * @param type Determines how to compose the data.
         */
        virtual void compositeData(const std::vector<int>& values, CompositeType type) = 0;
        
        /**
         * @brief Sets a pixel to a color.
         *
         * @param x The horizontal coordinate of the pixel.
         * @param y The vertical coordinate of the pixel.
         * @param r The red component of the color.
         * @param g The green component of the color.
         * @param b The blue component of the color.
         */
        virtual void setPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) = 0;
        
        /**
         * @brief Returns the image width.
         *
         * @returns The image width.
         */
        unsigned int getWidth() { return width; }
        
        /**
         * @brief Returns the image height.
         *
         * @returns The image height.
         */
        unsigned int getHeight() { return height; }
    };
}

#endif