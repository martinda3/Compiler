#include <iostream>

#include "ASsimpleExpr.h"
#include "TCtokens.h"
#include "TCglobals.h"

namespace toyc {
    ASsimpleExpr::ASsimpleExpr(TCtoken *e) { expr = e; }

    std::string ASsimpleExpr::toString() {
        std::string str = "";
        str +=
                ((expr->getTokenType() == NUMBER) ? ("(" + expr->getLexeme() + "," + "NUMBER)") :
                 (expr->getTokenType() == ID) ? symTable->getSym(expr)->toString() :
                 "error"
                );
        return ("s_expr(" + str + ")");
    }

    TCtoken *ASsimpleExpr::getExpr() { return expr; }

}
