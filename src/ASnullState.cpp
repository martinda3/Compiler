#include <iostream>

#include "ASnullState.h"
#include "TCoutput.h"

namespace toyc
{
	ASnullState::ASnullState()
	{
		setType(NULLstate);
	}

	std::string ASnullState::toString()
	{
		return (spaces() + "nullStatement()");
	}
}