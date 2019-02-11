#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include "Node.h"

class Parser
{
	private:
		Scanner myScanner;
		Token myTok; 

	public:
		Parser(const std::string& input);

		Node *parse();

	private:
		Node *start();
		Node *multiplikation();
		Node *klammer();
		NodeFunc *funktion();
		NodeIdent *bezeichner();
		NodeNumber *zahl();

		void accept(TokenType type);
		void getNextToken();
};

#endif /* PARSER_H */