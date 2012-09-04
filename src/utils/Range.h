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
         * @brief Bottom boundary of the range.
         *
         * @returns Beginning of the range.
         */
        inline T min() const { return from; }

        /**
         * @brief Top boundary of the range.
         *
         * @returns End of the range.
         */
        inline T max() const { return to; }
        
        /**
         * @brief Checks if the range contains given value.
         *
         * @param num The value to be checked.
         *
         * @returns True if the range contains the given value.
         */
        inline bool contains(T num) const { return (num >= from) && (num <= to); }
    private:
        T from, to;
    };
}

#endif
