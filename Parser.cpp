#include "Parser.h"
#include <iostream>

Parser::Parser(const std::string& input) : myScanner(input) 
{
	getNextToken();
}

Node *Parser::parse()
{
	Node *res = start();
	accept(TT_NIL);
	return res;
}
 
Node *Parser::start()
{
	Node *res = multiplikation();

	while (myTok.equal(TT_PLUS) || myTok.equal(TT_MINUS))
	{
		switch (myTok.getType())
		{
			case TT_PLUS:
				getNextToken();
				res = new NodeAdd(res, multiplikation());
				break;

			case TT_MINUS:
				getNextToken();
				res = new NodeSub(res, multiplikation());
				break;
		}
	}

	return res;
}
 
Node *Parser::multiplikation()
{
	Node *res = klammer();

	while (myTok.equal(TT_MUL) || myTok.equal(TT_DIV) || myTok.equal(TT_MOD) || myTok.equal(TT_POW))
	{
		switch (myTok.getType())
		{
			case TT_MUL:
				getNextToken();
				res = new NodeMul(res, klammer());
				break;

			case TT_DIV:
				getNextToken();
				res = new NodeDiv(res, klammer());
				break;
                
            case TT_MOD:
				getNextToken();
				res = new NodeMod(res, klammer());
				break;
                
            case TT_POW:
				getNextToken();
				res = new NodePow(res, klammer());
				break;
		}
	}

	return res;
}

Node *Parser::klammer()
{
	int sign = 1; 

	if (myTok.equal(TT_PLUS) || myTok.equal(TT_MINUS))
	{
		if (myTok.equal(TT_MINUS))
		{
			sign = -1; 
		}

		getNextToken();
	}

	if (myTok.equal(TT_LPAREN))
	{
		accept(TT_LPAREN);

		Node *res = start(); 

		accept(TT_RPAREN);

		return new NodeMul(new NodeNumber(sign), res);
	}
	else if (myTok.equal(TT_IDENT))
	{
		if (myScanner.getNextToken(true).equal(TT_LPAREN))
		{
			return funktion();
		}
		return bezeichner();
	}
	
	return new NodeMul(new NodeNumber(sign), zahl());
}
 
NodeFunc *Parser::funktion()
{
	NodeFunc *res = new NodeFunc(bezeichner());

	accept(TT_LPAREN);

	if (!myTok.equal(TT_RPAREN))
	{
		res->pushArg(start());

		while (myTok.equal(TT_COMMA))
		{
			accept(TT_COMMA);
			res->pushArg(start()); 
		}
	}

	accept(TT_RPAREN);

	return res;
}

NodeIdent *Parser::bezeichner()
{
	std::string ident = myTok.getStrValue();

	accept(TT_IDENT);

	return new NodeIdent(ident);
}

NodeNumber *Parser::zahl()
{
	double res = myTok.getValue();

	accept(TT_NUMBER);

	return new NodeNumber(res);
}

void Parser::accept(TokenType type)
{
	if (!myTok.equal(type))
	{
		std::cerr << "Error: unerwartetes Token " << myTok.toString() << ", " << TokenTypeStr[type] << " erwartet" << std::endl;
	}
	getNextToken();
}

void Parser::getNextToken()
{
	myTok = myScanner.getNextToken();
}