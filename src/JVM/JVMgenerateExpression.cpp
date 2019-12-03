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
#include "AStype.h"

#include "line.h"
#include "JVMgenUtils.h"
#include "JVMgenGlobals.h"
#include "ASexprState.h"

#include "GETSTATIC.h"
#include "ASfuncCall.h"

#include "INEG.h"

namespace toyc {
    void JVMgenerateExpression::genExpression(ASexpression *ast, JVMtargetCode *tc) {
        enum exprType etype = ast->getType();
        if (etype == EXPRexpr) {
            ASexpr *be = dynamic_cast<ASexpr *>(ast);
            genExpression(be->getOp1(), tc);
            genExpression(be->getOp2(), tc);
            ASoperator *temp = be->getOper();
            TCtoken *check1, *check2;
            TCtoken *op = temp->getExpr();
            std::string cleanup, idd;
            ASsimpleExpr *se;
            switch (op->getTokenType()) {
                case ADDOP:     JVMgenUtils::gen_ADDOP(*op, tc);    break;  // Untested
                case MULOP:     JVMgenUtils::gen_MULOP(*op, tc);    break;  // Untested
                case RELOP:     JVMgenUtils::gen_RELOP(*op, tc);    break;  // Untested
                case OR:        JVMgenUtils::gen_OR(*op, tc);       break;  // Untested
                case AND:       JVMgenUtils::gen_AND(*op, tc);      break;  // Untested
                case ASSIGNOP:                                              // Semi-testsed
                    se = dynamic_cast<ASsimpleExpr *>(be->getOp2());
                    check1 = dynamic_cast<TCtoken *>(se->getExpr());
//                    std::cout << check1->toString() << std::endl;

                    se = dynamic_cast<ASsimpleExpr *>(be->getOp1());
                    check2 = dynamic_cast<TCtoken *>(se->getExpr());
//                    std::cout << check2->toString() << std::endl;

                    if (check1->getTokenType() == ID && check2->getTokenType() == NUMBER) {
                        JVMgenUtils::gen_ICONST(stoi(check2->getLexeme()), tc);
                        TCsymbol *idsym = symTable->getSym(symTable->find(check1->getLexeme()));
//                        std::cout << check1->getLexeme() << std::endl;
                        JVMgenUtils::gen_ISTORE(*symTable->getSym(symTable->find(check1->getLexeme())), tc);
                        break;
                    } else if (check1->getTokenType() == ID) {
                        TCsymbol *idsym = symTable->getSym(symTable->find(check1->getLexeme()));
                        JVMgenUtils::gen_ISTORE(*symTable->getSym(symTable->find(check1->getLexeme())), tc);
                        break;
                    }
                    break;
                default: // shouldn't happen
                    std::cerr << "Fatal internal error #1: JVMgenerateExpression" << std::endl;
                    exit(EXIT_FAILURE);
            }
//        Dose note do anything
//        } else if (etype == SIMPLEexpr) {
//            ASsimpleExpr *se = dynamic_cast<ASsimpleExpr *>(ast);
//            TCtoken *t = se->getExpr();
//            std::string lexeme = t->getLexeme();
//            if (t->getTokenType() == ID) {
//
//            } else if (t->getTokenType() == NUMBER) {
//
//            } else // shouldn't happen
//            {
//                std::cerr << "Fatal internal error #2: JVMgenerateExpression" << std::endl;
//                exit(EXIT_FAILURE);
//            }
        } else if (etype == FUNCCALLexpr) { // Semi-testsed [Writestate]
            ASfuncCall *sexpr = dynamic_cast<ASfuncCall *>(ast);
//            std::cout << "  " << sexpr->getOp1()->toTypeString() << std::endl;
            ASsimpleExpr *se = dynamic_cast<ASsimpleExpr *>(sexpr->getOp1());
            TCtoken *t = se->getExpr();
//            std::cout << t->getLexeme() << std::endl;
            TCsymbol *idsym = symTable->getSym(symTable->find(t->getLexeme()));
            tc->add(new GETSTATIC(OUTPUT_FIELD_SPEC, OUTPUT_DESCRIPTOR));
            JVMgenUtils::gen_ILOAD(*idsym, tc);
        }
//        Untested
//         else if (etype == MINUSexpr) {
//
//        } else if (etype == NOTexpr) {
//
//        } else if (etype == EMPTYexpr) {
//
//        }
    }

}
