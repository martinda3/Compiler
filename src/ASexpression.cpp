/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>
#include "ASexpression.h"
#include "TCoutput.h"

namespace toyc
{
	ASexpression::ASexpression()
	{
		setType(EMPTYexpr);
	}
	std::string ASexpression::toString()
	{
		return "";
	}
	enum exprType ASexpression::getType() { return type; }
	void ASexpression::setType(enum exprType t) { type = t; }
	std::string ASexpression::toTypeString()
	{
		std::string s;
		switch (type)
		{
			case FUNCCALLexpr:	s = "FUNCCALLexpr";	break;
			case EXPRexpr:		s = "EXPRexpr";		break;
			case MINUSexpr:		s = "MINUSexpr";	break;
			case NOTexpr:		s = "NOTexpr";		break;
			case SIMPLEexpr:	s = "SIMPLEexpr";	break;
			case EMPTYexpr:		s = "EMPTYexpr";	break;
			default:			s = "error";		break;
		}
		return s;
	}
}
