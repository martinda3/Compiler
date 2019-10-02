#include <iostream>

#include "ASbinaryExpr.h"

namespace toyc {
    ASbinaryExpr::ASbinaryExpr(TCtoken *opr, ASexpr *oper1, ASexpr *oper2) {
        oper = opr;
        op1 = oper1;
        op2 = oper2;
    }

    std::string ASbinaryExpr::toString() {
        return ("b_expr(" + oper->toString() + "," +
                op1->toString() + "," +
                op2->toString() + ")");

    }

    ASexpr *ASbinaryExpr::getOp1() { return op1; }

    ASexpr *ASbinaryExpr::getOp2() { return op2; }

    TCtoken *ASbinaryExpr::getOper() { return oper; }

}
