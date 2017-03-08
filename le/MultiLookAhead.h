#pragma once
#include "Token.h"
#include "Lexer.h"
#include "MLHBuffer.h"

/**
stat	: list EOF | assign EOF;
assign	: list '=' list;
list	: '[' elements ']';
elements: element (',' element)*
element	: NAME '=' NAME | NAME | list;
*/
class MultiLookAhead
{
public:
	MultiLookAhead();
	~MultiLookAhead();
	bool check(std::string str) {
		str_ = str;
		init();
		return stat();
	}
private:
	using TT = Token::TokenType;
	Lexer l_;
	std::string str_;
	MLHBuffer buffer_;
	bool probing_ = true;
	void init() { l_.assignCotent(str_); l_.tokenize(); buffer_.prepare(); }
	bool stat() {
		bool result = false;
		buffer_.mark();
		result = list() && buffer_.matchType(TT::NONE);
		if (result) {
			return true;
		}
		else {
			buffer_.restore();
			result = assign() && buffer_.matchType(TT::NONE);
		}
		return result;
	}
	bool assign() {
		if (list()
			&& buffer_.matchType(TT::EQUAL)
			&& list()) {
			return true;
		}
		return false;
	}
	bool list() {
		if (buffer_.matchType(TT::LBRACKET)
			&& elements()
			&& buffer_.matchType(TT::RBRACKET))
			return true;
		return false;
	}
	bool elements() {
		if (!element())return false;
		while (buffer_.LAhead(TT::COMMA, 0)) {
			if (!(buffer_.matchType(TT::COMMA)
				&& element())) {
				return false;
			}
		}
		return true;
	}
	bool element() {
		if (buffer_.LAhead(TT::NAME, 0) && buffer_.LAhead(TT::EQUAL, 1)) {
			if (buffer_.matchType(TT::NAME)
				&&
				buffer_.matchType(TT::EQUAL)
				&&
				buffer_.matchType(TT::NAME)) {
				return true;
			}
		}
		else if (buffer_.LAhead(TT::NAME, 0)) {
			if (buffer_.matchType(TT::NAME)) {
				return true;
			}
		}
		else {
			if (list()) {
				return true;
			}
		}
		return false;
	}
};

