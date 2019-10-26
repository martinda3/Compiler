#ifndef ASUNARYEXPR_H
#define ASUNARYEXPR_H

#include "ASexpr.h"
#include "TCtoken.h"

namespace toyc
{
	class ASunaryExpr : public ASexpr
	{
	public:
		ASunaryExpr(TCtoken*, ASexpr*);

		ASexpr* getExpr();

		TCtoken* getOper();

		std::string toString();

	private:
		ASexpr* expr;
		TCtoken* oper;
	};
}
#endif
