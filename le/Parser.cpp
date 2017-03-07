#include "Parser.h"

Parser::~Parser()
{
}

void Parser::matchAndConsume(Token::TokenType type)
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
	matchAndConsume(TT::LBRACKET);
	elements();
	matchAndConsume(TT::RBRACKET);
}

void Parser::elements()
{
	element();
	while(lookAheadToken.type_ == Token::TokenType::COMMA) {
		matchAndConsume(Token::TokenType::COMMA);
		element();
	}
}

void Parser::element()
{
	if (lookAheadToken.type_ == Token::TokenType::LBRACKET) {
		list();
	}
	else {
		matchAndConsume(Token::TokenType::NAME);
	}
}
