#include <iostream>

#include "ASvarDef.h"
#include "TCsymTable.h"
#include "TCglobals.h"

namespace toyc
{
	ASvarDef::ASvarDef(ASsimpleExpr* identifiers[], int num, AStype* t)
	{
		for (int i = 0; i < num; i++)
		{
			identifierList[i] = identifiers[i];

		}
		numIdentifiers = num;
		type = t;
		setType(VARdef);
	}

	ASsimpleExpr* ASvarDef::getIdentifier(int num)
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
		str += "varDef(" + identifierList[0]->toString();
		for (int i = 1; i < numIdentifiers; i++)
		{
			str += ", " + identifierList[i]->toString();
		}
		str += ")";
		return str;
	}

}
