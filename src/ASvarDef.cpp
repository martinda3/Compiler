#include <iostream>

#include "ASvarDef.h"
#include "TCsymTable.h"
#include "TCglobals.h"
#include "TCoutput.h"

namespace toyc
{
	ASvarDef::ASvarDef(ASexpression* identifiers[], int num, AStype* t)
	{
		for (int i = 0; i < num; i++)
		{
			identifierList[i] = identifiers[i];

		}
		numIdentifiers = num;
		type = t;
		setType(VARdef);
	}

	ASexpression* ASvarDef::getIdentifier(int num)
	{
		return identifierList[num];
	}
	AStype* ASvarDef::getType()
	{
		return type;
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
			str += (spaces() + ", " + identifierList[i]->toString());
		}
		str += (spaces() + ")");
		return str;
	}

}
