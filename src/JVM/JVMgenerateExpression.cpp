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

#include "INEG.h"

namespace toyc {
  void JVMgenerateExpression::genExpression(ASexpression *ast,JVMtargetCode *tc) {
    enum exprType etype = ast->getType();
    if (etype==EXPRexpr){
        ASexpr *be = dynamic_cast<ASexpr*>(ast);
        genExpression(be->getOp1(),tc); genExpression(be->getOp2(),tc);
        ASoperator *temp = be->getOper();
        TCtoken *op = temp->getExpr();
        switch (op->getTokenType()) {
            case ADDOP: JVMgenUtils::gen_ADDOP(*op,tc); break;
            case MULOP: JVMgenUtils::gen_MULOP(*op,tc); break;
            case RELOP: JVMgenUtils::gen_RELOP(*op,tc); break;
            case OR:    JVMgenUtils::gen_OR(*op,tc); break;
            case AND:   JVMgenUtils::gen_AND(*op,tc); break;
            default: // shouldn't happen
                std::cerr << "Fatal internal error #1: JVMgenerateExpression" << std::endl;
                exit(EXIT_FAILURE);
      }
    } /*else if (etype==UNARYexpr) {
      ASunaryExpr *ue = dynamic_cast<ASunaryExpr*>(ast);
      genExpression(ue->getExpr(),tc);
      tc->add(new INEG());
    }*/ else if (etype==SIMPLEexpr) {
       ASsimpleExpr *se = dynamic_cast<ASsimpleExpr*>(ast);
      TCtoken *t = se->getExpr();
      std::string lexeme = t->getLexeme();
      if(t->getTokenType()==ID) {
        TCsymbol *idsym = symTable->getSym(symTable->find(lexeme));
        JVMgenUtils::gen_ILOAD(*idsym,tc);
      } else if(t->getTokenType()==NUMBER) {
       JVMgenUtils::gen_ICONST(stoi(lexeme),tc);
      } else { // shouldn't happen     
        std::cerr << "Fatal internal error #2: JVMgenerateExpression" << std::endl;
        exit(EXIT_FAILURE);
      }
    }
  }
 
}
