#include <iostream>

#include "ASunaryExpr.h"

namespace toyc {
    ASunaryExpr::ASunaryExpr(TCtoken* t, ASexpr* e) {
        oper = t;
        expr = e;
    }

    std::string ASunaryExpr::toString() {
        return ("u_expr(" + oper->toString() + "," + oper->toString() + ")");
    }

    ASexpr *ASunaryExpr::getExpr() { return expr; }

    TCtoken *ASunaryExpr::getOper() { return oper; }

}
