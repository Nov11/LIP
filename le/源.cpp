#include "Lexer.h"
#include "Parser.h"
int main() {
	Lexer l;
	l.assignCotent("[a, b]");
	l.tokenize();
	Token t;
	while (t = l.nextToken()) {
		std::cout << t;
	}

	std::cout << "parser" << std::endl;
	Parser p(l);
	p.assignContent("[aaa, bbb, [abc, def]]");
	p.init();
	if (p.check()) {
		std::cout << "legal list" << std::endl;
	}
}