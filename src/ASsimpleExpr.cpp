#include <iostream>

#include "ASsimpleExpr.h"
#include "TCtokens.h"
#include "TCglobals.h"

namespace toyc
{
	ASsimpleExpr::ASsimpleExpr(TCtoken* e) { expr = e; }

	std::string ASsimpleExpr::toString()
	{
		std::string str = "";
		switch (expr->getTokenType())
		{
			case NUMBER:
				str += expr->toString();
				break;
			case ID:
				str += symTable->getSym(expr)->toString();
				break;
			case CHARLITERAL:
				str += expr->toString();
				break;
			case STRING:
				str += expr->toString();
				break;
			case default:
				str += "error";
				break;
		}
		return str;
	}

	TCtoken* ASsimpleExpr::getExpr() { return expr; }

}
