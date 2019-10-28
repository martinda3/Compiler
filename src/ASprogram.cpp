#include <iostream>
#include "ASprogram.h"

namespace toyc
{

	enum progType ASprogram::getType() { return type; }

	void ASprogram::setType(enum progType t) { type = t; }

	std::string ASprogram::toTypeString(enum progType t)
	{
		std::string s;
		switch (t)
		{
			case PROGprog:
				s = "PROGprog";
				break;
			default:
				s = "error";
				break;
		}
		return s;
	}
}
