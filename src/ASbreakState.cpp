#include <iostream>

#include "ASbreakState.h"
#include "TCoutput.h"

namespace toyc
{
	ASbreakState::ASbreakState()
	{
		setType(BREAKstate);
	}

	std::string ASbreakState::toString()
	{
		return (spaces() + "breakStatement()");
	}
}