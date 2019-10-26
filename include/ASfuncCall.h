#ifndef ASFUNCCALL_H
#define ASFUNCCALL_H


#include "ASexpression.h"
#include "ASsimpleExpr.h"
#include "TCtoken.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASfuncCall :public ASexpression
	{
	public:
		ASfuncCall(ASsimpleExpr*, ASexpression* [], int);
		std::string toString();

		ASsimpleExpr* getOp1();
		ASexpression* getExpression(int);
		int getNumExpressions();

	private:
		ASexpression* expressionList[MAX_STATEMENTS];
		ASsimpleExpr* id;
		int numExpressions;
	};

}
#endif
