#pragma once
#include <vector>
#include <assert.h>
#include "Token.h"
#include "Lexer.h"

//ring buffer for tokens

class RingBuffer
{
public:
	RingBuffer(int size, Lexer& l) 
		:size_(size), idx_(0), l_(l)
	{ 
	}
	~RingBuffer();	
	
	Token peek(int position) {
		assert(position >= 0);
		int pos = nextIndex(idx_ + position);
		return buffer_[pos];
	}
	Token peek() {
		return peek(0);
	}	
	
	void consume() {
		consume(1);
	}
	void consume(int number) {
		for (int i = 0; i < number; i++) {
			buffer_[idx_] = l_.nextToken();
			idx_ = nextIndex(idx_ + 1);
		}
	}
	void init(){
		assert(l_.tokenized());
		for (decltype(size_) i = 0; i < size_; i++)
		{
			Token tmp = l_.nextToken();
			//if tmp means 'NONE', it's ok. 
			//when encounter 'NONE' token, it is known that this buffer is drained.
			buffer_.push_back(tmp);
		}
	}
private:
	std::vector<Token>::size_type size_;
	std::vector<Token> buffer_;
	int idx_;
	Lexer& l_;
	int nextIndex(int originalIndex) {
		return originalIndex % size_;
	}

};

