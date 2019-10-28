#include <iostream>

#include "ASnot.h"

namespace toyc
{

	ASnot::ASnot(ASexpression* e)
	{
		expression = e;
		setType(NOTexpr);
	}

	ASexpression* ASnot::getExpression() { return expression; }

	std::string ASnot::toString()
	{
		return "not(" + expression->toString() + ")";
	}

}
