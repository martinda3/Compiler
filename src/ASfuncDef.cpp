#include <iostream>

#include "ASfuncDef.h"
#include "TCsymTable.h"
#include "TCglobals.h"
#include "TCoutput.h"

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
			return ("varDef(\n" +
			        spaces() + identifier->toString() + "\n" +
			        spaces() + type->toString() + "\n" +
			        spaces() + statement->toString() + "\n" + ")");
		}
		std::string str = "";
		str += (spaces() + "varDef(\n" +
				spaces() + identifier->toString() + "\n" +
				spaces() + type->toString());

		for (int i = 0; i < numVarDef; i++)
		{
			str += ("\n" + varDefList[i]->toString());
		}
		str += ("\n" + statement->toString() +
				"\n" + spaces() + ")");
		return str;
	}
}
