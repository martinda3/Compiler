#include <iostream>

#include "ASifState.h"
#include "TCoutput.h"

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
			s = (spaces() + "ifStatementQ\n");
			indent();
			s += (  spaces() + op1->toString() + "\n" +
					spaces() + op2->toString() + "\n" +
					spaces() + op3->toString() + "\n" +
					spaces() + "    Q\n");
			outdent();
			return s;
		}
		else
		{
			s = (spaces() + "ifStatementQ\n");
			indent();
			s += (  spaces() + op1->toString() + "\n" +
			        spaces() + op2->toString() + "\n" +
			        spaces() + "    Q\n");
			outdent();
			return s;
		}
	}

	ASexpression* ASifState::getOp1() { return op1; }
	ASstatement* ASifState::getOp2() { return op2; }
	ASstatement* ASifState::getOp3() { return op3; }//Dont call this if the third argument is not defined.

}
