#include <iostream>

#include "ASwhileState.h"
#include "TCoutput.h"

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
		std::string s;
		s = spaces() + "whileStatement(\n";
		indent();
		s += op1->toString() + "\n" +
		     op2->toString() + "\n" +
		     spaces() +  ")";
		outdent();
		return s;
	}

	ASexpression* ASwhileState::getOp1() { return op1; }
	ASstatement* ASwhileState::getOp2() { return op2; }

}
