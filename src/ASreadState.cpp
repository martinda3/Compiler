#include <iostream>

#include "ASreadState.h"
#include "TCsymTable.h"
#include "TCglobals.h"

namespace toyc
{
	ASreadState::ASreadState(int sym)
	{
		id = sym;
		setType(READstate);
	}

	std::string ASreadState::toString()
	{
		std::string str = "";
		str += symTable->getSym(id)->toString();
		return "read(" + str + ")";
	}

	int ASreadState::getId() { return id; }

}
