#ifndef ASEXPR_H
#define ASEXPR_H

#include "ASexpression.h"
#include "ASoperator.h"
#include "TCtoken.h"

namespace toyc
{

	class ASexpr : public ASexpression
	{
	public:
		ASexpr(ASoperator*, ASexpression*, ASexpression*);
		std::string toString();
		ASexpression* getOp1();
		ASexpression* getOp2();
		ASoperator* getOper();

	private:
		ASoperator *oper;
		ASexpression *op1, *op2;
	};

}
#endif
