#ifndef USERDEFINED_H
#define USERDEFINED_H

#include "formulas/Formula.h"
#include <vector>
#include <string>
#include "generation/CustomDistribution.h"

namespace sag {
    /**
     * @brief A special kind of Formula that allows the user to use their own formula.
     */
	class UserDefined : public Formula {
	public:
		UserDefined(): Formula(), pc(0), _is3D(false), isSet(false) {}

		UserDefined(const std::vector<number>& parameters): Formula(parameters), pc(0), _is3D(false), isSet(false) {}

		virtual ~UserDefined() {}

		CLONEABLE(UserDefined)
		
		virtual Vector<number> step(const Vector<number>& prev, const std::vector<number> params);

		virtual const std::string name() const;
		virtual inline bool is3D() const;
		virtual inline int paramCount() const;
		virtual const ParamDistribution& getDistribution() const;

        /**
         * @brief Sets the formula as specified by the user.
         *
         * @param formulas Formulas for every coordinate.
         * @param paramCount How many parameters are there.
         * @param distribution The parameter distribution.
         * @param fname The formula name.
         *
         * @returns True, if the provided data is valid.
         */
		bool set(std::vector<std::string> formulas, int paramCount, CustomDistribution& distribution, std::string fname);
        
        /**
         * @brief Validates a single formula.
         *
         * @param formula The formula.
         * @param pc The formula's parameter count.
         */
        static bool validate(std::string formula, int pc);

	protected:
        
        /**
         * @brief The Lexer.
         */
		class Lexer {
		public:
			enum Tokens {
				OP_PLUS,
				OP_MINUS,
				OP_TIMES,
				OP_DIV,
				OP_MOD,
				OP_POW,
				L_PAREN,
				R_PAREN,
				ABS,
				SIN,
				COS,
				LOG,
				SQRT,
				PARAM,
				NUM,
				ARG_X,
				ARG_Y,
				ARG_Z,
				END
			};

			struct Token {
				Tokens t;
				number n;
			};

            /**
             * @brief Splits the formula into tokens.
             *
             * @param in The formula.
             *
             * @returns True, if there were no errors.
             */
			bool tokenize(std::string in);

            /**
             * @brief Returns the tokens.
             *
             * @returns A vector of tokens.
             */
			std::vector<Token> getTokens();

		private:
			void pushToken(Tokens t, number n=0);

			std::vector<Token> tokens;
			static constexpr number PI = 3.14159265359;
			static constexpr number E = 2.71828182846;
		};

        /**
         * @brief The Parser
         */
		class Parser {
		public:
			typedef double (*unary_function)(double);
			typedef double (*binary_function)(double, double);

			union Value {
				int i;
				number n;
				unary_function un_op;
				binary_function bin_op;
			};

			static inline double add(double a, double b) { return a+b; }
			static inline double sub(double a, double b) { return a-b; }
			static inline double mult(double a, double b) { return a*b; }
			static inline double div(double a, double b) { return a/b; }

			enum Type {
				UNARY_OPERATOR,
				BINARY_OPERATOR,
				PARAMETER,
				ARGUMENT,
				NUMBER
			};

			struct Elem {
				Type type;
				Value val;
			};

            /**
             * @brief Parses the tokens into Reverse Polish Notation.
             *
             * @param tokens A std::vector of Tokens
             *
             * @returns True, if there were no errors
             */
			bool parse(std::vector<Lexer::Token>& tokens);

            /**
             * @brief Returns the Reverse Polish Notation
             *
             * @returns The RPN.
             */
			std::vector<Elem> getRPN();

		private:
			std::vector<Elem> RPN;

			bool expression(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool expression(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& acc, std::vector<Elem>& res);

			bool summand(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool summand(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& acc, std::vector<Elem>& res);

			bool factor(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool factor(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& acc, std::vector<Elem>& res);

			bool power(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool application(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool atomicExpression(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool additiveOperator(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool multiplicativeOperator(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool powerOperator(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool applicativeOperator(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool leftParenthesis(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end);

			bool rightParenthesis(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end);

			bool parameter(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool num(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

			bool argument(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res);

		};
        
        static bool validateRPN(std::vector<Parser::Elem>& rpn, int pc);

		int pc;
		bool _is3D;
		bool isSet;
		CustomDistribution dstr;
		std::vector<std::vector<Parser::Elem>> RPN;
		std::string formulaName;
		std::vector<std::string> formulas;
	};
}

#endif
