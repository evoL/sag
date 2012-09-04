#ifndef SAG_COLOR_H
#define SAG_COLOR_H

#include <algorithm>

namespace sag {
    class Color {
    public:
        Color(): r(0), g(0), b(0), h(0), s(0), l(0) {};
        Color(int r, int g, int b);
        
        inline unsigned char red() const   { return r; }
        inline unsigned char green() const { return g; }
        inline unsigned char blue() const  { return b; }
        inline double hue() const          { return h; }
        inline double saturation() const   { return s; }
        inline double lightness() const    { return l; }
        
        inline void red(unsigned char v)   { r = v; updateHSL(); }
        inline void green(unsigned char v) { g = v; updateHSL(); }
        inline void blue(unsigned char v)  { b = v; updateHSL(); }
        inline void hue(double v)          { h = v; updateRGB(); }
        inline void saturation(double v)   { s = v; updateRGB();}
        inline void lightness(double v)    { l = v; updateRGB();}
        
        static Color fromHSL(double h, double s, double l);
    private:
        unsigned char r, g, b;
        double h, s, l;
        
        Color(unsigned char r, unsigned char g, unsigned char b,
              double h, double s, double l):
        r(r), g(g), b(b), h(h), s(s), l(l) {}
        
        static double hue2rgb(double p, double q, double t);
        
        void updateRGB();
        void updateHSL();
    };
}

#endif