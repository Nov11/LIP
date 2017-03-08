#pragma once
#include <stack>
#include "Lexer.h"
#include "Token.h"

class MLHBuffer
{
public:
	MLHBuffer(Lexer& l);
	~MLHBuffer();
	void reserve(std::vector<Token>::size_type i);
	void prepare();
	void mark();
	void restore();
	void consume();
	bool LAhead(Token::TokenType type, int pos);
	void matchAndRemoveTokenFromBuff(Token::TokenType type);
	bool matchType(Token::TokenType type) { bool ret = type == tokenBuff_[idx_].type_; consume(); return ret; }
	void Probing(bool pro) { probing_ = pro; }
private:
	Lexer& l_;
	std::vector<Token> tokenBuff_;
	std::vector<Token>::size_type idx_;
	std::stack<std::vector<Token>::size_type> backTrace_;
	bool probing_ = true;
};

