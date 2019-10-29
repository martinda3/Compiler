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
				str += ("number(" + expr->getLexeme() + ")");
				break;
			case ID:
				str += (symTable->getSym(expr)->toString());
				break;
			case CHARLITERAL:
				str += ("charliteral(" + expr->getLexeme() + ")");
				break;
			case STRING:
				str += ("string(" + expr->getLexeme() + ")");
				break;
			default:
				str += "error";
				break;
		}
		return str;
	}

	TCtoken* ASsimpleExpr::getExpr() { return expr; }

}
