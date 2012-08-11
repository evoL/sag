#ifndef SAG_RANGE_H
#define SAG_RANGE_H

namespace sag {
    template <typename T>
    class Range {
    public:
        Range(): from(0), to(1) {}
        Range(T to): from(0), to(to) {}
        Range(T from, T to): from(from), to(to) {}
        
        T min() { return from; }
        T max() { return to; }
        
        bool contains(T num) { return (num >= from) && (num <= to); }
    private:
        T from, to;
    };
}

#endif