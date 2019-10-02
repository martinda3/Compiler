#ifndef ASASSIGNSTATE_H
#define ASASSIGNSTATE_H

#include "ASstatement.h"
#include "ASexpr.h"

namespace toyc {

    class ASassignState : public ASstatement {
    public:
        ASassignState(int, ASexpr *);

        std::string toString();

        int getVar();

        ASexpr *getExpression();

    private:
        int var;
        ASexpr *expression;
    };

}
#endif
