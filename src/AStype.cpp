#include <iostream>

#include "AStype.h"
#include "TCtokens.h"
#include "TCglobals.h"
#include "TCoutput.h"

namespace toyc
{
	AStype::AStype(TCtoken* e, TCtoken* ee)
	{
		expr = e;
		ident = ee;
	}

	std::string AStype::toString()
	{
		std::string s;
//		switch (expr->getTokenType())
//		{
//			case INT:		s = (spaces() + "int(" + expr->getLexeme() + ")");		break;
//			case CHAR:		s = (spaces() + "char(" + expr->getLexeme() + ")");		break;
//			default:		s =  "error";								            break;
//		}
		return (expr->getLexeme() + " " + ident->getLexeme());
	}

	TCtoken* AStype::getExpr()
	{
		return expr;
	}
}
