#include <iostream>

#include "ASfuncDef.h"
#include "TCsymTable.h"
#include "TCglobals.h"
#include "TCoutput.h"

namespace toyc
{
	ASfuncDef::ASfuncDef(AStype* id, ASdefinition* varDef[], int num, ASstatement* s)
	{
		identifier = id;
		for (int i = 0; i < num; i++)
		{
			varDefList[i] = varDef[i];
		}
		numVarDef = num;
		statement = s;
		setType(FUNCdef);
	}
	AStype* ASfuncDef::getIdentifier()
	{
		return identifier;
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
			return (spaces() + "funDef(\n" +
			        spaces() + identifier->toString() + "\n" +
			        statement->toString() + "\n" + ")");
		}
		std::string str = "";
		str += (spaces() + "funDef(\n" +
				spaces() + identifier->toString() + "\n");

		for (int i = 0; i < numVarDef; i++)
		{
			str += (varDefList[i]->toString());
		}
		str += ("\n" + statement->toString() +
				"\n" + spaces() + ")");
		return str;
	}
}
