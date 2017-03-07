#pragma once

#include <string>
#include<vector>

class Token {
public:
	Token(int type, std::string content) :
		type_(type), content_(content) {}
	Token():type_(TokenType::NONE), content_(meaning_[TokenType::NONE]){}
	int type_;
	std::string content_;
	enum TokenType
	{
		NONE,
		NAME,
		LBRACKET,
		RBRACKET,
		COMMA
	};
	static std::vector<std::string> meaning_;

	operator bool() {
		return (type_ != NONE);
	}
};

inline std::ostream& operator<<(std::ostream& os, Token& t) {
	os << "< " << Token::meaning_[t.type_] << " £¬" << t.content_ << " >" << std::endl;
	return os;
}