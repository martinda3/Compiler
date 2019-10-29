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
		s = spaces() + "exprStatement(\n";
		indent();
		s+= op->toString() + "\n";
		outdent();
		s+= spaces() + ")\n";
		return s;
	}

	ASexpression* ASexprState::getOp() { return op; }

}
