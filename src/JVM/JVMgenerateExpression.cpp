#include <iostream>
#include <string>

#include "JVMgenerateExpression.h"

#include "ASexpr.h"
//#include "ASbinaryExpr.h" //
//#include "ASunaryExpr.h" //
#include "ASexpression.h"
#include "ASsimpleExpr.h"
#include "JVMtargetCode.h"
#include "JVMgenUtils.h"
#include "TCtoken.h"
#include "ASoperator.h"
#include "TCtokens.h"
#include "TCglobals.h"
#include "TCsymbol.h"
#include "TCsymTable.h"

#include "ASexprState.h"

#include "INEG.h"

namespace toyc {
    void JVMgenerateExpression::genExpression(ASexpression *ast, JVMtargetCode *tc) {
        enum exprType etype = ast->getType();
        if (etype == EXPRexpr) {
            int loc;
            ASexpr *be = dynamic_cast<ASexpr *>(ast);
            genExpression(be->getOp1(), tc);
            genExpression(be->getOp2(), tc);
            ASoperator *temp = be->getOper(); // This is easier do this!!!!!!!!!!!!
            TCtoken *op = temp->getExpr();    // This is easier do this!!!!!!!!!!!!
            //std::string cleanup, idd;
            //TCsymbol *tok;
            switch (op->getTokenType()) {
                case ADDOP:
                    JVMgenUtils::gen_ADDOP(*op, tc);
                    break;
                case MULOP:
                    JVMgenUtils::gen_MULOP(*op, tc);
                    break;
                case RELOP:
                    JVMgenUtils::gen_RELOP(*op, tc);
                    break;
                case OR:
                    JVMgenUtils::gen_OR(*op, tc);
                    break;
                case AND:
                    JVMgenUtils::gen_AND(*op, tc);
                    break;
                case ASSIGNOP:
//                    cleanup = be->getOp2()->toString();
//                    idd = cleanup.substr(4, (cleanup.length() -1) - 4);
//                    loc = symTable->find(idd);
//                    tok->setId(idd);
//                    tok->setType(VAR);
//                    tok->setValue(symTable->getSym(loc)->getValue());
//                    JVMgenUtils::gen_ISTORE(*symTable->getSym(tok)->getId(),tc);
                    break;
                default: // shouldn't happen
                    //getvale = dynamic_cast<ASexprState *>(be->getOp1());
                    //std::cout << be->getOp1()->toString() << std::endl;
                    //std::cout << be->getOp2()->toString() << std::endl;
                    //std::cout << op->getLexeme() << std::endl;
                    std::cerr << "Fatal internal error #1: JVMgenerateExpression" << std::endl;
                    exit(EXIT_FAILURE);
            }
        } else if (etype == SIMPLEexpr) {
            ASsimpleExpr *se = dynamic_cast<ASsimpleExpr *>(ast);
            TCtoken *t = se->getExpr();
            std::string lexeme = t->getLexeme();
            if (t->getTokenType() == ID) {
                TCsymbol *idsym = symTable->getSym(symTable->find(lexeme));
                JVMgenUtils::gen_ILOAD(*idsym, tc);
            } else if (t->getTokenType() == NUMBER) {
                JVMgenUtils::gen_ICONST(stoi(lexeme), tc);
            } else { // shouldn't happen
                std::cerr << "Fatal internal error #2: JVMgenerateExpression" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (etype == FUNCCALLexpr) {


        } else if (etype == MINUSexpr) {

        } else if (etype == NOTexpr) {

        } else if (etype == EMPTYexpr) {

        }
    }

}
