#include <iostream>

#include "ASreturnState.h"
#include "TCoutput.h"

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
			s = spaces() + "returnStatement(\n";
			indent();
			s += (  spaces() + op->toString() + "\n" +
					spaces() + "    )\n");
			outdent();
			return s;
		}
		else
		{
			return (spaces() + "returnStatement()");
		}
	}

	ASexpression* ASreturnState::getOp()
	{
		return op;	// This might cause a crash if someone calls this
	}				// function when op is not defined in the constructor, idk.
					// Try to avoid doing that. 
}
