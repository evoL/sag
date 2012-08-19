#ifndef SAG_COLOR_H
#define SAG_COLOR_H

namespace sag {
    class Color {
    public:
        unsigned char r, g, b;
        
        Color(): r(0), g(0), b(0) {};
        Color(int r, int g, int b);
        
        static Color fromHSL(double h, double s, double l);
    private:
        static double hue2rgb(double p, double q, double t);
    };
}

#endif