#include <iostream>

#include "ASfuncCall.h"
#include "TCoutput.h"

namespace toyc
{
	ASfuncCall::ASfuncCall(ASexpression* identifier, ASexpression* expressions[], int num)
	{
		for (int i = 0; i < num; i++)
		{
			expressionList[i] = expressions[i];
			
		}
		id = identifier;
		numExpressions = num;
		setType(FUNCCALLexpr);
	}

	std::string ASfuncCall::toString()
	{
		if (numExpressions == 0)
		{
			return (spaces() + "funcCall(\n" + spaces() + id->toString() + "\n" + spaces() + ")");
		}
		std::string str = "";
		str += (spaces() + "funcCall(\n" + spaces() + id->toString());
		for (int i = 0; i < numExpressions; i++)
		{
			str += ("\n" + spaces() + expressionList[i]->toString());
		}
		str += ("\n" + spaces() + ")");
		return str;
	}

	ASexpression* ASfuncCall::getOp1()
	{
		return id;
	}
	ASexpression* ASfuncCall::getExpression(int num)
	{
		return expressionList[num];
	}
	int ASfuncCall::getNumExpressions()
	{
		return numExpressions;
	}
}