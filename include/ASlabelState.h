#ifndef ASLABELSTATE_H
#define ASLABELSTATE_H

#include "ASstatement.h"

namespace toyc {

    class ASlabelState : public ASstatement {
    public:
        ASlabelState(int, ASstatement*);

        std::string toString();

        int getLabel();

        ASstatement *getStatement();

    private:
        int label;
        ASstatement *statement;
    };

}
#endif
