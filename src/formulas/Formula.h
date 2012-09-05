#ifndef FORMULA_H
#define FORMULA_H

#define CLONEABLE(className) \
	virtual Formula* clone() const { \
		return new className(*this); \
	}

#include <vector>
#include <string>
#include "utils/types.h"
#include "utils/Vector.h"
#include "generation/ParamDistribution.h"
namespace sag {
	/**
	 * @brief Abstract class that represents formula
	 */
	class Formula {
	public:
		/**
		 * @brief Default constructor
		 */
		Formula() {}
		
		/**
		 * @brief Constructor
		 *
		 * Sets additionally given parameters
		 *
		 * @param parameters Parameters to be set
		 */
		Formula(const std::vector<number>& parameters):
            parameters(parameters) {}

		/**
		 * @brief Destructor
		 */
		virtual ~Formula() {}

        /**
         * @brief Ensures that parameters are set
         */
		void prepare();

		/**
		 * @brief Randomizes parameters
		 */
        void randomize();
        
		/**
		 * @brief Calculates new position of the particle
		 *
		 * @param prev Previous particle position
		 *
		 * @returns New particle position
		 */
        Vector<number> step(const Vector<number>& prev);

        /**
         * @ brief Pure virtual method. Calculates new position of the particle taking passed parameters into account
         *
         * @param prev Previous particle position
         * @param params Parameters
         *
         * @returns New particle position
         */
        virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params) = 0;
        
        /**
         * @brief Returns start point
         *
         * @returns Start point
         */
        inline Vector<number> getStartPoint() const { return startPoint; }

        /**
         * @brief Returns actual parameters
         *
         * @returns Parameters
         */
        inline const std::vector<number>& getParameters() const { return parameters; }
        
        /**
         * @brief Pure virtual method. Returns formula name.
         *
         * @returns Name
         */
        virtual const std::string name() const = 0;

        /**
         * @brief Checks if the formula works in 3-dimensional Euclidean space.
         *
         * @returns True if formula is 3D.
         */
        virtual inline bool is3D() const { return false; }

        /**
         * @brief Returns number of parameters needed to calculate formula
         *
         * @returns Number of parameters
         */
        virtual inline int paramCount() const { return 0; }

        /**
         * @brief Returns distribution of parameters.
         *
         * @returns Distribution
         */
        virtual const ParamDistribution& getDistribution() const = 0;

        /**
         * @brief Pure virtual method. Clones formula.
         *
         * @returns Pointer to the cloned formula.
         */
        virtual Formula* clone() const = 0;
        
	protected:
		static const int MAXITER = 5000;
		std::vector<number> parameters;
        Vector<number> startPoint;
        
		/**
		 * @brief Verifies if formula with provided parameters is sufficiently chaotic.
		 *
		 * @param params Parameters
		 *
		 * @returns True if it is chaotic
		 */
        bool verifyParams(const std::vector<number>& params);
	};
}

#endif
