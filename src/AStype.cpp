#include <iostream>

#include "AStype.h"
#include "TCtokens.h"
#include "TCglobals.h"
#include "TCoutput.h"

namespace toyc
{
	AStype::AStype(TCtoken* e)
	{
		expr = e;
	}

	std::string AStype::toString()
	{
		std::string s;
		switch (expr->getTokenType())
		{
			case INT:		s = (spaces() + "int(" + expr->getLexeme() + ")");		break;
			case CHAR:		s = (spaces() + "char(" + expr->getLexeme() + ")");		break;
			default:		s =  "error";								            break;
		}
		return s;
	}

	TCtoken* AStype::getExpr()
	{
		return expr;
	}
}
