#pragma once
#include "Lexer.h"


/**
*grammar :
*list		: '[' elements ']'
*elements	: element (','element)*
*element    : NAME | list
*NAME		: ('a'..'z' | 'A'..'Z')+
*/



class Parser
{
public:
	Parser(Lexer& l) :l_(l) {};
	~Parser();
	Lexer& l_;
	Token lookAheadToken;
	std::string str_;
	void assignContent(std::string str) { str_ = str; }
	void init() { l_.assignCotent(str_); l_.tokenize(); lookAheadToken = l_.nextToken(); }
	bool check() { list(); return true; }
	void consume() { lookAheadToken = l_.nextToken(); }
	void match(Token::TokenType type);
	void error(std::string str) { std::cerr << "error " << str << " current token:" << lookAheadToken << std::endl; exit(1); }
	void list();
	void elements();
	void element();
};

