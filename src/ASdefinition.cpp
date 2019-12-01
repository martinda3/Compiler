/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>
#include "ASdefinition.h"
#include "TCoutput.h"

namespace toyc
{

	enum defType ASdefinition::getType() { return type; }

	void ASdefinition::setType(enum defType t) { type = t; }

	std::string ASdefinition::toTypeString()
	{
		std::string s;
		switch (type)
		{
			case FUNCdef:
				s = "FUNCdef";
				break;
			case VARdef:
				s = "VARdef";
				break;
			default:
				s = "error";
				break;
		}
		return s;
	}
}
