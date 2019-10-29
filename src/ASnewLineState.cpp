#include <iostream>

#include "ASnewLineState.h"
#include "TCoutput.h"

namespace toyc
{
	ASnewLineState::ASnewLineState()
	{
		setType(NEWLINEstate);
	}

	std::string ASnewLineState::toString()
	{
		return (spaces() + "newLineStatement()");
	}
}