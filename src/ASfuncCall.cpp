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
			std::string s;
			s = spaces() + "funcCall(\n";
			indent();
			s += id->toString();
			outdent();
			s += "\n" + spaces() + ")";
			return s;
		}
		std::string str = "";
		str += (spaces() + "funcCall(\n");
		indent();
		str += (id->toString() + "\n");
		for (int i = 0; i < numExpressions; i++)
		{
			str += ("\n" + expressionList[i]->toString());
		}
		outdent();
		str += spaces() + ")";
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