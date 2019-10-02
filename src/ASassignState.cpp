#include <iostream>

#include "ASassignState.h"
#include "TCglobals.h"
#include "TCsymTable.h"
#include "TCsymbol.h"

namespace toyc {

    ASassignState::ASassignState(int l, ASexpr* e) {
        var = l;
        expression = e;
        setType(ASSIGNstate);
    }

    int ASassignState::getVar() { return var; }

    ASexpr *ASassignState::getExpression() { return expression; }

    std::string ASassignState::toString() {
        return
                "assign(" + symTable->getSym(getVar())->toString() + "," +
                expression->toString() + ")";
    }

}
