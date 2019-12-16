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
#include "ASfuncCall.h"
#include "ASwriteState.h"
#include "ASexprState.h"
#include "ASblockState.h"
#include "ASvarDef.h"
#include "ASreadState.h"
#include "AStype.h"

#include "TCtoken.h"

#include "limit.h"
#include "JVMgenerateProgram.h"
#include "JVMtargetCode.h"
#include "JVMgenerateStatement.h"
#include "JVMgenerateExpression.h"
#include "JVMgenUtils.h"
#include "JVMgenGlobals.h"
#include "codeLabel.h"
#include "line.h"
#include "GOTO.h"
#include "IFNE.h"
#include "INVOKESPECIAL.h"
#include "INVOKEVIRTUAL.h"
#include "RETURN.h"
#include "LDC.h"
#include "GETSTATIC.h"


namespace toyc {
    /// Useless Function Sorry
    ASvarDef* JVMgenerateStatement::ASvarDefinition(ASvarDef *initlize, JVMtargetCode *tc) { return initlize; }

    void JVMgenerateStatement::genStatement(ASdefinition *ast,JVMtargetCode *tc) {
      ASfuncDef *Functions = dynamic_cast<ASfuncDef*>(ast);

      int FunctionDeclarations = Functions->getNumVarDef();

      if (FunctionDeclarations < 2) { tc->add(new limit("stack",10)); }
      else { tc->add(new limit("stack",10 )); }

      for (int Function = 0 ; Function <  FunctionDeclarations; Function++) // Not sure if needed
      {
//          ASvarDef *VarInit = JVMgenerateStatement::ASvarDefinition(dynamic_cast<ASvarDef*>(Functions->getVarDef(Function)), tc);
//          AStype *step = dynamic_cast<AStype*>(VarInit->getIdentifier(Function));
//          std::cout << "  "<< step->getExpr()->getLexeme() << std::endl;
//          JVMgenUtils::gen_ISTORE(*symTable->getSym(symTable->find(step->getExpr()->getLexeme())),tc);
      }

      ASblockState *FunctionBlock = dynamic_cast<ASblockState*>(Functions->getStatement());
      JVMgenerateStatement::BlockStatement(FunctionBlock, tc);
  }

    void JVMgenerateStatement::BlockStatement(ASblockState *ThisBlock,JVMtargetCode *tc) {
      int BlockVars = ThisBlock->getNumVarDef();
      tc->add(new limit("locals",10));  // Scooping is hard
      for (int Var = 0 ; Var <  BlockVars; Var++) // not sure if needed
      {
//          ASvarDef *VarInit = JVMgenerateStatement::ASvarDefinition(dynamic_cast<ASvarDef*>(ThisBlock->getVarDef(Var)), tc);
//          AStype *step = dynamic_cast<AStype*>(VarInit->getIdentifier(Var));
//          std::cout << "  "<< step->getExpr()->getLexeme() << std::endl;
//          JVMgenUtils::gen_ISTORE(*symTable->getSym(symTable->find(step->getExpr()->getLexeme())),tc);
      }
      ASreadState *read_set;
      ASexprState *expr_set; ASifState *If_set;
      ASwriteState *write_set; ASreturnState *return_set;
      int Blocks = ThisBlock->getNumStatement();
      for(int Block = 0 ; Block < Blocks ; Block++)
      {
          enum stateType ThisStatement = ThisBlock->getStatement(Block)->getType();

          switch (ThisStatement){
              case READstate:
                  JVMgenerateProgram::gen_input_stream_store(tc);
//                  tc->add(new line(LINE_COUNTER)); LINE_COUNTER++;    //  Bookmakr
                  break;
              case WRITEstate: // Untested
//                  tc->add(new GETSTATIC(OUTPUT_FIELD_SPEC,OUTPUT_DESCRIPTOR));
//                  JVMgenUtils::gen_ASTORE(*symTable->getSym(symTable->find("System.out")),tc);
//                  JVMgenerateProgram::gen_output_stream_store(tc);
//                  tc->add(new line(LINE_COUNTER)); LINE_COUNTER++;    //  Bookmakr
                  break;
              default: // Should not happen
                  break;
          }
      }
      for (int Block = 0 ; Block < Blocks ; Block++)
      {
          enum stateType ThisStatement = ThisBlock->getStatement(Block)->getType();
          switch (ThisStatement){
              case EXPRstate:
                  expr_set = dynamic_cast<ASexprState*>(ThisBlock->getStatement(Block));
                  JVMgenerateStatement::ExprStatement(expr_set, tc);
                  break;
              case BREAKstate: // not done
                  break;
              case BLOCKstate:
                  break;
              case IFstate:
                  If_set = dynamic_cast<ASifState*>(ThisBlock->getStatement(Block));
                  JVMgenerateStatement::IfStatement(If_set, tc);
                  break;
              case NULLstate:
                  break;
              case RETURNstate:
                  return_set = dynamic_cast<ASreturnState*>(ThisBlock->getStatement(Block));
                  JVMgenerateStatement::ReturnStatement(return_set, tc);
                  break;
              case WHILEstate:
                  break;
              case READstate:
                  read_set = dynamic_cast<ASreadState*>(ThisBlock->getStatement(Block));
                  JVMgenerateStatement::ReadStatement(read_set, tc);
                  break;
              case WRITEstate:
                  write_set = dynamic_cast<ASwriteState*>(ThisBlock->getStatement(Block));
                  JVMgenerateStatement::WriteStatement(write_set, tc);
                  break;
              case NEWLINEstate:
                  break;
              case EMPTYstate:
                  break;
              default:
                  break;
          }
      }
    }

