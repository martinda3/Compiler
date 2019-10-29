/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>

#include "ASbreakState.h"
#include "TCoutput.h"

namespace toyc
{
	ASbreakState::ASbreakState()
	{
		setType(BREAKstate);
	}

	std::string ASbreakState::toString()
	{
		return (spaces() + "breakStatement()");
	}
}