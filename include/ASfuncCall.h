#ifndef ASFUNCCALL_H
#define ASFUNCCALL_H


#include "ASexpression.h"
#include "TCtoken.h"

#define MAX_STATEMENTS 500 // arbitrary

namespace toyc
{

	class ASfuncCall :public ASexpression
	{
	public:
		ASfuncCall(ASexpression*, ASexpression* [], int);
		std::string toString();

		ASexpression* getOp1();
		ASexpression* getExpression(int);
		int getNumExpressions();

	private:
		ASexpression* expressionList[MAX_STATEMENTS];
		ASexpression* id;
		int numExpressions;
	};

}
#endif
