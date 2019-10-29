/*

   EGRE 591 Compiler Construction
   Abstract Syntax: Charles Dieztel

 */

#ifndef ASMINUS_H
#define ASMINUS_H

#include "ASexpression.h"

namespace toyc
{

	class ASminus : public ASexpression
	{
	public:
		ASminus(ASexpression*);

		ASexpression* getExpression();

		std::string toString();

	private:
		ASexpression* expression;
	};

}
#endif
