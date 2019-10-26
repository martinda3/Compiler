#include <iostream>

#include "ASexpr.h"

namespace toyc
{
	ASexpr::ASexpr(ASoperator* opr, ASexpression* oper1, ASexpression* oper2)
	{
		oper = opr;
		op1 = oper1;
		op2 = oper2;
		setType(EXPRexpr);
	}

	std::string ASexpr::toString()
	{
		return "expr(" + oper->toString() + ", " + op1->toString() + ", " + op2->toString() + ")";
	}

	ASexpression* ASexpr::getOp1() { return op1; }
	ASexpression* ASexpr::getOp2() { return op2; }
	ASoperator* ASexpr::getOper() { return oper; }

}