    void JVMgenerateStatement::ReadStatement(ASreadState *ThisRead, JVMtargetCode *tc){
    }

    void JVMgenerateStatement::IfStatement(ASifState *ThisIf,JVMtargetCode *tc) {
        ASexpr *expr_set; ASstatement *statement_set; ASblockState *FunctionBlock;
        if (!ThisIf->isBinary()){
            expr_set = dynamic_cast<ASexpr*>(ThisIf->getOp1());
            JVMgenerateExpression::genExpression(expr_set, tc);
            statement_set = dynamic_cast<ASstatement*>(ThisIf->getOp2());
//                std::cout << "  " << statement_set->toTypeString() << std::endl;    // Debuggung
            FunctionBlock = dynamic_cast<ASblockState*>(statement_set);
            JVMgenerateStatement::BlockStatement(FunctionBlock, tc);
        } else {
//                std::cout << "  " << ThisIf->getOp1()->toTypeString() << std::endl;    // Debuggung
            expr_set = dynamic_cast<ASexpr*>(ThisIf->getOp1());
            JVMgenerateExpression::genExpression(expr_set, tc);
//            tc->add(new line(LINE_COUNTER)); LINE_COUNTER++;    //  Bookmakr
            statement_set = dynamic_cast<ASstatement*>(ThisIf->getOp2());
//                std::cout << "  " << statement_set->toTypeString() << std::endl;    // Debuggung
            FunctionBlock = dynamic_cast<ASblockState*>(statement_set);
            JVMgenerateStatement::BlockStatement(FunctionBlock, tc);
            statement_set = dynamic_cast<ASstatement*>(ThisIf->getOp3());
//                std::cout << "  " << statement_set->toTypeString() << std::endl;    // Debuggung
            FunctionBlock = dynamic_cast<ASblockState*>(statement_set);
            JVMgenerateStatement::BlockStatement(FunctionBlock, tc);
        }
    }

    void JVMgenerateStatement::ReturnStatement(ASreturnState *ThisReturn,JVMtargetCode *tc) {
        ASsimpleExpr *var;
        if (ThisReturn->isSimple()){
            var = dynamic_cast<ASsimpleExpr*>(ThisReturn->getOp());
//                std::cout << " " << var->getExpr()->getLexeme()<< std::endl;    // Debuggung
            JVMgenerateExpression::genExpression(var, tc);
        } else { }
    }

    void JVMgenerateStatement::ExprStatement(ASexprState *ThisExpr,JVMtargetCode *tc) {
        ASexpr *expr_set;
//        tc->add(new line(LINE_COUNTER)); LINE_COUNTER++;    //  Bookmakr
//            std::cout << "  " << ThisExpr->getOp()->toTypeString() << std::endl;     // Debuggung
        expr_set = dynamic_cast<ASexpr*>(ThisExpr->getOp());
        JVMgenerateExpression::genExpression(expr_set, tc);

    }

    void JVMgenerateStatement::WriteStatement(ASwriteState *ThisWrite,JVMtargetCode *tc) {
        ASfuncCall *sexpr = dynamic_cast<ASfuncCall*>(ThisWrite->getExpression(0));
        JVMgenerateExpression::genExpression(sexpr,tc);
    }
}




