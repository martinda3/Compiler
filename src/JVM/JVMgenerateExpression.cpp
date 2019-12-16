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

#include "INVOKESPECIAL.h"
#include "INVOKEVIRTUAL.h"
#include "GETSTATIC.h"
#include "ASfuncCall.h"

#include "LDC.h"
#include "INEG.h"

namespace toyc {
    void JVMgenerateExpression::genExpression(ASexpression *ast, JVMtargetCode *tc) {
        TCtoken *check1;
        std::string cleanup, idd;
        ASsimpleExpr *se;
        enum exprType etype = ast->getType();
        if (etype == EXPRexpr) {
            ASexpr *be = dynamic_cast<ASexpr *>(ast);
            ASoperator *temp = be->getOper();
            TCtoken *op = temp->getExpr();
            if (op->getTokenType() == DIVOP) {
                genExpression(be->getOp2(), tc);
                genExpression(be->getOp1(), tc);
            } else { genExpression(be->getOp1(), tc); }

            if (op->getTokenType() == ASSIGNOP) {
                se = dynamic_cast<ASsimpleExpr *>(be->getOp2());
                check1 = dynamic_cast<TCtoken *>(se->getExpr());
                JVMgenUtils::gen_ISTORE(*symTable->getSym(symTable->find(check1->getLexeme())), tc);
            }
            else {
                if (op->getTokenType() != DIVOP) { genExpression(be->getOp2(), tc); }
                switch (op->getTokenType()) {
                    case ADDOP:     JVMgenUtils::gen_ADDOP(*op, tc);    break;  // Untested
                    case MULOP:  /*JVMgenUtils::gen_MULOP(*op, tc);*/   break;  // Modulous
                    case MULTI:     JVMgenUtils::gen_MULOP(*op, tc);    break;  // multi
                    case DIVOP:     JVMgenUtils::gen_MULOP(*op, tc);    break;  // multi
                    case RELOP:     JVMgenUtils::gen_RELOP(*op, tc);    break;  // Untested
                    case OR:        JVMgenUtils::gen_OR(*op, tc);       break;  // Untested
                    case AND:       JVMgenUtils::gen_AND(*op, tc);      break;  // Untested
                    case ASSIGNOP:                                      break;  // Redudnat
                    default: // shouldn't happen
//                    std::cerr << "Fatal internal error #1: JVMgenerateExpression" << std::endl;
//                    exit(EXIT_FAILURE);
                        break;
                }
            }


        } else if (etype == SIMPLEexpr) {
            TCsymbol *idsym;
            ASsimpleExpr *se = dynamic_cast<ASsimpleExpr *>(ast);
            TCtoken *t = se->getExpr();
            std::string lexeme = t->getLexeme();
            if (t->getTokenType() == ID) {
                idsym = symTable->getSym(symTable->find(t->getLexeme()));
                JVMgenUtils::gen_ILOAD(*idsym, tc);
            } else if (t->getTokenType() == NUMBER) {
                JVMgenUtils::gen_ICONST(stoi(lexeme), tc);
            } else // shouldn't happen
            {
                std::cerr << "Fatal internal error #2: JVMgenerateExpression" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (etype == FUNCCALLexpr) { // Semi-testsed [Writestate]
            TCsymbol *idsym;
            ASfuncCall *sexpr = dynamic_cast<ASfuncCall *>(ast);
            ASsimpleExpr *se = dynamic_cast<ASsimpleExpr *>(sexpr->getOp1());
            TCtoken *t = se->getExpr(); std::string choper;
            switch (t->getTokenType())
            {
                case NUMBER:
                    tc->add(new GETSTATIC(OUTPUT_FIELD_SPEC, OUTPUT_DESCRIPTOR));
                    tc->add(new LDC(t->getLexeme()));
                    tc->add(new INVOKEVIRTUAL(PRINT_STRING_METHOD_SPEC));
                    break;
                case ID:
                    idsym = symTable->getSym(symTable->find(t->getLexeme()));
                    tc->add(new GETSTATIC(OUTPUT_FIELD_SPEC, OUTPUT_DESCRIPTOR));
                    JVMgenUtils::gen_ILOAD(*idsym, tc);
                    tc->add(new INVOKEVIRTUAL(PRINT_INT_NEWLINE_METHOD_SPEC));
                    break;
                case STRING:
                    tc->add(new GETSTATIC(OUTPUT_FIELD_SPEC, OUTPUT_DESCRIPTOR));
                    choper = t->getLexeme().substr(1, (t->getLexeme().length() - 2)); // removes extra ""THis is the sirng""
                    tc->add(new LDC(choper));
                    tc->add(new INVOKEVIRTUAL(PRINT_STRING_METHOD_SPEC));
                    break;
                default:
                    break;
            }
        }
//        Unimplemented
//         else if (etype == MINUSexpr) {
//
//        } else if (etype == NOTexpr) {
//
//        } else if (etype == EMPTYexpr) {
//
//        }
    }

}
