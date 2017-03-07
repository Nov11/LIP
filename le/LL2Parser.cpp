#include "LL2Parser.h"
#include "Token.h"

LL2Parser::~LL2Parser()
{
}

bool LL2Parser::check(std::string str)
{
	str_ = str;
	l_.assignCotent(str);
	l_.tokenize();
	buff_.init();
	list();
	return true;
}

void LL2Parser::elements()
{
	element();
	while (matchType(Token::TokenType::COMMA)) {
		buff_.consume();
		element();
	}
}

void LL2Parser::element()
{
	using TT = Token::TokenType;
	if (matchType(TT::NAME) && match(1, TT::EQUAL)) {
		shouldMatchAndConsume(TT::NAME);
		shouldMatchAndConsume(TT::EQUAL);
		shouldMatchAndConsume(TT::NAME);
	}
	else if (matchType(TT::NAME)) {
		shouldMatchAndConsume(TT::NAME);
	}
	else {
		list();
	}
}

void LL2Parser::list()
{
	using TT = Token::TokenType;
	shouldMatchAndConsume(TT::LBRACKET);
	elements();
	shouldMatchAndConsume(TT::RBRACKET);
}

bool LL2Parser::match(int position, Token::TokenType type)
{
	Token peekToken = buff_.peek(position);
	if (Token::matchToken(type, peekToken)) {
		return true;
	}
	return false;
}

bool LL2Parser::matchType(Token::TokenType type)
{
	return match(0, type);
}

void LL2Parser::shouldMatchAndConsume(Token::TokenType type)
{
	if (matchType(type)) {
		buff_.consume();
		return;
	}
	error(type, buff_.peek());
}

void LL2Parser::error(Token::TokenType type, Token & peek)
{
	std::string msg("supposed to match type ");
	msg.append(Token::meaning_[type]);
	msg.append(" but failed ");
	msg.append("encounter token type : ");
	msg.append(Token::meaning_[peek.type_]);
	std::cerr << msg << std::endl;
	exit(1);
}
