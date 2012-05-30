#ifndef SAG_FORMULA_H
#define SAG_FORMULA_H

#include <vector>
#include "../utils/Vector.h"
#include "../utils/types.h"

namespace sag {
    
    /**
     * @brief Represents a formula.
     *
     * A formula is just a specific equation which can be set a range of
     * constants, called parameters. Each formula requires a specific amount
     * of parameters.
     */
    class Formula {
    public:        
        Formula() {} ///< Default constructor.
        
        /**
         * @brief Initializes a Formula using parameters from an array.
         *
         * @param count Number of parameters
         * @param params An array of parameters
         */
//        F/ormula(int count, number params[]);
        
        /**
         * @brief Initializes a Formula using a parameter vector.
         *
         * @param params A vector of parameters
         */
//        Formula(std::vector<number> params);*/
        
        /**
         * @brief Prepares the formula for calculation.
         *
         * This method should contain the code to validate parameters
         * if necessary.
         */
        virtual void prepare();
        
        /**
         * @brief Calculates the next vector.
         *
         * @params v The starting vector.
         */
        virtual Vector step(Vector& src) = 0;
        
        /**
         * @brief Sets up the parameters using an array
         *
         * @param count Number of parameters
         * @param params An array of parameters
         */
        void setParameters(int count, number params[]);
        
        /**
         * @brief Sets up the parameters using a vector
         *
         * @param params A vector of parameters
         */
        void setParameters(std::vector<number>& params);
        
    protected:
        /**
         * @brief The vector of parameters.
         */
        std::vector<number> parameters;
        
        /**
         * @brief Specifies how many parameters can the Formula take.
         *
         * Currently must be redefined for every Formula class.
         */
        int paramCount;
    };
}

#endif