/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

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
    bool ASreturnState::isSimple(){ return hasop; }
	std::string ASreturnState::toString()
	{
		if (hasop)
		{
			s = (spaces() + "returnStatement(\n");
			indent();
			s += (op->toString() + "\n");
			outdent();
			s += (spaces() +  ")\n");
			return s;
		}
		else
		{
			return (spaces() + "returnStatement()\n");
		}
	}

	ASexpression* ASreturnState::getOp()
	{
		return op;	// This might cause a crash if someone calls this
	}				// function when op is not defined in the constructor, idk.
					// Try to avoid doing that. 
}
