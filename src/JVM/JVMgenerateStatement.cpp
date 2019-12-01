#include <iostream>
#include "ASdefinition.h"
//#include "ASassignState.h"
#include "ASdefinition.h"
#include "ASexpr.h"
#include "ASifState.h"
#include "ASfuncDef.h"
#include "ASwriteState.h"
#include "ASreadState.h"
#include "ASstatement.h"
#include "ASsimpleExpr.h"

#include "JVMtargetCode.h"

#include "JVMgenerateStatement.h"
#include "JVMgenerateExpression.h"
#include "JVMgenUtils.h"
#include "JVMgenGlobals.h"

#include "codeLabel.h"

#include "GOTO.h"
#include "IFNE.h"
#include "INVOKESPECIAL.h"
#include "INVOKEVIRTUAL.h"

#include "ASblockState.h"

#include "LDC.h"

namespace toyc {

  void JVMgenerateStatement::genStatement(ASdefinition *ast,JVMtargetCode *tc) {
      int states, embedded, dets, other_check;
      ASfuncDef *test = dynamic_cast<ASfuncDef*>(ast);
      ASblockState *test1 = dynamic_cast<ASblockState*>(test->getStatement());
      states = test1->getNumStatement();
      std::cout << std::endl << test->getIdentifier()->toString()  << std::endl;
      for(int i =0 ; i< states ; i++)
      {
          std::cout << "  " << test1->getStatement(i)->toTypeString() << std::endl;
          if (test1->getStatement(i)->getType() == IFstate) {
              ASifState *is = dynamic_cast<ASifState *>(test1->getStatement(i));
              std::cout << "   1. getOp1 EXPRexpr" << std::endl;
              ASexpr *getstuff = dynamic_cast<ASexpr *>(is->getOp1());
              std::cout << "         a." << getstuff->getOp1()->toString() << std::endl;
              std::cout << "         b." << getstuff->getOp2()->toString() << std::endl;
              std::cout << "         c." << getstuff->getOper()->toString() << std::endl;

              std::cout << "   2. getOp2 " << is->getOp2()->toTypeString()<<std::endl;
              ASblockState *nest = dynamic_cast<ASblockState *>(is->getOp2());
              embedded = nest->getNumStatement();
              for (int j = 0; j < embedded; j++)
              {
                  std::cout << "      " << j << ". " << nest->getStatement(j)->toTypeString() << std::endl;
                  if (nest->getStatement(j)->getType() == EXPRstate)
                  {
                      std::cout << "           This works121\n";
                  }
              }

              std::cout << "   3. getOp3 " << is->getOp3()->toTypeString() << std::endl;
              ASblockState *nest1 = dynamic_cast<ASblockState *>(is->getOp3());
              dets = nest1->getNumStatement();
              for (int k = 0; k < dets; k++)
              {
                  std::cout << "      " << k << ". " << nest1->getStatement(k)->toTypeString() << std::endl;
              }

          } else if (test1->getStatement(i)->getType() == EXPRstate) { std::cout << "    This works\n"; }
      }
    /*if (stype==ASSIGNstate){
      ASassignState *as = dynamic_cast<ASassignState*>(ast);
      ASexpr *expr = as->getExpression();
      JVMgenerateExpression::genExpression(expr,tc);
      JVMgenUtils::gen_ISTORE(*symTable->getSym(as->getVar()),tc);
    } else if (stype==WRITEstate) {
      ASwriteState *ws = dynamic_cast<ASwriteState*>(ast);
      ASsimpleExpr *sexpr = dynamic_cast<ASsimpleExpr*>(ws->getExpression(1));
      JVMgenUtils::gen_ALOAD(*symTable->getSym(symTable->find("System.out")),tc);
      JVMgenerateExpression::genExpression(sexpr,tc);
      tc->add(new INVOKEVIRTUAL(PRINT_INT_NEWLINE_METHOD_SPEC));
      } else if (stype==READstate) {
      ASreadState *rs = dynamic_cast<ASreadState*>(ast);
      // prompt first
      JVMgenUtils::gen_ALOAD(*symTable->getSym(symTable->find("System.out")),tc);
      tc->add(new LDC("input: "));
      tc->add(new INVOKEVIRTUAL(PRINT_STRING_METHOD_SPEC));
      // now input value
      JVMgenUtils::gen_ALOAD(*symTable->getSym(symTable->find("System.in")),tc);
      tc->add(new INVOKEVIRTUAL(READ_INT_METHOD_SPEC));
      JVMgenUtils::gen_ISTORE(*symTable->getSym(rs->getId()),tc);
    } else if (stype==IFstate) {
      ASifState *is = dynamic_cast<ASifState*>(ast);
      JVMgenerateExpression::genExpression(is->getExpression(),tc);
      tc->add(new IFNE(new label(symTable->getSym(is->getLabel())->getId())));
    } else if (stype==GOTOstate) {
      ASgotoState *gs = dynamic_cast<ASgotoState*>(ast);
      tc->add(new GOTO(new label(symTable->getSym(gs->getLabel())->getId())));
    } else if (stype==LABELstate) {
      ASlabelState *ls = dynamic_cast<ASlabelState*>(ast);
      tc->add(new codeLabel(symTable->getSym(ls->getLabel())->getId()));
      JVMgenerateStatement::genStatement(ls->getStatement(),tc);
    } else if (stype==SKIPstate) {
      // do nothing
    */}

  }


