#pragma once
#include <string>
#include <list>
#include <iostream>
#include "Token.h"



class Lexer
{
public:
	Lexer();
	~Lexer();
	void assignCotent(std::string str);
	void tokenize();
	Token nextToken();
private:
	void match(std::string str);
	void error(const std::string& s) { std::cerr << "pos: " << idx_ << " of string: " << str_  << " hint: " << s << std::endl; exit(1); }
	std::string str_;
	std::list<Token> tokens_;
	char c_;
	std::string::size_type idx_;
	void consume();
	void trimWhiteSpace();
	bool isWhiteSpace();
	void variable();
	bool isLetter() {
		return (c_ >= 'a' && c_ <= 'z') || (c_ >= 'A' && c_ <= 'Z');
	}
};

