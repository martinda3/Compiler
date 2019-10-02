#include <iostream>

#include "ASgotoState.h"
#include "TCsymTable.h"
#include "TCglobals.h"

namespace toyc {
    ASgotoState::ASgotoState(int l) {
        label = l;
        setType(GOTOstate);
    }

    std::string ASgotoState::toString() {
        std::string str = "";
        str += symTable->getSym(label)->toString();
        return "goto(" + str + ")";
    }

    int ASgotoState::getLabel() { return label; }

}
