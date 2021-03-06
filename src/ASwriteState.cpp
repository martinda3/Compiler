/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel
   Pretty Printing: Dajion Martin

 */

#include <iostream>

#include "ASwriteState.h"
#include "TCoutput.h"

namespace toyc
{

	ASwriteState::ASwriteState(ASexpression* expressions[], int num)
	{
		for (int i = 0; i < num; i++)
		{
			expressionList[i] = expressions[i];

		}
		numExpressions = num;
		setType(WRITEstate);
	}

	ASexpression* ASwriteState::getExpression(int num)
	{
		return expressionList[num];
	}
	int ASwriteState::getNumExpressions()
	{
		return numExpressions;
	}
	std::string ASwriteState::toString()
	{
		if (numExpressions == 0)
		{
			return "error";
		}
		std::string str = "";
		str += (spaces() + "writeStatement(\n");
		indent();
		str +=(expressionList[0]->toString() + "\n");
		for (int i = 1; i < numExpressions; i++)
		{
			str += (expressionList[i]->toString());
		}
		outdent();
		str += spaces() + ")\n";
		return str;
	}

}
