#include "Parser.h"

Parser::~Parser()
{
}

void Parser::match(Token::TokenType type)
{
	if (lookAheadToken.type_ == type) {
		consume();
	}
	else {
		std::string tmp("suppose to match token type: \'");
		tmp.append(Token::meaning_[type]);
		tmp.append("\' ");
		error(tmp);
	}
}

void Parser::list()
{
	using TT = Token::TokenType;
	match(TT::LBRACKET);
	elements();
	match(TT::RBRACKET);
}

void Parser::elements()
{
	element();
	while(lookAheadToken.type_ == Token::TokenType::COMMA) {
		match(Token::TokenType::COMMA);
		element();
	}
}

void Parser::element()
{
	if (lookAheadToken.type_ == Token::TokenType::LBRACKET) {
		list();
	}
	else {
		match(Token::TokenType::NAME);
	}
}
