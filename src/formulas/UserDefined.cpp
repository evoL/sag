#include "formulas/UserDefined.h"
#include <cmath>
#include <stack>
#include <sstream>
#include "utils/Range.h"

namespace sag {
	Vector<number> UserDefined::step(const Vector<number>& prev, const std::vector<number> params) {
		std::vector<number> res;

		for (std::vector<std::vector<Parser::Elem>>::iterator formula = RPN.begin(); formula < RPN.end(); formula++) {
			std::stack<number> st;

			for (std::vector<Parser::Elem>::iterator it = formula->begin(); it < formula->end(); it++) {
				switch (it->type) {
				case Parser::NUMBER:
					st.push(it->val.n);
					break;
				case Parser::PARAMETER:
					st.push(params[it->val.i]);
					break;
				case Parser::ARGUMENT:
					st.push(prev[it->val.i]);
					break;
				case Parser::BINARY_OPERATOR:
					number arg1, arg2;
					arg1 = st.top();
					st.pop();
					arg2 = st.top();
					st.pop();
					st.push(it->val.bin_op(arg1, arg2));
					break;
				case Parser::UNARY_OPERATOR:
					number arg;
					arg = st.top();
					st.pop();
					st.push(it->val.un_op(arg));
					break;
				}
			}
			res.push_back(st.top());
			st.pop();
		}

		if (_is3D) return Vector<number>(res[0], res[1], res[2]);
		return Vector<number>(res[0], res[1]);
	}

	const std::string UserDefined::name() const {
		if (!isSet) throw "The formula has not been set up";
		return formulaName;
	}

	int UserDefined::paramCount() const {
		if (!isSet) throw "The formula has not been set up";
		return pc;
	}
	bool UserDefined::is3D() const {
		if (!isSet) throw "The formula has not been set up";
		return _is3D;
	}

	const ParamDistribution& UserDefined::getDistribution() const {
		if (!isSet) throw "The formula has not been set up";
		return dstr;
	}

	bool UserDefined::set(std::vector<std::string> formulas, int paramCount, CustomDistribution& distribution, std::string fname) {
		if (paramCount != distribution.paramCount()) return false;
		pc = paramCount;
		dstr = distribution;
		formulaName = fname;

		if (formulas.size() == 2) {
			_is3D = false;
		} else if (formulas.size() == 3) {
			_is3D = true;
		} else throw "Invalid number of formulas";

		RPN.clear();

		for (std::vector<std::string>::iterator it = formulas.begin(); it < formulas.end(); it++) {
			Lexer lex;
			if (!lex.tokenize(*it)) return false;

			std::vector<Lexer::Token> tokens = lex.getTokens();

			Parser parser;
			if (!parser.parse(tokens)) return false;

			RPN.push_back(parser.getRPN());

			if (!validateRPN(RPN.back())) {
				RPN.clear();
				return false;
			}
		}

		isSet = true;
		return true;
	}

	bool UserDefined::validateRPN(std::vector<Parser::Elem>& rpn) {
		Range<int> range(0, pc-1);
		for (std::vector<Parser::Elem>::iterator it = rpn.begin(); it < rpn.end(); it++) {
			if (it->type == Parser::PARAMETER && !range.contains(it->val.i)) return false;
		}
		return true;
	}

	bool UserDefined::Lexer::tokenize(std::string in) {

		tokens.clear();

		std::stringstream ss;
        ss.precision(18);
		ss << in;

		char c, _c;
		while (ss.get(c)) {
			switch (c) {
			case ' ':
			case '\t':
			case '\n':
				break;
			case '+':
				pushToken(OP_PLUS);
				break;
			case '-':
				pushToken(OP_MINUS);
				break;
			case '*':
				pushToken(OP_TIMES);
				break;
			case '/':
				pushToken(OP_DIV);
				break;
			case 'm':
				if (ss.get() == 'o')
					if (ss.get() == 'd') {
						pushToken(OP_MOD);
						break;
					}
				tokens.clear();
				return false;
			case '^':
				pushToken(OP_POW);
				break;
			case '(':
				pushToken(L_PAREN);
				break;
			case ')':
				pushToken(R_PAREN);
				break;
			case 'a':
				if (ss.get() == 'b')
					if (ss.get() == 's') {
						pushToken(ABS);
						break;
					}
				tokens.clear();
				return false;
			case 's':
				ss.get(_c);
				if (_c == 'i') {
					if (ss.get() == 'n') {
						pushToken(SIN);
						break;
					}
				} else if (_c == 'q')
					if (ss.get() == 'r')
						if (ss.get() == 't') {
							pushToken(SQRT);
							break;
						}
				tokens.clear();
				return false;
			case 'c':
				if (ss.get() == 'o')
					if (ss.get() == 's') {
						pushToken(COS);
						break;
					}
				tokens.clear();
				return false;
			case 'l':
				if (ss.get() == 'o')
					if (ss.get() == 'g') {
						pushToken(LOG);
						break;
					}
				tokens.clear();
				return false;
			case 'p':
				ss.get(_c);;
				if (_c == 'i') {
					pushToken(NUM, PI);
					break;
				} else if (std::isdigit(_c)) {
					ss.putback(_c);
					int n;
					ss >> n;
					pushToken(PARAM, n);
					break;
				}
				tokens.clear();
				return false;
			case 'e':
				pushToken(NUM, E);
				break;
			case 'x':
				pushToken(ARG_X);
				break;
			case 'y':
				pushToken(ARG_Y);
				break;
			case 'z':
				pushToken(ARG_Z);
				break;
			default:
				if (std::isdigit(c)) {
					ss.putback(c);
					number n;
					ss >> n;
					pushToken(NUM, n);
					break;
				}
				tokens.clear();
				return false;
			}
		}
		pushToken(END);
		return true;
	}
	std::vector<UserDefined::Lexer::Token> UserDefined::Lexer::getTokens() {
		return tokens;
	}

