#include <iostream>
#include "ASdefinition.h"
#include "TCoutput.h"

namespace toyc
{

	enum defType ASdefinition::getType() { return type; }

	void ASdefinition::setType(enum defType t) { type = t; }

	std::string ASdefinition::toTypeString(enum defType t)
	{
		std::string s;
		switch (t)
		{
			case FUNCdef:
				s = "FUNCdef";
				break;
			case VARdef:
				s = "VARdef";
				break;
			default:
				s = "error";
				break;
		}
		return s;
	}
}
