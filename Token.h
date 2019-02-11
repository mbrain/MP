#ifndef TOKEN_H
#define TOKEN_H

#include <string>

enum TokenType
{
    TT_PLUS, // +
    TT_MINUS, // -
    TT_MUL, // *
    TT_DIV, // /
    TT_MOD, // %
    TT_POW, // ^

	TT_COMMA, // ,

    TT_LPAREN, // (
    TT_RPAREN, // )

    TT_NUMBER, // 12345
	TT_IDENT, // sin


    TT_NIL // no match
};

static const char *TokenTypeStr[] = 
{
	"TT_PLUS",
	"TT_MINUS",
	"TT_MUL",
	"TT_DIV",
    "TT_MOD",
    "TT_POW",

	"TT_COMMA",

	"TT_LPAREN",
	"TT_RPAREN",

	"TT_NUMBER",
	"TT_IDENT",

	"TT_NIL"
};

class Token
{
	private:
		TokenType myType;
		double myValue;
		std::string myStrValue;

	public:
		Token(TokenType type = TT_NIL, double value = 0, const std::string& strValue = "");

		TokenType getType() const { return myType; }
		double getValue() const { return myValue; }
		const std::string& getStrValue() const { return myStrValue; }
		const char *toString() const { return TokenTypeStr[myType]; }
		bool equal(TokenType type) const { return myType == type; }
};

#endif /* TOKEN_H */