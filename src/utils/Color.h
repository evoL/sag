#ifndef SAG_COLOR_H
#define SAG_COLOR_H

#include <algorithm>

namespace sag {
    /**
     * @brief Represents color in RGB or HSL format
     */
	class Color {
    public:
        /**
         * @brief Default constructor
         *
         * Creates black color.
         */
		Color(): r(0), g(0), b(0), h(0), s(0), l(0) {};

		/**
		 * @brief Constructor
		 *
		 * Creates color using RGB values in range of 0-255
		 *
		 * @param r Red component value
		 * @param g Green component value
		 * @param b Blue component value
		 */
        Color(int r, int g, int b);
        
        /**
         * @brief Returns red component value in range of 0-255
         *
         * @returns Red component in range of 0-255
         */
        inline unsigned char red() const   { return r; }

        /**
		 * @brief Returns green component value in range of 0-255
		 *
		 * @returns Green component in range of 0-255
		 */
        inline unsigned char green() const { return g; }

        /**
		 * @brief Returns blue component value in range of 0-255
		 *
		 * @returns Blue component in range of 0-255
		 */
        inline unsigned char blue() const  { return b; }

        /**
         * @brief Returns the hue of the color in range of 0-1
         *
         * @returns Hue in range of 0-1.
         */
        inline double hue() const          { return h; }
        /**
		 * @brief Returns the saturation of the color in range of 0-1
		 *
		 * @returns Saturation in range of 0-1
		 */
        inline double saturation() const   { return s; }
        /**
		 * @brief Returns the lightness of the color in range of 0-1
		 *
		 * @returns Saturation in range of 0-1
		 */
        inline double lightness() const    { return l; }
        
        /**
         * @brief Sets the red component
         *
         * @param v Red component
         */
        inline void red(unsigned char v)   { r = v; updateHSL(); }
        /**
		 * @brief Sets the green component
		 *
		 * @param v Green component
		 */
        inline void green(unsigned char v) { g = v; updateHSL(); }
        /**
		 * @brief Sets the blue component
		 *
		 * @param v Blue component
		 */
        inline void blue(unsigned char v)  { b = v; updateHSL(); }
        /**
		 * @brief Sets the hue
		 *
		 * @param v Hue
		 */
        inline void hue(double v)          { h = v; updateRGB(); }
        /**
		 * @brief Sets the saturation
		 *
		 * @param Saturation
		 */
        inline void saturation(double v)   { s = v; updateRGB();}
        /**
		 * @brief Sets the lightness
		 *
		 * @param v Lightness
		 */
        inline void lightness(double v)    { l = v; updateRGB();}
        
        /**
         * @brief Creates color from HSL values
         *
         * @param h Hue
         * @param s Saturation
         * @param l Lightness
         *
         * @returns Desired color
         */
        static Color fromHSL(double h, double s, double l);
    private:
        unsigned char r, g, b;
        double h, s, l;
        
        /**
         * @brief Directly sets all the class fields.
         *
         * For internal use only.
         *
         * @param r Red component
         * @param g Green component
         * @param b Blue component
         * @param h Hue
         * @param s Saturation
         * @param l Lightness
         */
        Color(unsigned char r, unsigned char g, unsigned char b,
              double h, double s, double l):
        r(r), g(g), b(b), h(h), s(s), l(l) {}
        
        /**
         * @brief Helper function
         */
        static double hue2rgb(double p, double q, double t);
        
        /**
         * @brief Updates RGB from HSL values
         */
        void updateRGB();

        /**
         * @brief Updates HSL from RGB values
         */
        void updateHSL();
    };
}

#endif
