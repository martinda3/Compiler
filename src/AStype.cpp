#include <iostream>
#include "AStype.h"

namespace toyc
{
	AStype::AStype(enum typeType t)
	{
		type = t;
	}

	enum typeType AStype::getType() { return type; }
	void AStype::setType(enum typeType t) { type = t; }
	std::string AStype::toString()
	{
		std::string s;
		switch (type)
		{
			case INTtype:		s = "int";			break;
			case CHARtype:		s = "char";			break;
			default:			s = "error";		break;
		}
		return s;
	}
	std::string AStype::toTypeString(enum typeType)
	{
		std::string s;
		switch (type)
		{
			case INTtype:		s = "INTtype";			break;
			case CHARtype:		s = "CHARtype";			break;
			default:			s = "error";			break;
		}
		return s;
	}
}
