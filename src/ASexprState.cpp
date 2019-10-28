#include <iostream>

#include "ASexprState.h"

namespace toyc
{
	ASexprState::ASexprState(ASexpression* oper)
	{
		op = oper;
		setType(EXPRstate);
	}

	std::string ASexprState::toString()
	{
		return "exprStatement(" + op->toString() + ")";
	}

	ASexpression* ASexprState::getOp() { return op; }

}
