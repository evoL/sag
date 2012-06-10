#include "Vector.h"

#include <sstream>
#include "types.h"

namespace sag {
    template <typename T>
    Vector<T>::operator std::string() {
        std::ostringstream oss;

        oss << "Vector [";
        oss << x;
        oss << ", ";
        oss << y;
        oss << "]";

        return oss.str();
    }
    
    /////////////////////////////////////////////
    
    template <typename T>
    Vector<T>& Vector<T>::add(T x, T y) {
        this->x += x;
        this->y += y;
        
        return *this;
    }

    ///////// BECAUSE OF LINKER ERRORS
    
    template Vector<number>::operator std::string();
    template Vector<int>::operator std::string();
    
    template Vector<number>& Vector<number>::add(number x, number y);
    template Vector<int>& Vector<int>::add(int x, int y);
}