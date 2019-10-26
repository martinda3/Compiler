#include <iostream>

#include "ASifState.h"

namespace toyc
{
	ASifState::ASifState(ASexpression* oper1, ASstatement* oper2, ASstatement* oper3)
	{
		op1 = oper1;
		op2 = oper2;
		op3 = oper3;
		hasop = true;
		setType(IFstate);
	}
	ASifState::ASifState(ASexpression* oper1, ASstatement* oper2)
	{
		op1 = oper1;
		op2 = oper2;
		hasop = false;
		setType(IFstate);
	}

	std::string ASifState::toString()
	{
		if (hasop)
		{
			return "ifStatement(" + op1->toString() + ", " + op2->toString() + ", " + op3->toString() + ")";
		}
		else
		{
			return "ifStatement(" + op1->toString() + ", " + op2->toString() + ")";
		}
	}

	ASexpression* ASifState::getOp1() { return op1; }
	ASstatement* ASifState::getOp2() { return op2; }
	ASstatement* ASifState::getOp3() { return op3; }//Dont call this if the third argument is not defined.

}
