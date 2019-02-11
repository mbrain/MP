#include "Scanner.h"
#include <iostream>
#include <cstdlib>

Scanner::Scanner(const std::string& input) : myInput(input), myPos(0), myVecPos(0) // Initialisierungen
{
	// Erstes Zeichen
	readNextChar();
	// Alle Tokens
	initTokenVec();
}

void Scanner::initTokenVec()
{
	Token tok = readNextToken();

	while (!tok.equal(TT_NIL))
	{
		myTokenVec.push_back(tok);
		tok = readNextToken();
	}
}

Token Scanner::getNextToken(bool peek)
{
	if (myVecPos < myTokenVec.size())
	{
		if (!peek)
		{
			return myTokenVec[myVecPos++];
		}

		return myTokenVec[myVecPos];
	}

	return Token(TT_NIL);
}

Token Scanner::readNextToken()
{
	std::string buf;
	skipSpaces();

	switch (myCh)
	{
		case '+':
			readNextChar();
			return Token(TT_PLUS);

		case '-':
			readNextChar();
			return Token(TT_MINUS);

		case '*':
			readNextChar();
			return Token(TT_MUL);

		case '/':
			readNextChar();
			return Token(TT_DIV);

		case ',':
			readNextChar();
			return Token(TT_COMMA);

		case '(':
			readNextChar();
			return Token(TT_LPAREN);

		case ')':
			readNextChar();
			return Token(TT_RPAREN);
            
        case '%':
			readNextChar();
			return Token(TT_MOD);
            
        case '^':
			readNextChar();
			return Token(TT_POW);

		case 'a': case 'b': case 'c': case 'd': case 'e':
		case 'f': case 'g': case 'h': case 'i': case 'j':
		case 'k': case 'l': case 'm': case 'n': case 'o':
		case 'p': case 'q': case 'r': case 's': case 't': 
		case 'u': case 'v': case 'w': case 'x': case 'y': 
		case 'z': 
		case 'A': case 'B': case 'C': case 'D': case 'E':
		case 'F': case 'G': case 'H': case 'I': case 'J':
		case 'K': case 'L': case 'M': case 'N': case 'O':
		case 'P': case 'Q': case 'R': case 'S': case 'T': 
		case 'U': case 'V': case 'W': case 'X': case 'Y': 
		case 'Z': 
		case '_':
			while (isalpha(myCh) || myCh == '_')
			{
				buf += myCh;
				readNextChar();
			}

			return Token(TT_IDENT, 0, buf);

		case '0': case '1': case '2': case '3': case '4':
		case '5': case '6': case '7': case '8': case '9':

			while (isdigit(myCh) && myCh != '.')
			{
				buf += myCh;
				readNextChar();
			}

			if (myCh == '.')
			{
				buf += myCh;
				readNextChar();

				if (!isdigit(myCh))
				{
					std::cerr << "Error: die Dezimalzahl ist fehlerhaft" << std::endl;
				}
				else
				{
					while (isdigit(myCh))
					{
						buf += myCh;
						readNextChar();
					}
				}
			}

			return Token(TT_NUMBER, std::atof(buf.c_str()));

		default:
			if (myCh != 0)
			{
				std::cerr << "Error: nicht unterstuetztes Zeichen '" << myCh << "'" << std::endl;
			}
			break;
	}
	return Token(TT_NIL);
}

void Scanner::skipSpaces()
{
	while (myCh == ' ' || myCh == '\t' || myCh == '\r' || myCh == '\n')
	{
		readNextChar();
	}
}

void Scanner::readNextChar()
{
	if (myPos > myInput.length())
	{
		myCh = 0;
		return;
	}

	myCh = myInput[myPos++];
}