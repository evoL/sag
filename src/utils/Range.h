#ifndef SAG_RANGE_H
#define SAG_RANGE_H

namespace sag {
    /**
     * @brief Represents a range.
     */
	template <typename T>
    class Range {
    public:
        /**
         * @brief Default constructor. Sets the range from 0 to 1.
         */
		Range(): from(0), to(1) {}

		/**
		 * @brief Constructor. Sets the range from 0 to the given value.
		 *
		 * @param to The end of the range.
		 */
        Range(T to): from(0), to(to) {}

        /**
         * @brief Constructor. Sets the range between the given values.
         *
         * @param from The beginning of the range.
         * @param to The end of the range.
         */
        Range(T from, T to): from(from), to(to) {}
        
        /**
         * @brief Returns the beginning of the range.
         */
        inline T min() const { return from; }

        /**
         * @brief Returns the end of the range.
         */
        inline T max() const { return to; }
        
        /**
         * @brief Returs true if the range contains the given value.
         *
         * @param num The value to be checked.
         */
        inline bool contains(T num) const { return (num >= from) && (num <= to); }
    private:
        T from, to;
    };
}

#endif
