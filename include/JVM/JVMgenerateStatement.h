#ifndef JVMGENERATESTATEMENT_H
#define JVMGENERATESTATEMENT_H

#include "TCglobals.h"
#include "TCsymTable.h"

#include "ASstatement.h"
#include "ASexpr.h"
#include "JVMtargetCode.h"

/*
// D. Resler 4/2010

package codegen.JVM;

import compilers.SymbolTable;

import globals.TCglobals;

import abstractSyntax.Statement;
import abstractSyntax.Expression;
import abstractSyntax.LabeledState;
import abstractSyntax.AssignState;
import abstractSyntax.WriteState;
import abstractSyntax.ReadState;
import abstractSyntax.IfState;
import abstractSyntax.GotoState;
import abstractSyntax.SkipState;

import symTable.TCsymbol;

import codegen.JVM.instruction.GETSTATIC;
import codegen.JVM.instruction.INVOKEVIRTUAL;
import codegen.JVM.instruction.LDC;
import codegen.JVM.instruction.IFNE;
import codegen.JVM.instruction.GOTO;

import codegen.JVM.label.label;
import codegen.JVM.label.codeLabel;
*/
namespace toyc {

class JVMgenerateStatement {
  public:
  static void genStatement(ASdefinition*,JVMtargetCode*);

    /*
    public static void genStatement(Statement ast, JVMtargetCode tc) {
        if (ast instanceof AssignState) {
            AssignState as = (AssignState) ast;
            JVMgenerateExpression.genExpression(as.getExpr(),tc);
            JVMgenUtils.gen_ISTORE(as.getId(),tc);
        } else if (ast instanceof WriteState) {
            JVMgenUtils.gen_ALOAD(st.find("System.out"),tc);
            JVMgenerateExpression.genExpression(((WriteState) ast).getExpr(),tc);
            tc.add(new INVOKEVIRTUAL(JVMgenGlobals.PRINT_INT_NEWLINE_METHOD_SPEC));
        } else if (ast instanceof ReadState) {
            // prompt first
            JVMgenUtils.gen_ALOAD(st.find("System.out"),tc);
            tc.add(new LDC("input: "));
            tc.add(new INVOKEVIRTUAL(JVMgenGlobals.PRINT_STRING_METHOD_SPEC));
            // now input value
            JVMgenUtils.gen_ALOAD(st.find("System.in"),tc);
            tc.add(new INVOKEVIRTUAL(JVMgenGlobals.READ_INT_METHOD_SPEC));
            JVMgenUtils.gen_ISTORE(st.find(((ReadState)ast).getSymbol().getId()),tc);
        } else if (ast instanceof IfState) {
            IfState ifStateAST = (IfState) ast;
            JVMgenerateExpression.genExpression(ifStateAST.getCondition(),tc);
            tc.add(new IFNE(new label(ifStateAST.getLabel().getLexeme())));
        } else if (ast instanceof GotoState) {
            tc.add(new GOTO(new label(((GotoState)ast).getLabel().getLexeme()) ));
        } else if (ast instanceof LabeledState) {
            LabeledState labeledStateAST = (LabeledState) ast;
            tc.add(new codeLabel((labeledStateAST.getSym()).getId()));
            JVMgenerateStatement.genStatement(labeledStateAST.getState(),tc);
        } else if (ast instanceof SkipState) {
            // do nothing
        }
    }
    */
};

}
#endif
