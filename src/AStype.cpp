#include <iostream>

#include "AStype.h"
#include "TCtokens.h"
#include "TCglobals.h"

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
			case INT:		s = "int(" + expr->getLexeme() + ")";		break;
			case CHAR:		s = "char(" + expr->getLexeme() + ")";		break;
			default:		s = "error";								break;
		}
		return s;
	}

	TCtoken* AStype::getExpr()
	{
		return expr;
	}
}
