/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>

#include "ASvarDef.h"
#include "TCsymTable.h"
#include "TCglobals.h"
#include "TCoutput.h"

namespace toyc
{
	ASvarDef::ASvarDef(AStype* identifiers[], int num)
	{
		for (int i = 0; i < num; i++)
		{
			identifierList[i] = identifiers[i];

		}
		numIdentifiers = num;
		setType(VARdef);
        THISISCHEATING += num;
	}

	AStype* ASvarDef::getIdentifier(int num)
	{
		return identifierList[num];
	}

	int ASvarDef::getNumIdentifiers()
	{
		return numIdentifiers;
	}
	std::string ASvarDef::toString()
	{
		if (numIdentifiers == 0)
		{
			return "error";
		}
		std::string str = "";
		str += (spaces() + "varDef(" + identifierList[0]->toString());
		for (int i = 1; i < numIdentifiers; i++)
		{
			str += (", " + identifierList[i]->toString());
		}
		str += ")";
		return str;
	}

}
