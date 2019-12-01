#include <iostream>
#include "ASdefinition.h"
#include "ASreturnState.h"
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
      ASfuncDef *Functions = dynamic_cast<ASfuncDef*>(ast);
      std::cout << " " << Functions->getIdentifier()->toString() << std::endl;
      int FunctionDeclarations = Functions->getNumVarDef();
      for (int Function = 0 ; Function <  FunctionDeclarations; Function++)
      {
          std::cout << "  "<< Functions->getVarDef(Function)->toString() << std::endl;
      }
      ASblockState *FunctionBlock = dynamic_cast<ASblockState*>(Functions->getStatement());
      JVMgenerateStatement::BlockStatement(FunctionBlock, tc);
      std::cout << std::endl;
  }

  void JVMgenerateStatement::BlockStatement(ASblockState *ThisBlock,JVMtargetCode *tc) {
      std::cout << "  " << ThisBlock->toTypeString() << std::endl;
      int BlockVars = ThisBlock->getNumVarDef();
      for (int Var = 0 ; Var <  BlockVars; Var++)
      {
          std::cout << " "<< ThisBlock->getVarDef(Var)->toString() << std::endl;
      }
      ASexpr *expr_set; ASifState *If_set;
      ASwriteState *write_set; ASreturnState *return_set;
      int Blocks = ThisBlock->getNumStatement();
      for(int Block = 0 ; Block < Blocks ; Block++)
      {
          enum stateType ThisStatement = ThisBlock->getStatement(Block)->getType();

          switch (ThisStatement){
              case EXPRstate:
                  expr_set = dynamic_cast<ASexpr*>(ThisBlock->getStatement(Block));
                  std::cout << "   " << ThisBlock->getStatement(Block)->toTypeString() << std::endl;
                  //JVMgenerateExpression::genExpression(expr_set, tc);
                  break;
//              case BREAKstate:
//                  break;
//              case BLOCKstate:
//                  break;
              case IFstate:
                  If_set = dynamic_cast<ASifState*>(ThisBlock->getStatement(Block));
                  JVMgenerateStatement::IfStatement(If_set, tc);
                  break;
//              case NULLstate:
//                  break;
              case RETURNstate:
                  return_set = dynamic_cast<ASreturnState*>(ThisBlock->getStatement(Block));
                  std::cout << "   " << ThisBlock->getStatement(Block)->toTypeString() << std::endl;
                  JVMgenerateStatement::ReturnStatement(return_set, tc);
                  break;
//              case WHILEstate:
//                  break;
//              case READstate:
//                  break;
              case WRITEstate:
                  write_set = dynamic_cast<ASwriteState*>(ThisBlock->getStatement(Block));
                  std::cout << "   " << ThisBlock->getStatement(Block)->toTypeString() << std::endl;
                  break;
//              case NEWLINEstate:
//                  break;
//              case EMPTYstate:
//                  break;
//              default:
//                  break;
          }
          ASexpr *expr_set; ASifState *If_set;
          ASwriteState *write_set;
      }
    }

    void JVMgenerateStatement::IfStatement(ASifState *ThisIf,JVMtargetCode *tc) {
        ASexpr *expr_set; ASstatement *statement_set; ASblockState *FunctionBlock;
        std::cout << "   " << ThisIf->toTypeString() << std::endl;
        if (ThisIf->isBinary()){
            std::cout << "    Op1 " << ThisIf->getOp1()->toTypeString() << std::endl;
            expr_set = dynamic_cast<ASexpr*>(ThisIf->getOp1());
            JVMgenerateExpression::genExpression(expr_set, tc);
            statement_set = dynamic_cast<ASstatement*>(ThisIf->getOp2());
            std::cout << "    Op2 " << statement_set->toTypeString() << std::endl;
            FunctionBlock = dynamic_cast<ASblockState*>(statement_set);
            JVMgenerateStatement::BlockStatement(FunctionBlock, tc);
        } else {
            std::cout << "    " << ThisIf->getOp1()->toTypeString() << std::endl;
            expr_set = dynamic_cast<ASexpr*>(ThisIf->getOp1());
            JVMgenerateExpression::genExpression(expr_set, tc);
            statement_set = dynamic_cast<ASstatement*>(ThisIf->getOp2());
            std::cout << "    " << statement_set->toTypeString() << std::endl;
            FunctionBlock = dynamic_cast<ASblockState*>(statement_set);
            JVMgenerateStatement::BlockStatement(FunctionBlock, tc);
            statement_set = dynamic_cast<ASstatement*>(ThisIf->getOp3());
            std::cout << "    " << statement_set->toTypeString() << std::endl;
            FunctionBlock = dynamic_cast<ASblockState*>(statement_set);
            JVMgenerateStatement::BlockStatement(FunctionBlock, tc);
        }
    }
    void JVMgenerateStatement::ReturnStatement(ASreturnState *ThisReturn,JVMtargetCode *tc) {
        ASexpr *expr_set;
        std::cout << "   " << ThisReturn->toTypeString() << std::endl;
        if (ThisReturn->isSimple()){
            std::cout << "    Op1 " << ThisReturn->getOp()->toTypeString() << std::endl;
            expr_set = dynamic_cast<ASexpr*>(ThisReturn->getOp());
            //JVMgenerateExpression::genExpression(expr_set, tc);
        } else {
            std::cout << "   No " << ThisReturn->toTypeString() << std::endl;
        }
    }
  }




