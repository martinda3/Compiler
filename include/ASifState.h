#ifndef ASIFSTATE_H
#define ASIFSTATE_H

#include "ASstatement.h"
#include "ASexpr.h"

namespace toyc {

    class ASifState : public ASstatement {
    public:
        ASifState(ASexpr *, int);

        int getLabel();

        ASexpr *getExpression();

        std::string toString();

    private:
        ASexpr *expression;
        int label;
    };

}
#endif
