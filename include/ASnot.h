#ifndef ASNOT_H
#define ASNOT_H

#include "ASexpression.h"

namespace toyc
{

	class ASnot : public ASexpression
	{
	public:
		ASnot(ASexpression*);

		ASexpression* getExpression();

		std::string toString();

	private:
		ASexpression* expression;
	};

}
#endif
