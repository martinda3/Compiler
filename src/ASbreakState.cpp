#include <iostream>

#include "ASbreakState.h"

namespace toyc
{
	ASbreakState::ASbreakState()
	{
		setType(BREAKstate);
	}

	std::string ASbreakState::toString()
	{
		return "breakStatement()";
	}
}