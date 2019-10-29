#include <iostream>

#include "ASsimpleExpr.h"
#include "TCtokens.h"
#include "TCglobals.h"
#include "TCoutput.h"

namespace toyc
{
	ASsimpleExpr::ASsimpleExpr(TCtoken* e)
	{
		expr = e;
		setType(SIMPLEexpr);
	}

	std::string ASsimpleExpr::toString()
	{
		std::string str = "";
		switch (expr->getTokenType())
		{
			case NUMBER:
				str += (spaces() + "number(" + expr->getLexeme() + ")");
				break;
			case ID:
				str += (spaces() + symTable->getSym(expr)->toString());
				break;
			case CHARLITERAL:
				str += (spaces() + "charliteral(" + expr->getLexeme() + ")");
				break;
			case STRING:
				str += (spaces() +"string(" + expr->getLexeme() + ")");
				break;
			default:
				str += "error";
				break;
		}
		return str;
	}

	TCtoken* ASsimpleExpr::getExpr() { return expr; }

}
