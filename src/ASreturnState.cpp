#include <iostream>

#include "ASreturnState.h"

namespace toyc
{
	ASreturnState::ASreturnState(ASexpression* oper)
	{
		op = oper;
		hasop = true;
		setType(RETURNstate);
	}
	ASreturnState::ASreturnState()
	{
		hasop = false;
	}

	std::string ASreturnState::toString()
	{
		if (hasop)
		{
			return "returnStatement(" + op->toString() + ")";
		}
		else
		{
			return "returnStatement()";
		}
	}

	ASexpression* ASreturnState::getOp()
	{
		return op;	// This might cause a crash if someone calls this
	}				// function when op is not defined in the constructor, idk.
					// Try to avoid doing that. 
}
