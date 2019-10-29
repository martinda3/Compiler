/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>

#include "ASoperator.h"
#include "TCtokens.h"
#include "TCglobals.h"
#include "TCoutput.h"

namespace toyc
{
	ASoperator::ASoperator(TCtoken* e)
	{
		expr = e;
	}

	std::string ASoperator::toString()
	{
		std::string s;
		s = (spaces() + "operator(" + expr->getLexeme() + ")");
		return s;
	}

	TCtoken* ASoperator::getExpr()
	{
		return expr;
	}
}
