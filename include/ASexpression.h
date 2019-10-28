#ifndef ASEXPRESSION_H
#define ASEXPRESSION_H

#include "ASabstractSyntax.h"

namespace toyc
{

	enum exprType
	{
		FUNCCALLexpr, EXPRexpr, MINUSexpr, NOTexpr, SIMPLEexpr, EMPTYexpr
	};

	class ASexpression :public ASabstractSyntax
	{
	public:
		ASexpression();
		virtual std::string toString();
		enum exprType getType();
		void setType(enum exprType);
		std::string toTypeString(enum exprType);
	private:
		enum exprType type;
	};

}
#endif
