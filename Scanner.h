#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include "Token.h"

typedef std::vector<Token> TokenVec;

class Scanner
{
	private:
		std::string myInput;
		unsigned int myPos;
		unsigned int myVecPos;
		char myCh; 

		TokenVec myTokenVec;

	public:
		Scanner(const std::string& input);

		Token getNextToken(bool peek = false);

	private:
		void initTokenVec();
		Token readNextToken();
		void skipSpaces();
		void readNextChar();
};

#endif /* SCANNER_H */