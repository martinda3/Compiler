/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>
#include "ASstatement.h"
#include "TCoutput.h"

namespace toyc
{
	ASstatement::ASstatement()
	{
		setType(EMPTYstate);
	}
	std::string ASstatement::toString()
	{
		return "";
	}
	enum stateType ASstatement::getType() { return type; }

	void ASstatement::setType(enum stateType t) { type = t; }

	std::string ASstatement::toTypeString()
	{
		std::string s;
		switch (type)
		{
			case EXPRstate:
				s = "EXPRstate";
				break;
			case BREAKstate:
				s = "BREAKstate";
				break;
			case BLOCKstate:
				s = "BLOCKstate";
				break;
			case IFstate:
				s = "IFstate";
				break;
			case NULLstate:
				s = "NULLstate";
				break;
			case RETURNstate:
				s = "RETURNstate";
				break;
			case WHILEstate:
				s = "WRITEstate";
				break;
			case READstate:
				s = "READstate";
				break;
			case WRITEstate:
				s = "WRITEstate";
				break;
			case NEWLINEstate:
				s = "NEWLINEstate";
				break;
			default:
				s = "error";
				break;
		}
		return s;
	}
}