	void UserDefined::Lexer::pushToken(Tokens t, number n) {
		Token tok;

		tok.t = t;
		tok.n = n;

		tokens.push_back(tok);
	}

	bool UserDefined::Parser::parse(std::vector<UserDefined::Lexer::Token>& tokens) {
		RPN.clear();
		std::vector<Lexer::Token>::iterator end;
		bool res = expression(tokens.begin(), end, RPN);
		if (!(end == (tokens.end() - 1) && res)) {
			RPN.clear();
			return false;
		}
		return true;
	}

	std::vector<UserDefined::Parser::Elem> UserDefined::Parser::getRPN() {
		return RPN;
	}

	bool UserDefined::Parser::expression(std::vector<UserDefined::Lexer::Token>::iterator begin, std::vector<UserDefined::Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		std::vector<Lexer::Token>::iterator it;
		std::vector<Elem> res1;

		if (!(summand(begin, it, res1) && expression(it, end, res1, res))) return false;

		return true;
	}

	bool UserDefined::Parser::expression(std::vector<UserDefined::Lexer::Token>::iterator begin, std::vector<UserDefined::Lexer::Token>::iterator& end, std::vector<Elem>& acc, std::vector<Elem>& res) {
		std::vector<Lexer::Token>::iterator it1, it2;
		std::vector<Elem> res1, res2;

		if (additiveOperator(begin, it1, res1)) {
			if (!(summand(it1, it2, res2))) return false;
			acc.insert(acc.end(), res2.begin(), res2.end());
			acc.insert(acc.end(), res1.begin(), res1.end());
			if (!(expression(it2, end, acc, res))) return false;
		} else {
			res = acc;
			end = begin;
		}
		 return true;
	}

	bool UserDefined::Parser::summand(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		std::vector<Lexer::Token>::iterator it;
		std::vector<Elem> res1;

		if (!(factor(begin, it, res1) && summand(it, end, res1, res))) return false;

		return true;
	}

	bool UserDefined::Parser::summand(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& acc, std::vector<Elem>& res) {
		std::vector<Lexer::Token>::iterator it1, it2;
		std::vector<Elem> res1, res2;

		if (multiplicativeOperator(begin, it1, res1)) {
			if (!(factor(it1, it2, res2))) return false;
			acc.insert(acc.end(), res2.begin(), res2.end());
			acc.insert(acc.end(), res1.begin(), res1.end());
			if (!(summand(it2, end, acc, res))) return false;
		} else {
			res = acc;
			end = begin;
		}
		 return true;
	}

	bool UserDefined::Parser::factor(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		std::vector<Lexer::Token>::iterator it;
		std::vector<Elem> res1;

		if (!(power(begin, it, res1) && factor(it, end, res1, res))) return false;

		return true;
	}

	bool UserDefined::Parser::factor(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& acc, std::vector<Elem>& res) {
		std::vector<Lexer::Token>::iterator it1, it2;
		std::vector<Elem> res1, res2;

		if (powerOperator(begin, it1, res1)) {
			if (!(power(it1, it2, res2))) return false;
			acc.insert(acc.end(), res2.begin(), res2.end());
			acc.insert(acc.end(), res1.begin(), res1.end());
			if (!(factor(it2, end, acc, res))) return false;
		} else {
			res = acc;
			end = begin;
		}
		 return true;
	}

	bool UserDefined::Parser::power(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		std::vector<Lexer::Token>::iterator it1, it2;
		std::vector<Elem> res1, res2, res3;

		if (!(application(begin, it1, res1))) return false;

		if (!(powerOperator(it1, it2, res2))) {
			res = res1;
			end = it1;
		}
		else {
			if (!(power(it2, end, res3))) return false;
			res1.insert(res1.end(), res2.begin(), res2.end());
			res1.insert(res1.end(), res3.begin(), res3.end());
			res = res1;
		}
		return true;
	}

