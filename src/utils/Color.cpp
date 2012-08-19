#include "utils/Color.h"

namespace sag {
    Color::Color(int er, int gie, int be) {
        if (er < 0) er = 0;
        else if (er > 255) er = 255;
        
        if (gie < 0) gie = 0;
        else if (gie > 255) gie = 255;
        
        if (be < 0) be = 0;
        else if (be > 255) be = 255;
        
        r = er;
        g = gie;
        b = be;
    }
    
    Color Color::fromHSL(double h, double s, double l) {
        // The color can be achromatic, that is, saturation == 0
        if (s == 0) return Color(l * 255, l * 255, l * 255);
        
        double q = (l <= 0.5) ? l*(1+s) : l+s-l*s;
        double p = 2*l-q;
        
        return Color(
                     hue2rgb(p, q, h+0.333333333) * 255,
                     hue2rgb(p, q, h) * 255,
                     hue2rgb(p, q, h-0.333333333) * 255
                     );
    }
    
    double Color::hue2rgb(double p, double q, double t) {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        
        if (t < 0.166666667) return p + (q - p) * 6 * t;
        if (t < 0.5) return q;
        if (t < 0.666666667) return p + (q - p) * (0.666666667 - t) * 6;
        return p;
    };
}