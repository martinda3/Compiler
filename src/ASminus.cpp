#include <iostream>

#include "ASminus.h"
#include "TCoutput.h"

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
		return (spaces() + "minus(\n" + spaces() + expression->toString() + "\n" + spaces() +  ")");
	}

}
