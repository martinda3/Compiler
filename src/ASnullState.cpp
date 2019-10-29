/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>

#include "ASnullState.h"
#include "TCoutput.h"

namespace toyc
{
	ASnullState::ASnullState()
	{
		setType(NULLstate);
	}

	std::string ASnullState::toString()
	{
		return (spaces() + "nullStatement()");
	}
}