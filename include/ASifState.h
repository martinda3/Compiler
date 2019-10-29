/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASIFSTATE_H
#define ASIFSTATE_H

#include "ASstatement.h"
#include "ASexpression.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{
	class ASifState : public ASstatement
	{
	public:
		ASifState(ASexpression*, ASstatement*, ASstatement*);
		ASifState(ASexpression*, ASstatement*);
		std::string toString();

		ASexpression* getOp1();
		ASstatement* getOp2();
		ASstatement* getOp3();

	private:
		ASexpression* op1;
		ASstatement* op2;
		ASstatement* op3;
		std::string s;
		bool hasop;
	};

}
#endif
