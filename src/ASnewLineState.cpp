#include <iostream>

#include "ASnewLineState.h"

namespace toyc
{
	ASnewLineState::ASnewLineState()
	{
		setType(NEWLINEstate);
	}

	std::string ASnewLineState::toString()
	{
		return "newLineStatement()";
	}
}