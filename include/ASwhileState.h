/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASWHILESTATE_H
#define ASWHILESTATE_H

#include "ASstatement.h"
#include "ASexpression.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{
	class ASwhileState : public ASstatement
	{
	public:
		ASwhileState(ASexpression*, ASstatement*);
		std::string toString();

		ASexpression* getOp1();
		ASstatement* getOp2();

	private:
		ASexpression *op1;
		ASstatement *op2;
	};

}
#endif
