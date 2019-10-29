/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASOPERATOR_H
#define ASOPERATOR_H

#include "ASabstractSyntax.h"
#include "TCtoken.h"

namespace toyc
{
	class ASoperator :public ASabstractSyntax
	{
	public:
		ASoperator(TCtoken*);
		std::string toString();
		TCtoken* getExpr();
	private:
		TCtoken* expr;
	};

}
#endif
