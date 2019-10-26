#ifndef ASSIMPLEEXPR_H
#define ASSIMPLEEXPR_H

#include "ASexpr.h"
#include "TCtoken.h"

namespace toyc
{

	class ASsimpleExpr : public ASexpr
	{
	public:
		ASsimpleExpr(TCtoken*);

		std::string toString();

		TCtoken* getExpr();

	private:
		TCtoken* expr;

	};

}
#endif
