#include <iostream>
#include "ASexpression.h"

namespace toyc
{

	enum exprType ASexpression::getType() { return type; }
	void ASexpression::setType(enum exprType t) { type = t; }
	std::string ASexpression::toTypeString(enum exprType t)
	{
		std::string s;
		switch (t)
		{
			case FUNCCALLexpr:	s = "FUNCCALLexpr";	break;
			case EXPRexpr:		s = "EXPRexpr";		break;
			case MINUSexpr:		s = "MINUSexpr";	break;
			case NOTexpr:		s = "NOTexpr";		break;
			default:			s = "error";		break;
		}
		return s;
	}
}
