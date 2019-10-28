#include <iostream>

#include "ASreadState.h"
#include "TCsymTable.h"
#include "TCglobals.h"

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
		str += "readStatement(" + identifierList[0]->toString();
		for (int i = 1; i < numIdentifiers; i++)
		{
			str += ", " + identifierList[i]->toString();
		}
		str += ")";
		return str;
	}

}
