#ifndef SAG_RANGE_H
#define SAG_RANGE_H

namespace sag {
    template <typename T>
    class Range {
    public:
        Range(): from(0), to(1) {}
        Range(T to): from(0), to(to) {}
        Range(T from, T to): from(from), to(to) {}
        
        inline T min() const { return from; }
        inline T max() const { return to; }
        
        inline bool contains(T num) const { return (num >= from) && (num <= to); }
    private:
        T from, to;
    };
}

#endif