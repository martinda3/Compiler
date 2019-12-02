/*

   EGRE 591 Compiler Construction
   Created By: Dan Relser

 */

#include "TCsymbol.h"

namespace toyc
{
    int _nextOffset = 1;

	TCsymbol::TCsymbol() { id = ""; type = NO_TYPE; offset = -1; }

	TCsymbol::TCsymbol(std::string str, enum symType t) { id = str; type = t; }

	std::string TCsymbol::getId() { return id; }

	void TCsymbol::setId(std::string str) { id = str; }

	enum symType TCsymbol::getType() { return type; }

	void TCsymbol::setType(enum symType t) { type = t; if (type == VAR) {value = "NULL"; }}

    int TCsymbol::getOffset() { return offset; }

    std::string TCsymbol::getValue() { return value; }

    void TCsymbol::setValue(std::string setThis) { value = setThis; }

    void TCsymbol::setOffset(int n) { offset = n; }

    //int TCsymbol::getNextOffset() { return _nextOffset++; }
    void TCsymbol::getNextOffset() { _nextOffset++; }

	std::string TCsymbol::toString()
	{
		std::string str;
		switch (getType())
		{
			case VAR:       str = "var(" + getId() + ")";       break;
			case FUNC:      str = "Function(" + getId() + ")";  break;
            case OFFSET:    str = "OFFSET,";                   str += std::to_string(offset);  break;
			case NO_TYPE:   str = "NOTYPE(" + getId() + ")";    break;
			default:        str = "error";                      break;
		}
		return str;
	}
}