	bool UserDefined::Parser::application(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		std::vector<Lexer::Token>::iterator it;
		std::vector<Elem> res1, res2;

		if (applicativeOperator(begin, it, res1)) {
			if (!(atomicExpression(it, end, res2))) return false;
			res2.insert(res2.end(), res1.begin(), res1.end());
			res = res2;
		} else {
			if (!(atomicExpression(begin, end, res))) return false;
		}
		return true;
	}

	bool UserDefined::Parser::atomicExpression(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		std::vector<Lexer::Token>::iterator it1, it2;
		std::vector<Elem> res1;

		if (leftParenthesis(begin, it1)) {
			if (!(expression(it1, it2, res1))) return false;
			if (!(rightParenthesis(it2, end))) return false;
		} else if (parameter(begin, end, res1)) {}
		else if (argument(begin, end, res1)) {}
		else if (num(begin, end, res1)) {}
		else return false;

		res = res1;

		return true;
	}

	bool UserDefined::Parser::additiveOperator(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		Elem el;

		switch (begin->t) {
		case Lexer::OP_PLUS:
			el.type = BINARY_OPERATOR;
			el.val.bin_op = add;
			res.push_back(el);
			end = begin + 1;
			break;
		case Lexer::OP_MINUS:
			el.type = BINARY_OPERATOR;
			el.val.bin_op = sub;
			res.push_back(el);
			end = begin + 1;
			break;
		default:
			return false;
		}
		return true;
	}

	bool UserDefined::Parser::multiplicativeOperator(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		Elem el;

		switch (begin->t) {
		case Lexer::OP_TIMES:
			el.type = BINARY_OPERATOR;
			el.val.bin_op = mult;
			res.push_back(el);
			end = begin + 1;
			break;
		case Lexer::OP_DIV:
			el.type = BINARY_OPERATOR;
			el.val.bin_op = div;
			res.push_back(el);
			end = begin + 1;
			break;
		case Lexer::OP_MOD:
			el.type = BINARY_OPERATOR;
			el.val.bin_op = fmod;
			res.push_back(el);
			end = begin + 1;
			break;
		default:
			return false;
		}
		return true;
	}

	bool UserDefined::Parser::powerOperator(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		if (begin->t == Lexer::OP_POW) {
			Elem el;
			el.type = BINARY_OPERATOR;
			el.val.bin_op = pow;
			res.push_back(el);
			end = begin + 1;
			return true;
		}
		return false;
	}

	bool UserDefined::Parser::applicativeOperator(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		Elem el;

		switch (begin->t) {
		case Lexer::ABS:
			el.type = UNARY_OPERATOR;
            el.val.un_op = std::abs;
			res.push_back(el);
			end = begin + 1;
			break;
		case Lexer::SIN:
			el.type = UNARY_OPERATOR;
			el.val.un_op = sin;
			res.push_back(el);
			end = begin + 1;
			break;
		case Lexer::COS:
			el.type = UNARY_OPERATOR;
			el.val.un_op = cos;
			res.push_back(el);
			end = begin + 1;
			break;
		case Lexer::LOG:
			el.type = UNARY_OPERATOR;
			el.val.un_op = log;
			res.push_back(el);
			end = begin + 1;
			break;
		case Lexer::SQRT:
			el.type = UNARY_OPERATOR;
			el.val.un_op = sqrt;
			res.push_back(el);
			end = begin + 1;
			break;
		default:
			return false;
		}
		return true;
	}

	bool UserDefined::Parser::leftParenthesis(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end) {
		if (begin->t == Lexer::L_PAREN) {
			end = begin + 1;
			return true;
		}
		return false;
	}

	bool UserDefined::Parser::rightParenthesis(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end) {
		if (begin->t == Lexer::R_PAREN) {
			end = begin + 1;
			return true;
		}
		return false;
	}

	bool UserDefined::Parser::parameter(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		if (begin->t == Lexer::PARAM) {
			Elem el;
			el.type = PARAMETER;
			el.val.i = (int)begin->n;
			res.push_back(el);
			end = begin + 1;
			return true;
		}
		return false;
	}

	bool UserDefined::Parser::num(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		if (begin->t == Lexer::NUM) {
			Elem el;
			el.type = NUMBER;
			el.val.n = begin->n;
			res.push_back(el);
			end = begin + 1;
			return true;
		}
		return false;
	}

	bool UserDefined::Parser::argument(std::vector<Lexer::Token>::iterator begin, std::vector<Lexer::Token>::iterator& end, std::vector<Elem>& res) {
		Elem el;

		switch (begin->t) {
		case Lexer::ARG_X:
			el.type = ARGUMENT;
			el.val.i = 0;
			res.push_back(el);
			end = begin + 1;
			break;
		case Lexer::ARG_Y:
			el.type = ARGUMENT;
			el.val.i = 1;
			res.push_back(el);
			end = begin + 1;
			break;
		case Lexer::ARG_Z:
			el.type = ARGUMENT;
			el.val.i = 2;
			res.push_back(el);
			end = begin + 1;
			break;
		default:
			return false;
		}
		return true;
	}
}



