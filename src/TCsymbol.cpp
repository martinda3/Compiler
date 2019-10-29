/*

   EGRE 591 Compiler Construction
   Created By: Dan Relser

 */

#include "TCsymbol.h"

namespace toyc
{

	TCsymbol::TCsymbol()
	{
		id = "";
		type = NO_TYPE;
	}

	TCsymbol::TCsymbol(std::string str, enum symType t)
	{
		id = str;
		type = t;
	}

	std::string TCsymbol::getId() { return id; }

	void TCsymbol::setId(std::string str) { id = str; }

	enum symType TCsymbol::getType() { return type; }

	void TCsymbol::setType(enum symType t) { type = t; }

	std::string TCsymbol::toString()
	{
		std::string str;
		switch (getType())
		{
			case VAR:
				str = "var(" + getId() + ")";
				break;
			case LABEL:
				str = "label(" + getId() + ")";
				break;
			case OFFSET:
				str = "offset(" + getId() + ")";
				break;
			case NO_TYPE:
				str = "no_type(" + getId() + ")";
				break;
			default:
				str = "error";
				break;
		}
		return str;
	}
}
