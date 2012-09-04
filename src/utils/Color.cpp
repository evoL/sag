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
        
        updateHSL();
    }
    
    Color Color::fromHSL(double h, double s, double l) {
        // The color can be achromatic, that is, saturation == 0
        if (s == 0) return Color(l * 255, l * 255, l * 255);
        
        double q = (l <= 0.5) ? l*(1+s) : l+s-l*s;
        double p = 2*l-q;
        
        return Color(
                     hue2rgb(p, q, h+0.333333333) * 255,
                     hue2rgb(p, q, h) * 255,
                     hue2rgb(p, q, h-0.333333333) * 255,
                     h,
                     s,
                     l
                     );
    }
    
    double Color::hue2rgb(double p, double q, double t) {
        if (t < 0) t += 1;
        if (t > 1) t -= 1;
        
        if (t < 0.166666667) return p + (q - p) * 6 * t;
        if (t < 0.5) return q;
        if (t < 0.666666667) return p + (q - p) * (0.666666667 - t) * 6;
        return p;
    }
    
    void Color::updateRGB() {
        // The color can be achromatic, that is, saturation == 0
        if (s == 0) {
            r = l * 255;
            g = l * 255;
            b = l * 255;
            return;
        }
        
        double q = (l <= 0.5) ? l*(1+s) : l+s-l*s;
        double p = 2*l-q;
        
        r = hue2rgb(p, q, h+0.333333333) * 255;
        g = hue2rgb(p, q, h) * 255;
        b = hue2rgb(p, q, h-0.333333333) * 255;
    }
    
    void Color::updateHSL() {
        double rr = r / 255.0;
        double gg = g / 255.0;
        double bb = b / 255.0;
        double max = std::max(std::max(rr, gg), bb);
        double min = std::min(std::min(rr, gg), bb);
        
        l = (max - min) / 2;
        if (max == min) {
            // achromatic
            h = 0;
            s = 0;
        } else {
            double d = max - min;
            s = (l > 0.5) ? d / (2 - max - min) : d / (max + min);
            
            if (max == rr) h = (gg - bb) / d + (gg < bb ? 6 : 0);
            else if (max == gg) h = (bb - rr) / d + 2;
            else if (max == bb) h = (rr - gg) / d + 4;
            
            h /= 6;
        }
    }
}
