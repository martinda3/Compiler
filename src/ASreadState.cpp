/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>

#include "ASreadState.h"
#include "TCsymTable.h"
#include "TCglobals.h"
#include "TCoutput.h"

namespace toyc
{
	ASreadState::ASreadState(ASexpression* identifiers[], int num)
	{
		for (int i = 0; i < num; i++)
		{
			identifierList[i] = identifiers[i];
		}
		numIdentifiers = num;
		setType(READstate);
	}

	ASexpression* ASreadState::getIdentifier(int num)
	{
		return identifierList[num];
	}
	int ASreadState::getNumIdentifiers()
	{
		return numIdentifiers;
	}
	std::string ASreadState::toString()
	{
		if (numIdentifiers == 0)
		{
			return "error";
		}
		std::string str = "";
		str += (spaces() + "readStatement(\n" + spaces() + identifierList[0]->toString());
		for (int i = 1; i < numIdentifiers; i++)
		{
			str += ("\n" + spaces() + identifierList[i]->toString());
		}
		str += ("\n" + spaces() + ")");
		return str;
	}

}
