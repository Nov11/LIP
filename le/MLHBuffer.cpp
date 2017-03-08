#include "MLHBuffer.h"

MLHBuffer::MLHBuffer(Lexer & l)
	: l_(l),
	idx_(0) {}

MLHBuffer::~MLHBuffer()
{
}

void MLHBuffer::reserve(std::vector<Token>::size_type i)
{
	 while (tokenBuff_.size() <= i) { tokenBuff_.push_back(l_.nextToken()); } 
}

void MLHBuffer::prepare()
{
	idx_ = 0; reserve(10);
}

void MLHBuffer::mark() { backTrace_.push(idx_); }

void MLHBuffer::restore() { idx_ = backTrace_.top(); backTrace_.pop(); }

void MLHBuffer::consume() { 
	idx_++; 
	if (idx_ == tokenBuff_.size()) {
		reserve(idx_);
	}
}

bool MLHBuffer::LAhead(Token::TokenType type, int pos) { decltype(idx_) position = idx_ + pos;  reserve(position + 1);  return type == tokenBuff_[position].type_; }

void MLHBuffer::matchAndRemoveTokenFromBuff(Token::TokenType type) {
	if (tokenBuff_[idx_].type_ == type) { idx_++; if (idx_ == tokenBuff_.size()) { tokenBuff_.clear(); idx_ = 0; } }
	else {
		std::cerr << "should match type:" << Token::meaning_[type] << " but encounter :" << tokenBuff_[idx_] << std::endl;
		exit(1);
	}
}
