#include "TCsymbol.h"

namespace toyc {

    TCsymbol::TCsymbol() {
        id = "";
        type = NO_TYPE;
    }

    TCsymbol::TCsymbol(std::string str, enum symType t) {
        id = str;
        type = t;
    }

    std::string TCsymbol::getId() { return id; }

    void TCsymbol::setId(std::string str) { id = str; }

    enum symType TCsymbol::getType() { return type; }

    void TCsymbol::setType(enum symType t) { type = t; }

    std::string TCsymbol::toString() {
        std::string str = "(";
        str += (getId() + ",");
        switch (getType()) {
            case VAR:
                str += "VAR";
                break;
            case LABEL:
                str += "LABEL";
                break;
            case OFFSET:
                str += "OFFSET";
                break;
            case NO_TYPE:
                str += "NO_TYPE";
                break;
            default:
                str += "ERROR";
                break;
        }
        str += ")";
        return str;
    }
}
