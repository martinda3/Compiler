#ifndef ASSTATEMENT_H
#define ASSTATEMENT_H

#include "ASabstractSyntax.h"

namespace toyc {

    enum stateType {
        ASSIGNstate, GOTOstate, IFstate, LABELstate,
        READstate, SKIPstate, WRITEstate
    };

    class ASstatement : public ASabstractSyntax {
    public:
        virtual std::string toString() = 0;

        enum stateType getType();

        void setType(enum stateType);

        std::string toTypeString(enum stateType);

    private:
        enum stateType type;
    };

}
#endif
