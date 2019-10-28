#include <iostream>

#include "ASblockState.h"
#include "TCsymTable.h"
#include "TCglobals.h"

namespace toyc
{
	ASblockState::ASblockState(ASdefinition* varDef[], int numv, ASstatement* statements[], int nums)
	{
		for (int i = 0; i < numv; i++)
		{
			varDefList[i] = varDef[i];
		}
		numVarDef = numv;
		for (int i = 0; i < nums; i++)
		{
			statementList[i] = statements[i];
		}
		numStatements = nums;
		setType(BLOCKstate);
	}
	ASdefinition* ASblockState::getVarDef(int num)
	{
		return varDefList[num];
	}
	ASstatement* ASblockState::getStatement(int num)
	{
		return statementList[num];
	}
	int ASblockState::getNumVarDef()
	{
		return numVarDef;
	}
	int ASblockState::getNumStatement()
	{
		return numStatements;
	}
	std::string ASblockState::toString()
	{
		std::string str = "blockStatement(";
		if (numVarDef == 0 && numStatements == 0)
		{
			return "blockStatement()";
		}
		else if (numVarDef > 0)
		{
			str += varDefList[0]->toString();
			for (int i = 1; i < numVarDef; i++)
			{
				str += ", " + varDefList[i]->toString();
			}
			for (int i = 0; i < numStatements; i++)
			{
				str += ", " + statementList[i]->toString();
			}
			str += ")";
			return str;
		}
		else
		{
			str += statementList[0]->toString();
			for (int i = 1; i < numStatements; i++)
			{
				str += ", " + statementList[i]->toString();
			}
			str += ")";
			return str;
		}
	}
}
