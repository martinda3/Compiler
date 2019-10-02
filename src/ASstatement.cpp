#include <iostream>
#include "ASstatement.h"

namespace toyc {

    enum stateType ASstatement::getType() { return type; }

    void ASstatement::setType(enum stateType t) { type = t; }

    std::string ASstatement::toTypeString(enum stateType t) {
        std::string s;
        switch (t) {
            case ASSIGNstate:
                s = "ASSIGNstate";
                break;
            case GOTOstate:
                s = "GOTOstate";
                break;
            case IFstate:
                s = "IFstate";
                break;
            case LABELstate:
                s = "LABELstate";
                break;
            case READstate:
                s = "READstate";
                break;
            case SKIPstate:
                s = "SKIPstate";
                break;
            case WRITEstate:
                s = "WRITEstate";
                break;
            default:
                s = "error";
                break;
        }
        return s;
    }
}
