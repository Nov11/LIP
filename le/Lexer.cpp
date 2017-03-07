#include "Lexer.h"
#include <sstream>
Lexer::Lexer()
{
}


Lexer::~Lexer()
{
}

void Lexer::assignCotent(std::string str)
{
	str_ = str;
}

void Lexer::tokenize()
{
	if (str_.empty()) {
		tokens_.clear();
		return;
	}
	//1.set up look ahead charactor 'c' and index 'idx_'
	idx_ = 0;
	c_ = str_[idx_];
	//2.iterate through input string, and add tokens to tokens_
	while(idx_ != str_.size()) {
		trimWhiteSpace();
		switch (c_) {
		case '[': tokens_.push_back(Token(Token::TokenType::LBRACKET, "["));
			consume();
			break;
		case ']':
			tokens_.push_back(Token(Token::TokenType::RBRACKET, "]"));
			consume();
			break;
		case ',':
			tokens_.push_back(Token(Token::TokenType::COMMA, ","));
			consume();
			break;
		default:
			variable();
		}
	}
}

Token Lexer::nextToken()
{
	if (tokens_.empty()) {
		return Token();
	}
	Token ret = tokens_.front();
	tokens_.pop_front();
	return ret;
}

void Lexer::match(std::string str)
{
	for (std::string::size_type i = 0; i < str.size(); i++) {
		if (str[i] == c_) { consume(); }
		else {
			std::string tmp("matching ");
			tmp.append(str);
			error(tmp); 
		}
	}
}

void Lexer::consume()
{
	if (str_.size() == idx_) {
		idx_ = -1;
		c_ = EOF;
		return;
	}
	idx_++;
	c_ = str_[idx_];
}

void Lexer::trimWhiteSpace()
{
	while (isWhiteSpace()) {
		consume();
	}
}

bool Lexer::isWhiteSpace() {
	return (c_ == ' ' || c_ == '\t' || c_ == '\n' || c_ == '\r');
}

void Lexer::variable()
{
	std::stringstream tmp;
	while (isLetter()) {
		tmp<<c_;
		consume();
	}
	std::string s = tmp.str();
	if (s.size() != 0) {
		tokens_.push_back(Token(Token::TokenType::NAME, tmp.str()));
	}
	else {
		//well, this is not a variable name, report error
		std::string tmp("suppose to match variable name");
		error(tmp);
	}
}
