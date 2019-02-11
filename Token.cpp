#include "Token.h"

Token::Token(TokenType type, double value, const std::string& strValue) : myType(type), myValue(value), myStrValue(strValue)
{
}