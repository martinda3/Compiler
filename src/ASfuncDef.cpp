#include <iostream>

#include "ASfuncDef.h"
#include "TCsymTable.h"
#include "TCglobals.h"

namespace toyc
{
	ASfuncDef::ASfuncDef(ASexpression* id, AStype* t, ASdefinition* varDef[], int num, ASstatement* s)
	{
		identifier = id;
		type = t;
		for (int i = 0; i < num; i++)
		{
			varDefList[i] = varDef[i];
		}
		numVarDef = num;
		statement = s;
		setType(FUNCdef);
	}
	ASexpression* ASfuncDef::getIdentifier()
	{
		return identifier;
	}
	AStype* ASfuncDef::getType()
	{
		return type;
	}
	ASdefinition* ASfuncDef::getVarDef(int num)
	{
		return varDefList[num];
	}
	int ASfuncDef::getNumVarDef()
	{
		return numVarDef;
	}
	std::string ASfuncDef::toString()
	{
		if (numVarDef == 0)
		{
			return "varDef(" + identifier->toString() + type->toString() + statement->toString() + ")";
		}
		std::string str = "";
		str += "varDef(" + identifier->toString() + type->toString();
		for (int i = 0; i < numVarDef; i++)
		{
			str += ", " + varDefList[i]->toString();
		}
		str += ", " + statement->toString() + ")";
		return str;
	}
}
