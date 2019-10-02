#ifndef ASBINARYEXPR_H
#define ASBINARYEXPR_H

#include "ASexpr.h"
#include "TCtoken.h"

namespace toyc {

    class ASbinaryExpr : public ASexpr {
    public:
        ASbinaryExpr(TCtoken*, ASexpr*, ASexpr*);

        std::string toString();

        ASexpr* getOp1();

        ASexpr* getOp2();

        TCtoken* getOper();

    private:
        TCtoken *oper;
        ASexpr *op1, *op2;

    };

}
#endif
