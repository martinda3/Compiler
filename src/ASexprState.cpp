#include <iostream>

#include "ASexprState.h"

namespace toyc
{
	ASexprState::ASexprState(ASexpression* oper)
	{
		op = oper;
		setType(EXPRstate);
	}

	std::string ASifState::toString()
	{
		return "exprStatement(" + op->toString() + ")";
	}

	ASexpression* ASifState::getOp1() { return op; }

}
