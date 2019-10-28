#include <iostream>

#include "ASwhileState.h"

namespace toyc
{
	ASwhileState::ASwhileState(ASexpression* oper1, ASstatement* oper2)
	{
		op1 = oper1;
		op2 = oper2;
		setType(WHILEstate);
	}

	std::string ASwhileState::toString()
	{
		return "whileStatement(" + op1->toString() + ", " + op2->toString() + ")";
	}

	ASexpression* ASwhileState::getOp1() { return op1; }
	ASstatement* ASwhileState::getOp2() { return op2; }

}