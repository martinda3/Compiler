#include <iostream>

#include "ASfuncCall.h"

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
			return "funcCall(" + id->toString() + ")";
		}
		std::string str = "";
		str += "funcCall(" + id->toString();
		for (int i = 0; i < numExpressions; i++)
		{
			str += ", " + expressionList[i]->toString();
		}
		str += ")";
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