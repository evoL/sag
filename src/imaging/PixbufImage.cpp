#include "PixbufImage.h"
#include "utils/types.h"

#include <vector>

namespace sag {
    PixbufImage::PixbufImage(unsigned int width, unsigned int height): Image(width, height) {
        // Create the image buffer
        int size = width * height * 3;
        buffer = new unsigned char[size];
        stride = width * 3 * sizeof(unsigned char);
        
        // Create the pixbuf
        pixbuf = Gdk::Pixbuf::create_from_data(const_cast<const unsigned char*>(buffer), Gdk::COLORSPACE_RGB, false, 8, width, height, stride);
    }
    
    PixbufImage::~PixbufImage() {
        pixbuf.reset();
        delete[] buffer;
    }
    
    void PixbufImage::toFile(std::string filename) {
        // TODO: implement support for other image formats
        
        pixbuf->save(filename, "png");
    }
    
    void PixbufImage::clear() {
        for (int i=width*height*3-1; i>=0; --i) {
            buffer[i] = 0;
        }
    }
    
    // Box blur
    void PixbufImage::blur(int radius) {
        if (radius<1) return;
        
        int wm = width - 1;
        int hm = height - 1;
        int wh = width * height;
        int div = radius + radius + 1;
        
        unsigned char *r = new unsigned char[wh];
        unsigned char *g = new unsigned char[wh];
        unsigned char *b = new unsigned char[wh];
        
        int rsum, gsum, bsum, x, y, i, p, p1, p2, yp, yi, yw;
        
        int *vMIN = new int[MAX(width,height)];
        int *vMAX = new int[MAX(width,height)];
        
        unsigned char *dv = new unsigned char[256*div];
        for (i = 0; i < 256*div; i++) dv[i] = (i/div);
        
        yw = yi = 0;
        
        for (y = 0; y < (int)height; y++) {
            rsum = gsum = bsum = 0;
            for (i = -radius; i <= radius; i++) {
                p = (yi + MIN(wm, MAX(i,0))) * 3;
                rsum += buffer[p];
                gsum += buffer[p+1];
                bsum += buffer[p+2];
            }
            for (x = 0; x < (int)width; x++) {
                r[yi] = dv[rsum];
                g[yi] = dv[gsum];
                b[yi] = dv[bsum];
                
                if (y == 0) {
                    vMIN[x] = MIN(x + radius + 1, wm);
                    vMAX[x] = MAX(x - radius, 0);
                }
                p1 = (yw + vMIN[x]) * 3;
                p2 = (yw + vMAX[x]) * 3;
                
                rsum += buffer[p1] - buffer[p2];
                gsum += buffer[p1+1] - buffer[p2+1];
                bsum += buffer[p1+2] - buffer[p2+2];
                
                yi++;
            }
            yw += width;
        }
        
        for (x = 0; x < (int)width; x++) {
            rsum = gsum = bsum = 0;
            yp = -radius * width;
            for (i = -radius; i <= radius; i++) {
                yi = MAX(0, yp) + x;
                rsum += r[yi];
                gsum += g[yi];
                bsum += b[yi];
                yp += width;
            }
            
            yi = x;
            
            for (y = 0; y < (int)height; y++) {
                buffer[yi*3] = dv[rsum];
                buffer[yi*3 + 1] = dv[gsum];
                buffer[yi*3 + 2] = dv[bsum];
                if (x == 0) {
                    vMIN[y] = MIN(y + radius + 1, hm) * width;
                    vMAX[y] = MAX(y - radius, 0) * width;
                }
                p1 = x + vMIN[y];
                p2 = x + vMAX[y];
                
                rsum += r[p1] - r[p2];
                gsum += g[p1] - g[p2];
                bsum += b[p1] - b[p2];
                
                yi += width;
            }
        }
        
        delete r;
        delete g;
        delete b;
        
        delete vMIN;
        delete vMAX;
        delete dv;
    }
    
    void PixbufImage::drawData(const std::vector<int>& values) {
        int idx = 0;
        for (auto it = values.begin(); it < values.end(); it++) {
            buffer[idx++] = *it;
        }
    }
    
    void PixbufImage::compositeData(const std::vector<int>& values, CompositeType type) {
        int idx = 0;
        for (auto it = values.begin(); it < values.end(); it++) {
            switch (type) {
                case Image::COMPOSITE_ADD:
                    if ((int)buffer[idx] + *it > 255) buffer[idx++] = 255;
                    else buffer[idx++] += *it;
            }
        }
    }
    
    void PixbufImage::setPixel(unsigned int x, unsigned int y, unsigned char r, unsigned char g, unsigned char b) {
        int index = y * stride + x * 3;
        
        buffer[index]   = r;
        buffer[index+1] = g;
        buffer[index+2] = b;
    }
}
