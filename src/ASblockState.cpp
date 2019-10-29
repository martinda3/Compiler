/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>

#include "ASblockState.h"
#include "TCsymTable.h"
#include "TCglobals.h"
#include "TCoutput.h"

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
		std::string str = (spaces() + "blockStatement[\n");
		indent();
		if (numVarDef == 0 && numStatements == 0)
		{
			return (spaces() + "blockStatement[]\n");
		}
		else if (numVarDef > 0)
		{
			str += (varDefList[0]->toString());
			for (int i = 1; i < numVarDef; i++)
			{
				str += ("\n" + varDefList[i]->toString());
			}
			for (int i = 0; i < numStatements; i++)
			{
				str += ("\n" + statementList[i]->toString());
			}
			outdent();
			str += (spaces() + "]");
			return str;
		}
		else
		{
			str += (statementList[0]->toString());
			for (int i = 1; i < numStatements; i++)
			{
				str += ("\n" + statementList[i]->toString());
			}
			outdent();
			str += (spaces() + "]");
			return str;
		}
	}
}
