/*

   EGRE 591 Compiler Construction
   Created By: Dan Relser

 */

#include "TCsymbol.h"

namespace toyc
{
    int _nextOffset = 1;

	TCsymbol::TCsymbol() { id = ""; type = NO_TYPE; offset = -1; }

	TCsymbol::TCsymbol(std::string str, enum symType t)
	{
		id = str;
		type = t;

	}

	std::string TCsymbol::getId() { return id; }

	void TCsymbol::setId(std::string str) { id = str; }

	enum symType TCsymbol::getType() { return type; }

	void TCsymbol::setType(enum symType t) { type = t; if (type == VAR) {value = "NULL"; }}

    int TCsymbol::getOffset() { return offset; }

    std::string TCsymbol::getValue() { return value; }

    void TCsymbol::setValue(std::string setThis) { value = setThis; }

    void TCsymbol::setOffset(int n) { offset = n; }

    int TCsymbol::getNextOffset() { return _nextOffset++; }

	std::string TCsymbol::toString()
	{
		std::string str;
		switch (getType())
		{
			case VAR:
				str = "var(" + getId() + ")";
				break;
			case FUNC:
				str = "Function(" + getId() + ")";
				break;
			case NO_TYPE:
				str = "NOTYPE(" + getId() + ")";//This is sort of terrible, but considering that
				break;						//ToyC doesn't actually have labels or offsets
			default:						//I think we can actually assume that every 
				str = "error";				//Symbol is a variable, so probably this will 
				break;						//actually never cause problems. Still, it is
		}									//kinda hacky and we should change it later
		return str;							//TODO:fix this properly
	}
}
