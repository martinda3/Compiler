/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>

#include "AStype.h"
#include "TCtokens.h"
#include "TCglobals.h"
#include "TCoutput.h"

namespace toyc
{
	AStype::AStype(TCtoken* e, TCtoken* ee)
	{
		expr = e;
		ident = ee;
	}

	std::string AStype::toString()
	{
		std::string s;
		return (expr->getLexeme() + " " + ident->getLexeme());
	}

	TCtoken* AStype::getExpr()
	{
		return ident;
	}
}
