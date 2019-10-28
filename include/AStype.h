#ifndef ASTYPE_H
#define ASTYPE_H

#include "ASabstractSyntax.h"
#include "TCtoken.h"

namespace toyc
{
	class AStype : public ASabstractSyntax
	{
	public:
		AStype(TCtoken*);
		std::string toString();
		TCtoken* getExpr();
	private:
		TCtoken* expr;

	};

}
#endif
