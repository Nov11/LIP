#pragma once
#include "Lexer.h"
#include "RingBuffer.h"

/**
list	: '[' elements ']'
elements: element (',' element)*
element : NAME '=' NAME| NAME | list;
*/
class LL2Parser
{
public:
	LL2Parser(Lexer& l) : l_(l), buff_(BUFFERSIZE, l_) {}
	~LL2Parser();
	bool check(std::string str);
private:
	const static int BUFFERSIZE = 2;
	Lexer& l_;
	RingBuffer buff_;
	std::string str_;
	void elements();
	void element();
	void list();
	bool match(int position, Token::TokenType type);
	bool matchType(Token::TokenType type);
	void shouldMatchAndConsume(Token::TokenType type);
	void error(Token::TokenType type, Token& peek);
};

