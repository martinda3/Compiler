#include <iostream>

#include "ASlabelState.h"
#include "TCglobals.h"
#include "TCsymTable.h"
#include "TCsymbol.h"

namespace toyc {

    ASlabelState::ASlabelState(int l, ASstatement* s) {
        label = l;
        statement = s;
        setType(LABELstate);
    }

    int ASlabelState::getLabel() { return label; }

    ASstatement *ASlabelState::getStatement() { return statement; }

    std::string ASlabelState::toString() {
        return
                "label(" + symTable->getSym(getLabel())->toString() +
                "," + statement->toString() + ")";
    }

}
