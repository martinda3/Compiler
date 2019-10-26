#ifndef ASEXPRESSION_H
#define ASEXPRESSION_H

#include "ASabstractSyntax.h"

namespace toyc
{

	enum exprType
	{
		FUNCCALLexpr, EXPRexpr, MINUSexpr, NOTexpr
	};

	class ASexpression :public ASabstractSyntax
	{
	public:
		virtual std::string toString() = 0;
		enum exprType getType();
		void setType(enum exprType);
		std::string toTypeString(enum exprType);
	private:
		enum exprType type;
	};

}
#endif
