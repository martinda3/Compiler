/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>
#include "ASprogram.h"
#include "ASprog.h"
#include "TCoutput.h"

namespace toyc
{

	enum progType ASprogram::getType() { return type; }

	void ASprogram::setType(enum progType t) { type = t; }

	std::string ASprogram::toTypeString()
	{
		std::string s;
		switch (type)
		{
			case PROGprog:
				s = "PROGprog";
				break;
			default:
				s = "error";
				break;
		}
		return s;
	}
}
