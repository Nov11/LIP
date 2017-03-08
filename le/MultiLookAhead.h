#pragma once
#include "Token.h"
#include "Lexer.h"
#include "MLHBuffer.h"
#include <unordered_map>

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
	bool check(std::string str);
private:
	using TT = Token::TokenType;
	Lexer l_;
	std::string str_;
	MLHBuffer buffer_;
	bool probing_ = true;
	void init();
	bool stat();
	bool assign();
	bool list();
	bool elements();
	bool element();
	std::unordered_map<int, int> listCache;
};

