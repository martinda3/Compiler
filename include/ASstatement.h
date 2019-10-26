#ifndef ASSTATEMENT_H
#define ASSTATEMENT_H

#include "ASabstractSyntax.h"

namespace toyc {

    enum stateType {
        EXPRstate, BREAKstate, BLOCKstate, IFstate,
        NULLstate, RETURNstate, WHILEstate, READstate,
		WRITEstate, NEWLINEstate
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
