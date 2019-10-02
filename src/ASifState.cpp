#include <iostream>

#include "ASifState.h"
#include "TCsymTable.h"
#include "TCglobals.h"

namespace toyc {
    ASifState::ASifState(ASexpr* e, int l) {
        expression = e;
        label = l;
        setType(IFstate);
    }

    int ASifState::getLabel() { return label; }

    ASexpr *ASifState::getExpression() { return expression; }

    std::string ASifState::toString() {
        std::string str = "";
        str += (expression->toString() + "," + symTable->getSym(label)->toString());
        return "if(" + str + ")";
    }

}
