/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>

#include "ASnot.h"
#include "TCoutput.h"

namespace toyc
{

	ASnot::ASnot(ASexpression* e)
	{
		expression = e;
		setType(NOTexpr);
	}

	ASexpression* ASnot::getExpression() { return expression; }

	std::string ASnot::toString()
	{
		return (spaces() + "not(" + expression->toString() + ")");
	}

}
