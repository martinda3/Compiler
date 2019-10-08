#ifndef ASREADSTATE_H
#define ASREADSTATE_H

#include "ASstatement.h"

namespace toyc {

    class ASreadState : public ASstatement {
    public:
        ASreadState(int);

        std::string toString();

        int getId();

    private:
        int id;
    };

}
#endif
