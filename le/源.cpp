#include "Lexer.h"
#include "Parser.h"
#include "LL2Parser.h"
#include "MultiLookAhead.h"

void prt(bool valid, std::string testCase) {
	std::cout << "\'" << testCase << "\' is ";
	if (valid) { std::cout << "valid"; }
	else { std::cout << "not valid"; }
	std::cout << std::endl;
}
int main() {
	Lexer l;
	l.assignCotent("[a, b]");
	l.tokenize();
	Token t;
	while (t = l.nextToken()) {
		std::cout << t;
	}

	std::cout << "\nLL(1) parser" << std::endl;
	Parser p(l);
	p.assignContent("[aaa, bbb, [abc, def]]");
	p.init();
	if (p.check()) {
		std::cout << "legal list" << std::endl;
	}

	std::cout << "\nLL(2) parser" << std::endl;
	LL2Parser ll2parser(l);
	std::string test = "[a, b=c,[d,e]]";
	if (ll2parser.check(test)) {
		std::cout << test << " is valid" << std::endl;
	}

	std::cout << "\nLL(k) parser" << std::endl;
	MultiLookAhead p3;
	std::string test3 = "[a,b] = [c,d]";
	prt(p3.check(test3), test3);
}