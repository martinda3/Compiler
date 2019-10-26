#include <iostream>

#include "ASnullState.h"

namespace toyc
{
	ASnullState::ASnullState()
	{
		setType(NULLstate);
	}

	std::string ASnullState::toString()
	{
		return "nullStatement()";
	}
}