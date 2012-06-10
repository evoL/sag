#include "Bounds.h"
#include "Random.h"
#include "types.h"

namespace sag {
    template <typename T>
    template <typename U>
    Bounds<T>& Bounds<T>::operator=(const Bounds<U>& b) {
        xmin = b.xmin;
        xmax = b.xmax;
        ymin = b.ymin;
        ymax = b.ymax;
        
        return *this;
    }
    
    template <typename T>
    bool Bounds<T>::contains(T x, T y) {
        return (x >= xmin) && (x <= xmax) && (y >= ymin) && (y <= ymax);
    }
    
    template <typename T>
    bool Bounds<T>::contains(Vector<T> v) {
        return contains(v.x, v.y);
    }
    
    template <typename T>
    Vector<T> Bounds<T>::getRandomVector() {
        return Vector<T>(Random<T>::get().inRange(xmin, xmax),
                         Random<T>::get().inRange(ymin, ymax));
    }
    
    template <typename T>
    template <typename U>
    Vector<U> Bounds<T>::convert(Vector<T> &v, Bounds<U> &b) {
        return Vector<U>((v.x - xmin) / (xmax-xmin) * (b.xmax-b.xmin) + b.xmin,
                         (v.y - ymin) / (ymax-ymin) * (b.ymax-b.ymin) + b.ymin);
    }
    
    ///////// BECAUSE OF LINKER ERRORS
    
    template Vector<number> Bounds<number>::getRandomVector();
    template Vector<int> Bounds<number>::convert(Vector<number> &v, Bounds<int> &b);
}