/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASSIMPLEEXPR_H
#define ASSIMPLEEXPR_H

#include "ASexpr.h"
#include "TCtoken.h"

namespace toyc
{

	class ASsimpleExpr : public ASexpression
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
