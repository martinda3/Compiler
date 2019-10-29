#ifndef ASTYPE_H
#define ASTYPE_H

#include "ASabstractSyntax.h"
#include "TCtoken.h"

namespace toyc
{
	class AStype : public ASabstractSyntax
	{
	public:
		AStype(TCtoken*, TCtoken*);
		std::string toString();
		TCtoken* getExpr();
	private:
		TCtoken* expr;
		TCtoken* ident;

	};

}
#endif
