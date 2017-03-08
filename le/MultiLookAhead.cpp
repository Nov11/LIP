#include "MultiLookAhead.h"



MultiLookAhead::MultiLookAhead()
	:buffer_(l_)
{
}


MultiLookAhead::~MultiLookAhead()
{
}

bool MultiLookAhead::check(std::string str) {
	str_ = str;
	init();
	return stat();
}

void MultiLookAhead::init() { l_.assignCotent(str_); l_.tokenize(); buffer_.prepare(); }

bool MultiLookAhead::stat() {
	bool result = false;
	buffer_.mark();
	result = list() && buffer_.matchType(TT::NONE);
	if (result) {
		return true;
	}
	else {
		buffer_.restore();
		result = assign() && buffer_.matchType(TT::NONE);
	}
	return result;
}

bool MultiLookAhead::assign() {
	if (list()
		&& buffer_.matchType(TT::EQUAL)
		&& list()) {
		return true;
	}
	return false;
}

bool MultiLookAhead::list() {
	int start = buffer_.currentPosition();
	if (listCache[start] == 0) {
		//not probed yet.
		//default:there will not be a match
		listCache[start] = -1;
		if (buffer_.matchType(TT::LBRACKET)
			&& elements()
			&& buffer_.matchType(TT::RBRACKET)) {
			int end = buffer_.currentPosition();
			//set up match position
			listCache[start] = end;
			return true;
		}
		return false;
	}
	else if(listCache[start] != -1){
		//std::cout << "use cached match position for list" << std::endl;
		buffer_.seek(listCache[start]);
		return true;
	}
	else {
		//there will not be a match
		return false;
	}
}

bool MultiLookAhead::elements() {
	if (!element())return false;
	while (buffer_.LAhead(TT::COMMA, 0)) {
		if (!(buffer_.matchType(TT::COMMA)
			&& element())) {
			return false;
		}
	}
	return true;
}

bool MultiLookAhead::element() {
	if (buffer_.LAhead(TT::NAME, 0) && buffer_.LAhead(TT::EQUAL, 1)) {
		if (buffer_.matchType(TT::NAME)
			&&
			buffer_.matchType(TT::EQUAL)
			&&
			buffer_.matchType(TT::NAME)) {
			return true;
		}
	}
	else if (buffer_.LAhead(TT::NAME, 0)) {
		if (buffer_.matchType(TT::NAME)) {
			return true;
		}
	}
	else {
		if (list()) {
			return true;
		}
	}
	return false;
}
