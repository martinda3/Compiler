/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASWRITESTATE_H
#define ASWRITESTATE_H

#include "ASstatement.h"
#include "ASexpression.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASwriteState : public ASstatement
	{
	public:
		ASwriteState(ASexpression* [], int);

		ASexpression* getExpression(int);
		std::string toString();
		int getNumExpressions();

	private:
		ASexpression* expressionList[MAX_STATEMENTS];
		int numExpressions;
	};

}
#endif
