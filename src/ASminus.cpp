#include <iostream>

#include "ASminus.h"

namespace toyc
{

	ASminus::ASminus(ASexpression* e)
	{
		expression = e;
		setType(MINUSexpr);
	}

	ASexpression* ASminus::getExpression() { return expression; }

	std::string ASminus::toString()
	{
		return "minus(" + expression->toString() + ")";
	}

}
