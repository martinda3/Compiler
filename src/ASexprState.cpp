#include <iostream>

#include "ASexprState.h"
#include "TCoutput.h"

namespace toyc
{
	ASexprState::ASexprState(ASexpression* oper)
	{
		op = oper;
		setType(EXPRstate);
	}

	std::string ASexprState::toString()
	{
		s = (spaces() + "exprStatement|\n");
		//indent();
		s += (  spaces() + op->toString() +
				spaces() + "|\n");
		//outdent();
		return s;
	}

	ASexpression* ASexprState::getOp() { return op; }

}
