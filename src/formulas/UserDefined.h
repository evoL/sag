#ifndef USERDEFINED_H
#define USERDEFINED_H

#include "formulas/Formula.h"
#include <vector>
#include <string>
#include "generation/CustomDistribution.h"

namespace sag {
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

		bool set(std::vector<std::string> formulas, int paramCount, CustomDistribution& distribution, std::string fname);

	protected:
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

			bool tokenize(std::string in);

			std::vector<Token> getTokens();

		private:
			void pushToken(Tokens t, number n=0);

			std::vector<Token> tokens;
			static constexpr number PI = 3.14159265359;
			static constexpr number E = 2.71828182846;
		};

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

			bool parse(std::vector<Lexer::Token>& tokens);

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
        
        bool validateRPN(std::vector<Parser::Elem>& rpn);

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
